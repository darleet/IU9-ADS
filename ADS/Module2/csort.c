#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// определим размер буфера
#define BUFFER_SIZE 1000

// тип "слово"
typedef struct word {
    char *p;
    size_t len;
} word;

// получение слов из переданной строки
int get_words(char *str, word *arr) {
    char prev = ' ';
    int wcounter = 0;
    while (*str != '\0') {
        if (isspace(prev) && !isspace(*str)) {
            char *start = str;
            while (*str != '\0' && !isspace(*str)) {
                str++;
            }
            int length = (int)(str - start);
            (*arr).p = start;
            (*arr).len = length;
            wcounter++;
            arr++;
        } else {
            str++;
        }
    }
    return wcounter;
}

void csort(char *src, char *dest) {
    // список слов, *p - указатель на слово, len - длина слова
    word *words = (word *)malloc(sizeof(word) * (BUFFER_SIZE + 1));
    // количество слов
    int wnum = get_words(src, words);
    // переопределим количество выделенной памяти на массив
    words = (word *)realloc(words, wnum * sizeof(word));
    // массив подсчета количества слов по длине
    int *counter = (int *)calloc(BUFFER_SIZE + 1, sizeof(int));

    for (int i = 0; i < wnum - 1; i++) {
        for (int j = i + 1; j < wnum; j++) {
            if (words[j].len < words[i].len) {
                counter[i]++;
            } else {
                counter[j]++;
            }
        }
    }

    // выведем результат в dest
    int dest_index = 0;
    for (int i = 0; i < wnum; i++) {
        int j = 0;
        while (counter[j] != i) {
            j++;
        }
        char *wp = words[j].p;
        for (int i = 0; i < words[j].len; i++) {
            dest[dest_index] = *wp;
            dest_index++;
        }
        if (wnum - i > 1) {
            dest[dest_index] = ' ';
            dest_index++;
        }
    }
    dest[dest_index] = '\0';
    free(words);
    free(counter);
}

int main(int argc, char **argv) {
    char *input = (char *)calloc(BUFFER_SIZE, sizeof(char));
    char *output = (char *)calloc(BUFFER_SIZE, sizeof(char));
    fgets(input, BUFFER_SIZE, stdin);
    csort(input, output);
    printf("%s", output);
    free(input);
    free(output);
    return 0;
}