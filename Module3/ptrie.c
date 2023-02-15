#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_LEN 100000
#define ALPHABET_LEN 26

// хэш-коды ключевых слов
#define INSERT 400556
#define DELETE 372197
#define PREFIX 436508

typedef struct node {
    int usage;
    int word;
    struct node **arcs;
} node;

// Возвращает индекс символа в arcs
char normalise(char letter) {
    return letter - 97;
}

// Инициализация узла
node *init_node() {
    node *new_node = (node *)malloc(sizeof(node));
    new_node->arcs = (node **)calloc(ALPHABET_LEN, sizeof(node *));
    new_node->word = 0;
    new_node->usage = 0;
    return new_node;
}

// Поиск строки в множестве
int lookup(node *tr_ent, char *str) {
    size_t length = strlen(str);
    node *x_node = tr_ent;
    for (size_t i = 0; i < length; i++) {
        char letter = normalise(str[i]);
        if (x_node->arcs[letter]) {
            x_node = x_node->arcs[letter];
        } else {
            return 0;
        }
    }
    return x_node->word;
}

// Добавление строки в множество
void insert(node *tr_ent, char *str) {
    size_t length = strlen(str);
    node *x_node = tr_ent;
    for (size_t i = 0; i < length; i++) {
        char letter = normalise(str[i]);
        if (!x_node->arcs[letter]) {
            node *new_node = init_node();
            x_node->arcs[letter] = new_node;
        }
        x_node->arcs[letter]->usage++;
        x_node = x_node->arcs[letter];
    }
    x_node->word = 1;
}

// Удаление строки из множества
void delete(node *tr_ent, char *str) {
    size_t length = strlen(str);
    node *x_node = tr_ent;
    node *next_node;

    for (size_t i = 0; i < length; i++) {
        char letter = normalise(str[i]);
        next_node = x_node->arcs[letter];

        // если следующий узел используется один раз,
        // сбрасываем указатель на него
        if (x_node->arcs[letter]->usage == 1) {
            x_node->arcs[letter] = NULL;
        }

        // если текущий узел используется один раз,
        // освобождаем память от этого узла
        if (x_node->usage == 1) {
            free(x_node->arcs);
            free(x_node);
        // иначе уменьшаем кол-во вхождений
        } else  if (x_node->usage != 0) {
            x_node->usage--;
        }

        x_node = next_node;
    }

    x_node->word = 0;

    // если конечный узел используется один раз,
    // освобождаем память от этого узла
    if (x_node->usage == 1) {
        free(x_node->arcs);
        free(x_node);
    // иначе уменьшаем кол-во вхождений
    } else if (x_node->usage != 0) {
        x_node->usage--;
    }
}

// Подсчет кол-во вхождений префикса в строки
int prefix(node *tr_ent, char *str) {
    size_t length = strlen(str);
    node *x_node = tr_ent;
    for (size_t i = 0; i < length; i++) {
        char letter = normalise(str[i]);
        if (x_node->arcs[letter]) {
            x_node = x_node->arcs[letter];
        } else {
            return 0;
        }
    }
    return x_node->usage;
}

// Очистка бора
void clean_trie(node *tr_ent) {
    for (int i = 0; i < ALPHABET_LEN; i++) {
        if (tr_ent->arcs[i]) {
            clean_trie(tr_ent->arcs[i]);
        }
    }
    free(tr_ent->arcs);
    free(tr_ent);
}

long calc_hash(char *str) {
    long hash = *str;
    size_t length = strlen(str);
    for(size_t i = 0; i < length; i++) {
        hash = (hash << 2) + *str;
        str++;
    }
    return hash;
}

void handle(node *tr_ent, char *input) {
    switch (calc_hash(input)) {
        case INSERT:
            scanf("%s", input);
            if (!lookup(tr_ent, input)) {
                insert(tr_ent, input);
            }
            break;
        
        case DELETE:
            scanf("%s", input);
            delete(tr_ent, input);
            break;
        
        case PREFIX:
            scanf("%s", input);
            printf("%i ", prefix(tr_ent, input));
            break;

        default:
            break;
    }
}

int main(int argc, char **argv) {
    char *input = (char *)malloc((STR_LEN + 1) * sizeof(char));
    node *trie = init_node();
    scanf("%s", input);

    while(strcmp(input, "END")) {
        handle(trie, input);
        scanf("%s", input);
    }

    clean_trie(trie);
    free(input);
    return 0;
}