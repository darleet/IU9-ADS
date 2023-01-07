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
    // массив отсортированных слов
    word *sorted = (word *)malloc(sizeof(word) * wnum);

    // алгоритм сортировки, модифицирован для структуры word
    for (int i = 0; i < wnum; i++) {
        counter[words[i].len] += 1;
    }
    for (int i = 1; i < BUFFER_SIZE; i++) {
        counter[i] = counter[i-1] + counter[i];
    }
    for (int i = wnum - 1; i >= 0; i--) {
        int index = counter[words[i].len];
        sorted[index - 1].p = words[i].p;
        sorted[index - 1].len = words[i].len;
        counter[words[i].len]--;
    }

    // выведем результат в dest
    for (int i = 0; i < wnum; i++) {
        int length = sorted[i].len;
        char *symbol = (char *)sorted[i].p;
        for (int j = 0; j < length; j++) {
            *dest = *symbol;
            dest++;
            symbol++;
        }
        if (wnum - i > 1) {
            *dest = ' ';
            dest++;
        }
    }
    *dest = '\0';

    free(words);
    free(counter);
    free(sorted);
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