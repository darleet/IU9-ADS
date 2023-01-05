#include <stdio.h>
#include <stdlib.h>

// определим размер буфера
#define BUFFER_SIZE 1000

// тип "слово"
typedef struct word {
    char *p;
    size_t len;
} word;

// получение слов из переданной строки
int get_words(char *str, word *arr) {
    char symbol = -1;
    char prev = ' ';
    int wcounter = 0;
    while (symbol != '\0') {
        symbol = *str;
        if ((symbol == ' ' || symbol == '\0') && prev != ' ') {
            (*arr).len = str - (*arr).p;
            arr++;
        } else if (symbol != ' ' && prev == ' ') {
            (*arr).p = str;
            wcounter += 1;
        }
        prev = symbol;
        str++;
    }
    return wcounter;
}

void csort(char *src, char *dest) {

    // список слов, *p - указатель на слово, len - длина слова
    word *words = (word *)malloc(sizeof(word) * BUFFER_SIZE);
    // количество слов
    int wnum = get_words(src, words);
    // массив подсчета количества слов по длине
    int *counter = (int *)calloc(BUFFER_SIZE, sizeof(int));
    // массив отсортированных слов
    word *sorted = (word *)malloc(sizeof(word) * wnum);

    // алгоритм сортировки
    for (int i = 0; i < wnum; i++) {
        counter[words[i].len] += 1;
    }
    for (int i = 1; i < BUFFER_SIZE; i++) {
        counter[i] = counter[i-1] + counter[i];
    }
    for (int i = 0; i < wnum; i++) {
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

    free(words);
    free(counter);
    free(sorted);
}

int main(int argc, char **argv) {
    char *input = (char *)malloc(BUFFER_SIZE);
    char *output = (char *)malloc(BUFFER_SIZE);
    scanf("%[^\n]%*c", input);
    csort(input, output);
    printf("%s", output);
    free(input);
    free(output);
    return 0;
}