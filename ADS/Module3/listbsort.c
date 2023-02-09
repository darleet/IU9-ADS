#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define BUFFER_SIZE 10000

typedef struct Elem {
    struct Elem *next;
    char *word;
} Elem;

// Чтобы не вызывать strlen() при инициализации списка или
// добавлении новых элементов, передаю длину слова в качестве
// аргумента wlen. Туда будет передаваться значение счетчика букв

// Инициализация списка
Elem *init_list(char *word, int wlen) {
    Elem *new_list = (Elem *)malloc(sizeof(Elem));
    new_list->word = (char *)malloc((wlen + 1) * sizeof(char));
    strcpy(new_list->word, word);
    new_list->next = NULL;
    return new_list;
}

// Вставка элемента
Elem *insert_after(char *word, int wlen, Elem *pivot) {
    Elem *x_el = (Elem *)malloc(sizeof(Elem));
    x_el->word = (char *)malloc((wlen + 1) * sizeof(char));
    strcpy(x_el->word, word);
    x_el->next = pivot->next;
    pivot->next = x_el;
    return x_el;
}

// Очищение списка
void clean_list(Elem *list) {
    Elem *x_el = list;
    while (x_el) {
        Elem *next_el = x_el->next;
        free(x_el->word);
        free(x_el);
        x_el = next_el;
    }
}

void print_list(Elem *list) {
    Elem *x_el = list;
    while (x_el) {
        printf("%s\n", x_el->word);
        x_el = x_el->next;
    }
}

// Поменять местами два элемента списка
void swap(Elem *a, Elem *b) {
    char *temp_word = a->word;
    a->word = b->word;
    b->word = temp_word;
}

// Функция сортировки пузырьком
Elem *bsort(Elem *list) {
    if (list) {
        Elem *x_el = list->next;
        Elem *prev_el = list;
        while (x_el) {
            if (strlen(x_el->word) < strlen(prev_el->word)) {
                swap(x_el, prev_el);
            }
            prev_el = x_el;
            x_el = x_el->next;
        }
        Elem *bound = prev_el;
        x_el = list->next;
        prev_el = list;
        while (bound != list) {
            while (x_el != bound) {
                if (strlen(x_el->word) < strlen(prev_el->word)) {
                    swap(x_el, prev_el);
                }
                prev_el = x_el;
                x_el = x_el->next; 
            }
            bound = prev_el;
            x_el = list->next;
            prev_el = list;
        }
    }
    return list;
}

int main(int argc, char **argv) {
    char *str = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
    fgets(str, BUFFER_SIZE + 1, stdin);
    
    // создадим вспомогательный указатель
    char *pstr = str;

    char *word = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
    int w_index = 0;

    while (!(isspace(*pstr) || *pstr == '\0')) {
        word[w_index] = *pstr;
        w_index++;
        pstr++;
    }

    word[w_index] = '\0';
    Elem *list = init_list(word, w_index);
    Elem *prev_el = list;
    w_index = 0;

    while (*pstr != '\0') {
        pstr++;
        if ((isspace(*pstr) || *pstr == '\0') && w_index) {
            word[w_index] = '\0';
            prev_el = insert_after(word, w_index, prev_el);
            w_index = 0;
        } else if (!(isspace(*pstr) || *pstr == '\0')) {
            word[w_index] = *pstr;
            w_index++;
        }
    }

    Elem *sorted_list = bsort(list);
    print_list(sorted_list);

    clean_list(list);
    free(word);
    free(str);

    return 0;
}