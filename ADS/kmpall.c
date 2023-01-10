#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// префиксная функция (из презентации)
void prefix(char *str, size_t *pi, size_t len) {
    for (size_t i = 1; i < len; i++) {
        size_t t = pi[i-1];
        while ((t > 0) && (str[t] != str[i])) {
            t = pi[t-1];
        }
        if (str[t] == str[i]) {
            t++;
        }
        pi[i] = t;
    }
}

// алгоритм из презентации, добавил выполнение 
// префиксной функции (т.к. выводим все индексы вхождений)
void kmpfunc(char *str, char *sub) {
    size_t len_sub = strlen(sub);
    size_t len_str = strlen(str);
    size_t *pi = (size_t *)calloc(len_sub, sizeof(size_t));
    prefix(sub, pi, len_sub);
    size_t q = 0;
    for (size_t k = 0; k < len_str; k++) {
        while ((q > 0) && (sub[q] != str[k])) {
            q = pi[q-1];
        }
        if (sub[q] == str[k]) {
            q++;
        }
        if (q == len_sub) {
            // решил ограничиться простым выводом индекса в консоль
            // (в принципе, этого достаточно для решения задачи)
            printf("%lu ", k - len_sub + 1);
        }
    }
    printf("\n");
    free(pi);
}

int main(int argc, char **argv) {
    if (argc < 3) {
        return 0;
    }
    char *sub = argv[1];
    char *str = argv[2];
    kmpfunc(str, sub);
    return 0;
}