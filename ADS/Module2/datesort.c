#include <stdio.h>
#include <stdlib.h>

// объявил тип Date для упрощения работы с указателями
typedef struct Date {
    int Day;
    int Month;
    int Year;
} Date;

// получение поля структуры Date
int get_element(Date *arr, size_t index, int mode) {
    switch (mode) {
            case 31:
                return arr[index].Day - 1;
            case 12:
                return arr[index].Month - 1;
            case 61:
                return arr[index].Year - 1970;
            default:
                return -1;
        }
}

// сортировка распределением
void distsort(Date *arr, size_t arr_size, int keys) {
    size_t *counter = (size_t *)calloc(keys, sizeof(size_t));

    for (size_t i = 0; i < arr_size; i++) {
        int element = get_element(arr, i, keys);
        counter[element]++;
    }

    for (int i = 1; i < keys; i++) {
        counter[i] += counter[i-1];
    }

    Date *sorted = (Date *)calloc(arr_size, sizeof(Date));
    for (long i = (long)arr_size - 1; i >= 0; i--) {
        int element = get_element(arr, i, keys);
        int index = counter[element] - 1;
        sorted[index] = arr[i];
        counter[element]--;
    }

    for (size_t i = 0; i < arr_size; i++) {
        arr[i] = sorted[i];
    }

    free(counter);
    free(sorted);
}

void radixsort(Date *arr, size_t arr_size) {
    int bases[3] = {31, 12, 61};
    for (int i = 0; i < 3; i++) {
        distsort(arr, arr_size, bases[i]);
    }
}

int main(int argc, char **argv) {
    size_t n;
    scanf("%lu", &n);
    Date *Dates_Arr = (Date *)malloc(n * (sizeof(Date)));
    for (int i = 0; i < n; i++) {
        int year, month, day;
        scanf("%d%d%d", &year, &month, &day);
        Dates_Arr[i] = (Date){ day, month, year };
    }
    radixsort(Dates_Arr, n);
    for (int i = 0; i < n; i++) {
        int year = Dates_Arr[i].Year;
        int month = Dates_Arr[i].Month;
        int day = Dates_Arr[i].Day;
        printf("%04d %02d %02d\n", year, month, day);
    }
    free(Dates_Arr);
    return 0;
}