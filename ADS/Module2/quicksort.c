#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void swap(int *base, size_t ind1, size_t ind2) {
    int temp = base[ind1];
    base[ind1] = base[ind2];
    base[ind2] = temp;
}

// Для того, чтобы избежать рекурсивной вложенности больше log n,
// и, соответственно, переполнения стека, реализовал алгоритм 
// quicksort из .NET. Об этом алгоритме узнал в одном из постов
// на Хабре, вот ссыль: https://habr.com/ru/post/188012/

// Из этого вытекает использование мной пирамидальной сортировки,
// а она взята мной из презентации. Сам quicksort тоже из презентации,
// изменил только саму рекурсивную функцию, добавив в нее условия
// на превышение глубины рекурсии и длины последовательности
// меньше переданного числа m.

// heapify из презентации
void heapify(int *base, size_t index, size_t arr_size) {
    while (1) {
        size_t left = 2 * index + 1;
        size_t right = left + 1;
        size_t max_index = index;
        if (left < arr_size && base[index] < base[left]) {
            index = left;
        }
        if (right < arr_size && base[index] < base[right]) {
            index = right;
        }
        if (index == max_index) {
            break;
        }
        swap(base, index, max_index);
    }
}

// build heap из презентации
void build_heap(void *base, size_t arr_size) {
    long long i = (arr_size / 2) - 1;
    for (i; i >= 0; i--) {
        heapify(base, i, arr_size);
    }
}

// hsort из презентации
void hsort(void *base, size_t arr_size) {
    if (arr_size > 1) {
        build_heap(base, arr_size);
        long long i = arr_size - 1;
        for (i; i > 0; i--) {
            swap(base, 0, i);
            heapify(base, 0, i);
        }
    }
}

// сортировка прямым выбором
void selsort(int *base, size_t arr_size) {
    for (size_t i = 0; i < arr_size; i++) {
        size_t min_index = i;
        for (size_t j = i + 1; j < arr_size; j++) {
            if (base[min_index] > base[j]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            swap(base, min_index, i);
        }
    }
}

// алгоритм разделения подпоследовательности (из презентации)
size_t partition(int *base, size_t left, size_t right) {
    size_t border = left;
    for (size_t i = left; i < right-1; i++) {
        if (base[i] < base[right-1]) {
            swap(base, i, border);
            border++;
        }
    }
    swap(base, border, right-1);
    return border;
}

// рекурсивная функция сортировки
void quicksortrec(int *base, size_t left, size_t right, size_t selsort_tr, int call_depth) {
    if (right - left < selsort_tr) {
        selsort(base + left, right - left);
    } else if (call_depth <= 0) {
        hsort(base + left, right - left);
    } else if (left + 1 < right) {
        size_t border = partition(base, left, right);
        quicksortrec(base, left, border, selsort_tr, call_depth-1);
        quicksortrec(base, border, right, selsort_tr, call_depth-1);
    }
}

// функция сортировки (каркас)
void quicksort(int *base, size_t arr_size, size_t selsort_tr) {
    quicksortrec(base, 0, arr_size, selsort_tr, log10(arr_size));
}

int main(int argc, char **argv) {
    size_t n, m;
    scanf("%lu", &n);
    scanf("%lu", &m);
    int *arr = (int *)calloc(n, sizeof(int));
    for (size_t i = 0; i < n; i++) {
        scanf("%i", &arr[i]);
    }
    quicksort(arr, n, m);
    for (size_t i = 0; i < n; i++) {
        printf("%i\n", arr[i]);
    }
    free(arr);
    return 0;
}

// (Комментарий по поводу решения задачи перед heapify)