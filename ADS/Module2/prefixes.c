#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// префикс функция (из презентации)
void prefix(char *str, int *pi, int length) {
    for (int i = 1; i < length; i++) {
        int j = pi[i - 1];
        while ((j > 0) && (str[i] != str[j])) {
            j = pi[j - 1];
        }
        if (str[i] == str[j]) {
            j++;
        }
        pi[i] = j;
    }
}

int main(int argc, char **argv) {
    if (argc < 2) {
        return 0;
    }

    char *str = argv[1];
    int length = strlen(str);
    int *pi = (int *)calloc(length, sizeof(int));
    prefix(str, pi, length);

    for (int i = 1; i < length / 2; i++) {
        int prefix_end = i * 2 - 1;
        int sub_counter = 2;
        while ((prefix_end < length) && (pi[prefix_end] >= i)) {
            printf("%i %i\n", prefix_end + 1, sub_counter);
            prefix_end += i;
            sub_counter++;
        }
        if (prefix_end != i * 2 - 1) {
            i = prefix_end;
        }
    }

    free(pi);
    return 0;
}