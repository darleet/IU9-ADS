#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// слияние подпоследовательностей (из презентации)
void merge(int *base, size_t seq1_start, size_t seq2_start, size_t seq2_end) {
    size_t length = seq2_end - seq1_start;
    int *buffer = (int *)malloc(sizeof(int) * length);
    size_t cnt1 = seq1_start;
    size_t cnt2 = seq2_start;
    size_t cntbuff = 0;
    while (cntbuff < length) {
        if (cnt2 < seq2_end && (abs(base[cnt2]) < abs(base[cnt1]) || cnt1 == seq2_start)) {
            buffer[cntbuff] = base[cnt2];
            cnt2++;
        } else {
            buffer[cntbuff] = base[cnt1];
            cnt1++;
        }
        cntbuff++;
    }
    memcpy(base + seq1_start, buffer, sizeof(int) * length);
    free(buffer);
}

void swap(int *base, size_t index1, size_t index2) {
    int temp = base[index1];
    base[index1] = base[index2];
    base[index2] = temp;
}

// функция сортировки вставками (из презентации)
void insertionsort(int *base, size_t arr_size) {
    for (size_t i = 1; i < arr_size; i++) {
        int step_el = base[i];
        for (size_t j = i; j > 0; j--) {
            if (abs(step_el) < abs(base[j-1])) {
                swap(base, j, j-1);
            } else {
                break;
            }
        }
    }
}

// рекурсивная функция сортировки (из презентации)
void mergesortrec(int *base, size_t start, size_t end) {
    if (end - start >= 5) {
        size_t med = (start + end) / 2;
        mergesortrec(base, start, med);
        mergesortrec(base, med, end);
        merge(base, start, med, end);
    } else if (end - start > 1) {
        insertionsort(base + start, end - start);
    }
}

// функция сортировки слиянием (из презентации)
void mergesort(int *base, size_t arr_size) {
    mergesortrec(base, 0, arr_size);
}

int main(int argc, char **argv) {
    size_t arr_size;
    scanf("%lu", &arr_size);
    int *arr = (int *)malloc(sizeof(int) * arr_size);
    for (size_t i = 0; i < arr_size; i++) {
        scanf("%i", &arr[i]);
    }
    mergesort(arr, arr_size);
    for (size_t i = 0; i < arr_size; i++) {
        printf("%i ", arr[i]);
    }
    free(arr);
    return 0;
}