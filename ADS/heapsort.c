#include <stdio.h>
#include <stdlib.h>

// тип строки со встроенным счетчиком букв "а"
typedef struct str_acnt {
    char *str;
    unsigned long a_counter;
} str_acnt;

void swap(void *base, size_t width, size_t a, size_t b) {
    char *el1 = ((char *)base + a * width);
    char *el2 = ((char *)base + b * width);
    for (size_t i = 0; i < width; i++) {
        char temp = *el1;
        *el1 = *el2;
        *el2 = temp;
        el1++;
        el2++;
    }
}

// heapify из презентации
void heapify(void *base, size_t width, size_t index, size_t arr_size,
        int (*compare)(const void *a, const void *b)) {
    while (1) {
        size_t low = 2 * index + 1;
        size_t high = low + 1;
        size_t max_index = index;
        if (low < arr_size && compare((char *)base + width * index, 
                (char *)base + width * low) < 0) {
            index = low;
        }
        if (high < arr_size && compare((char *)base + width * index, 
                (char *)base + width * high) < 0) {
            index = high;
        }
        if (index == max_index) {
            break;
        }
        swap(base, width, index, max_index);
    }
}

// build heap из презентации
void build_heap(void *base, size_t width, size_t arr_size,
        int (*compare)(const void *a, const void *b)) {
    long long i = (arr_size / 2) - 1;
    for (i; i >= 0; i--) {
        heapify(base, width, i, arr_size, compare);
    }
}

// hsort из презентации
void hsort(void *base, size_t nel, size_t width,
        int (*compare)(const void *a, const void *b)) {
    if (nel > 1) {
        build_heap(base, width, nel, compare);
        long long i = nel - 1;
        for (i; i > 0; i--) {
            swap(base, width, 0, i);
            heapify(base, width, 0, i, compare);
        }
    }
}

unsigned long count_a(char *str) {
    unsigned long counter = 0;
    char symbol = *str;
    while (symbol != '\0') {
        if (symbol == 'a') {
            counter++;
        }
        str++;
        symbol = *str;
    }
    return counter;
}

int cmpfunc(const void *a, const void *b) {
    const str_acnt *str_a = (const str_acnt *)a;
    const str_acnt *str_b = (const str_acnt *)b;
    unsigned long val1 = (*str_a).a_counter;
    unsigned long val2 = (*str_b).a_counter;
    return (str_a->a_counter - str_b->a_counter);
}

int main(int argc, char **argv) {
    size_t arr_size;
    scanf("%li", &arr_size);
    str_acnt *arr = (str_acnt *)malloc(arr_size * sizeof(str_acnt));
    for (size_t i = 0; i < arr_size; i++) {
        scanf("%ms", &arr[i].str);
        arr[i].a_counter = count_a(arr[i].str);
    }
    hsort(arr, arr_size, sizeof(str_acnt), cmpfunc);
    for (size_t i = 0; i < arr_size; i++) {
        printf("%s\n", arr[i].str);
    }
    free(arr);
    return 0;
}