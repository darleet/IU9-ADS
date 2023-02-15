#include <stdio.h>

void bubblesort(unsigned long nel,
        int (*compare)(unsigned long i, unsigned long j),
        void (*swap)(unsigned long i, unsigned long j)) {
    unsigned long rt = nel - 1;
    unsigned long lt = 0;
    unsigned long bound;
    while (lt < rt && nel != 0) {
        bound = rt;
        rt = 0;
        for (int i = lt; i < bound; i++) {
            if (compare(i, i+1) > 0) {
                swap(i, i+1);
                rt = i;
            }
        }

        bound = lt;
        lt = 0;
        for (int i = rt; i > bound; i--) {
            if (compare(i, i-1) < 0) {
                swap(i, i-1);
                lt = i;
            }
        }
    }
}

unsigned long arr[6] = {5, 2, 9, 1, 3, 12};
unsigned long n = 6;

int compare(unsigned long i, unsigned long j) {
    if (arr[i] == arr[j]) {
        return 0;
    }
    if (arr[i] < arr[j]) {
        return -1;
    }
    return 1;
}

void swap(unsigned long i, unsigned long j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

int main(int argc, char **argv) {
    bubblesort(n, compare, swap);
    for (int i = 0; i < n; i++) {
        printf("%lu ", arr[i]);
    }
    return 0;
}