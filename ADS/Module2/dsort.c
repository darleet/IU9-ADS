#include <stdio.h>
#include <stdlib.h>

// 26 латинских букв
#define DICT_SIZE 26

void dsort(char *str) {
    unsigned long *counter = (unsigned long *)calloc(DICT_SIZE, sizeof(unsigned long));
    char *symbol = str;
    unsigned long length = 0;

    while (*symbol != '\0') {
        long index = *symbol - 'a';
        counter[*symbol - 'a']++;
        symbol++;
        length++;
    }
    for (int i = 1; i < DICT_SIZE; i++) {
        counter[i] = counter[i] + counter[i-1];
    }

    // чтобы алгоритм был устойчив, будем записывать
    // буквы в последовательность в обратном порядке
    
    char *sorted = (char *)malloc(length * sizeof(char));
    for (long long i = (long long)length - 1; i >= 0; i--) {
        unsigned long index = str[i] - 'a';
        unsigned long indexc = counter[index];
        char symbol = str[i];
        sorted[counter[index] - 1] = str[i];
        counter[index]--;
    }

    for (unsigned long i = 0; i < length; i++) {
        *str = sorted[i];
        str++;
    }

    free(sorted);
    free(counter);
}

int main(int argc, char **argv) {
    char *str;
    scanf("%ms", &str);
    dsort(str);
    printf("%s", str);
    free(str);
    return 0;
}