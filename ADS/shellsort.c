#include <stdio.h>

// функция расчета массива фибоначчиевых чисел
int fib_calc(unsigned long nel, unsigned long *fibs) {
    fibs[0] = 1;
    fibs[1] = 1;
    int i = 1;
    while (fibs[i] < nel) {
        i++;
        fibs[i] = fibs[i-1] + fibs[i-2];
    }
    // возвращаем индекс последнего фиб. числа
    return i - 1;
}

void shellsort(unsigned long nel,
        int (*compare)(unsigned long i, unsigned long j),
        void (*swap)(unsigned long i, unsigned long j)) {
    unsigned long fibs[50];
    int mfib_index = fib_calc(nel, fibs);
    // проход по числам фибоначчи
    for (int di = mfib_index; di > 0; di--) {
        // фибоначчиево число d (под индексом di)
        unsigned long d = fibs[di];
        for (unsigned long i = d; i < nel; i++) {
            long long j = i - d;
            while (j >= 0 && compare(j+d, j) < 0) {
                swap(j+d, j);
                j -= d;
            }
        }
    }
}

long arr[15] = {-8, 8, -8, -8, -6, -7, 3, 3, 3, 4, 4, -6, -6, -7, 2};

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

int main(int argc, char *argv) {
    shellsort(15, compare, swap);
    for (int i = 0; i < 15; i++) {
        printf("%li ", arr[i]);
    }
    return 0;
}