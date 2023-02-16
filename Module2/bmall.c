#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SZ 94

char norm(char letter) {
    return letter - 33;
}

// Суффиксная функция из презентации
int *suffix(char *s) {
    int length = strlen(s);
    int *arr = (int *)calloc(length, sizeof(int));
    arr[length - 1] = length - 1;
    int t = length - 1;

    for (int i = length - 2; i >= 0; i--) {
        while (t < length - 1 && s[t] != s[i]) {
            t = arr[t + 1];
        }
        if (s[t] == s[i]) {
            t--;
        }
        arr[i] = t;
    }

    return arr;
}

// Построение таблицы стоп-символов delta1 из презентации
int *del1(char *s, int size) {
    int *table = (int *)calloc(size, sizeof(int));
    int length = strlen(s);

    for (int a = 0; a < size; a++) {
        table[a] = length;
    }

    for (int j = 0; j < length; j++) {
        table[norm(s[j])] = length - 1 - j;
    }

    return table;
}

int *del2(char *s) {
    int length = strlen(s);
    int *table = (int *)calloc(length, sizeof(int));
    int *suff_arr = suffix(s);
    int t = suff_arr[0];

    for (int i = 0; i < length; i++) {
        while (t < i) {
            t = suff_arr[t + 1];
        }
        table[i] = t + length - i;
    }

    for (int i = 0; i < length - 1; i++) {
        t = i;
        while (t < length - 1) {
            t = suff_arr[t + 1];
            if (s[i] != s[t]) {
                table[t] = length - 1 - i;
            }
        }
    }

    free(suff_arr);
    return table;
}

// Алгоритм из презентации, изменил лишь его вывод
int bmsub(char *s, char *t, int size, int *indices) {
    int counter = 0;
    int slen = strlen(s);
    int tlen = strlen(t);
    int *table1 = del1(s, size);
    int *table2 = del2(s);
    int k = slen - 1;

    while (k < tlen) {
        int i = slen - 1;
        while (t[k] == s[i]) {
            if (i == 0) {
                indices[counter] = k;
                counter++;
                break;
            }
            i--;
            k--;
        }
        k += table1[norm(t[k])] > table2[i] ? table1[norm(t[k])] : table2[i];
    }

    free(table1);
    free(table2);
    return counter;
}

int main(int argc, char **argv) {
    char *s = argv[1];
    char *t = argv[2];
    int *indices = (int *)malloc(1000 * sizeof(int));
    int sub_cnt = bmsub(s, t, ALPHABET_SZ, indices);

    for (int i = 0; i < sub_cnt; i++) {
        printf("%i ", indices[i]);
    }

    free(indices);
    return 0;
}