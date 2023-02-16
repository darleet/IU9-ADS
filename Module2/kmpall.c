#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SUB 100000

// Префикс-функция из презентации
int *prefix(char *s) {
    int length = strlen(s);
    int *pi = (int *)calloc(length, sizeof(int));
    int t = 0;

    for (int i = 1; i < length; i++) {
        while (t > 0 && s[t] != s[i]) {
            t = pi[t - 1];
        }
        if (s[t] == s[i]) {
            t++;
        }
        pi[i] = t;
    }

    return pi;
}

// Алгоритм КМП из презентации
int kmpsub(char *s, char *t, int *indices) {
    int counter = 0;
    int slen = strlen(s);
    int tlen = strlen(t);
    int *pi = prefix(s);
    int q = 0;

    for (int k = 0; k < tlen; k++) {
        while (q > 0 && s[q] != t[k]) {
            q = pi[q - 1];
        }
        if (s[q] == t[k]) {
            q++;
        }
        if (q == slen) {
            k = k - slen + 1;
            indices[counter] = k;
            counter++;
        }
    }

    free(pi);
    return counter;
}

int main(int argc, char **argv) {
    char *s = argv[1];
    char *t = argv[2];
    int *indices = (int *)malloc(MAX_SUB * sizeof(int));
    int sub_cnt = kmpsub(s, t, indices);

    for (int i = 0; i < sub_cnt; i++) {
        printf("%i ", indices[i]);
    }

    free(indices);
    return 0;
}