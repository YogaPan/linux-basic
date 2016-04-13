import numpy as np
import matplotlib.pyplot as plt

def main():
    # insertion sort
    data_list = []
    time_list = []
    with open('./insertion_sort.txt', 'r') as f:
        for line in f:
            temp = line.split()
            data_list.append(temp[0])
            time_list.append(temp[2])

    plt.plot(data_list, time_list, 'r-', label='Insertion Sort')

    # selection sort
    data_list = []
    time_list = []
    with open('./selection_sort.txt', 'r') as f:
        for line in f:
            temp = line.split()
            data_list.append(int(temp[0]))
            time_list.append(int(temp[2]))

    plt.plot(data_list, time_list, 'g-', label='Selection Sort')

    # bubble sort
    data_list = []
    time_list = []
    with open('./bubble_sort.txt', 'r') as f:
        for line in f:
            temp = line.split()
            data_list.append(int(temp[0]))
            time_list.append(int(temp[2]))

    plt.plot(data_list, time_list, 'b-', label='Bubble Sort')

    # heap sort
    data_list = []
    time_list = []
    with open('./heap_sort.txt', 'r') as f:
        for line in f:
            temp = line.split()
            data_list.append(int(temp[0]))
            time_list.append(int(temp[2]))

    plt.plot(data_list, time_list, 'c-', label='Heap Sort')

    # merge sort
    data_list = []
    time_list = []
    with open('./merge_sort.txt', 'r') as f:
        for line in f:
            temp = line.split()
            data_list.append(int(temp[0]))
            time_list.append(int(temp[2]))

    plt.plot(data_list, time_list, 'y-', label='Merge Sort')

    # quick sort
    data_list = []
    time_list = []
    with open('./quick_sort.txt', 'r') as f:
        for line in f:
            temp = line.split()
            data_list.append(int(temp[0]))
            time_list.append(int(temp[2]))

    plt.plot(data_list, time_list, 'k-', label='Quick Sort')

    plt.legend()
    plt.savefig('sort.png')

if __name__ == '__main__':
    main()
