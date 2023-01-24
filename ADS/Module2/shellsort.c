#include <stdio.h>

void shellsort(unsigned long nel,
        int (*compare)(unsigned long i, unsigned long j),
        void (*swap)(unsigned long i, unsigned long j)) {
    
    // вычисление массива фибоначчиевых чисел
    unsigned long fibs[50];
    fibs[0] = 1;
    fibs[1] = 1;
    int fib_index = 1;
    while(fibs[fib_index] < nel) {
        fib_index++;
        fibs[fib_index] = fibs[fib_index - 1] + fibs[fib_index - 2];
    }
    fib_index--;

    // проход по числам фибоначчи с конца
    for (fib_index; fib_index > 0; fib_index--) {
        // левая граница каждый раз в нуле
        unsigned long l_index = 0;
        unsigned long fib_number = fibs[fib_index];
        // правая граница каждый раз в индексе по числу фибоначчи
        for (unsigned long r_index = fib_number; r_index < nel; r_index++) {
            // временные границы (левое и правое число для сравнения)
            long long temp_li = l_index;
            long long temp_ri = r_index;
            // если левая граница не вышла за массив и левое число больше правого
            while (temp_li >= 0 && compare(temp_li, temp_ri) > 0) {
                swap(temp_li, temp_ri);
                temp_ri = temp_li;
                temp_li -= fib_number;
            }
            // подвинули левую границу на 1, в цикле так же подвинется и правая
            l_index++;
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

int main(int argc, char **argv) {
    shellsort(15, compare, swap);
    for (int i = 0; i < 15; i++) {
        printf("%li ", arr[i]);
    }
    return 0;
}