#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SZ 94
#define MAX_SUB 100000

char norm(char letter) {
    return letter - 33;
}

// Суффиксная функция из презентации
long *suffix(char *s) {
    long length = strlen(s);
    long *arr = (long *)calloc(length, sizeof(long));
    arr[length - 1] = length - 1;
    long t = length - 1;

    for (long i = length - 2; i >= 0; i--) {
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
long *del1(char *s, int size) {
    long *table = (long *)calloc(size, sizeof(long));
    long length = strlen(s);

    for (int a = 0; a < size; a++) {
        table[a] = length;
    }

    for (long j = 0; j < length; j++) {
        table[norm(s[j])] = length - 1 - j;
    }

    return table;
}

long *del2(char *s) {
    long length = strlen(s);
    long *table = (long *)calloc(length, sizeof(long));
    long *suff_arr = suffix(s);
    long t = suff_arr[0];

    for (long i = 0; i < length; i++) {
        while (t < i) {
            t = suff_arr[t + 1];
        }
        table[i] = t + length - i;
    }

    for (long i = 0; i < length - 1; i++) {
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
long bmsub(char *s, char *t, int size, long *indices) {
    long counter = 0;
    long slen = strlen(s);
    long tlen = strlen(t);
    long *table1 = del1(s, size);
    long *table2 = del2(s);
    long k = slen - 1;

    while (k < tlen) {
        long i = slen - 1;
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
    long *indices = (long *)malloc(MAX_SUB * sizeof(long));
    long sub_cnt = bmsub(s, t, ALPHABET_SZ, indices);

    for (long i = 0; i < sub_cnt; i++) {
        printf("%li ", indices[i]);
    }

    free(indices);
    return 0;
}