#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#define PORT "80"
#define MAX_DATA_SIZE 1024

void *get_in_addr(struct sockaddr *sa)
{
        if (sa->sa_family == AF_INET) {
                return &(((struct sockaddr_in *)sa)->sin_addr);
        }

        return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

int main(int argc, char **argv)
{
        struct addrinfo hints, *servinfo, *p;
        int rv;
        int sockfd;
        int numbytes;
        char s[INET6_ADDRSTRLEN];
        char buf[MAX_DATA_SIZE];
        char query[100];

        if (argc != 2) {
                fprintf(stderr, "fuck.\n");
                exit(1);
        }

        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;

        if ((rv = getaddrinfo(argv[1], PORT, &hints, &servinfo)) != 0) {
                fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
                exit(1);
        }

        for (p = servinfo; p != NULL; p = p->ai_next) {
                if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
                        perror("client: socket");
                        continue;
                }
                if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
                        close(sockfd);
                        perror("client: connect");
                        continue;
                }
                break;
        }

        if (p == NULL) {
                fprintf(stderr, "client: failed to connect");
                exit(1);
        }
        inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr), s, sizeof(s));

        printf("client: connecting to %s\n", s);
        freeaddrinfo(servinfo);

        fgets(query, 200-1, stdin);
        printf("%s\n", query);

        if (send(sockfd, query, 200-1, 0) == -1) {
                perror("send");
                exit(1);
        }

        if ((numbytes = recv(sockfd, buf, MAX_DATA_SIZE-1, 0)) == 0) {
                perror("recv");
                exit(1);
        }
        buf[numbytes] = '\0';
        printf("\n\n%s\n\n", buf);

        close(sockfd);
        return 0;
}
