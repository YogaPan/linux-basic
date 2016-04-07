#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT "8888"
#define MAXDATASIZE 1000

static void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in *)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char **argv)
{
	int sockfd, numbytes;
	char buf[MAXDATASIZE];
	struct addrinfo hints, *servinfo, *p;
	int rv;
	char s[INET6_ADDRSTRLEN];

	if (argc != 2) {
		fprintf(stderr, "usage: client: hostname\n");
		exit(1);
	}

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	rv = getaddrinfo(argv[1], PORT, &hints, &servinfo);
	if (rv != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}

	for (p = servinfo; p != NULL; p = p->ai_next) {
		sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (sockfd == -1) {
			perror("client: socket");
			continue;
		}
		if ((connect(sockfd, p->ai_addr, p->ai_addrlen)) == -1) {
			close(sockfd);
			perror("client: connect");
			continue;
		}
		break;
	}

	if (p == NULL) {
		fprintf(stderr, "client: failed to connect\n");
		return 2;
	}

	inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr), \
		  s, sizeof(s));

	printf("client: connecting to %s\n", s);
	freeaddrinfo(servinfo);

	if (send(sockfd, "GET / HTTP/1.1\r\n\r\n", 30, 0) == -1) {
		perror("send");
		exit(1);
	}
	numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0);
	if (numbytes == -1) {
		perror("recv");
		exit(1);
	}
	buf[numbytes] = '\0';
	printf("client: received %s\n", buf);

	close(sockfd);
	return 0;
}