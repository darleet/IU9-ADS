#include <stdio.h>
#include <stdlib.h>

#define DSORT_BASE 256

union Int32 {
    int x;
    unsigned char bytes[4];
};

void distsort(union Int32 *arr, size_t arr_size, int digit) {
    size_t *counter = (size_t *)calloc(DSORT_BASE, sizeof(size_t));

    for (size_t i = 0; i < arr_size; i++) {
        union Int32 number = arr[i];
        int key;
        if (digit == 3) {
            key = (int)(number.bytes[digit] ^ 0x80);
        } else {
            key = number.bytes[digit];
        }
        counter[key]++;
    }

    for (int i = 1; i < DSORT_BASE; i++) {
        counter[i] += counter[i-1];
    }

    union Int32 *sorted = (union Int32 *)malloc(arr_size * sizeof(union Int32));
    for (long long i = (long long)arr_size - 1; i >= 0; i--) {
        union Int32 number = arr[i];
        int key;
        if (digit == 3) {
            key = (int)(number.bytes[digit] ^ 0x80);
        } else {
            key = number.bytes[digit];
        }
        counter[key]--;
        size_t index = counter[key];
        sorted[index] = number;
    }

    for (size_t i = 0; i < arr_size; i++) {
        arr[i] = sorted[i];
    }
    
    free(sorted);
    free(counter);
}

void radixsort(union Int32 *arr, size_t arr_size) {
    for (int i = 0; i < 4; i++) {
        distsort(arr, arr_size, i);
    }
}

int main(int argc, char **argv) {
    size_t n;
    scanf("%lu", &n);
    union Int32 *arr = (union Int32 *)malloc(n * sizeof(union Int32));
    for (size_t i = 0; i < n; i++) {
        scanf("%d", &arr[i].x);
    }
    radixsort(arr, n);
    for (size_t i = 0; i < n; i++) {
        printf("%i ", arr[i].x);
    }
    free(arr);
    return 0;
}