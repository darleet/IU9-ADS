#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 10
#define M 19

// Ключ служебного элемента-ограничителя
#define LIM -1000000000

#define INSERT 400556
#define LOOKUP 416020
#define DELETE 372197
#define RANK 27667

typedef struct Elem {
    long key;
    char *str;
    struct Elem **next;
    long *span;
} Elem;

// Реализация списка с пропусками взята из презентации

// Инициализация списка
Elem *init_slist(int m) {
    Elem *slist = (Elem *)malloc(sizeof(Elem));
    slist->next = (Elem **)calloc(m, sizeof(Elem *));
    slist->span = (long *)calloc(m, sizeof(long));
    slist->key = LIM;
    slist->str = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
    return slist;
}

Elem *succ_slist(Elem *x_el) {
    return x_el->next[0];
}

void skip_slist(Elem *slist, int m, long key, Elem **ptrs) {
    Elem *x_el = slist;
    for (int i = m - 1; i >= 0; i--) {
        while (x_el->next[i] && x_el->next[i]->key < key) {
            x_el = x_el->next[i];
        }
        ptrs[i] = x_el;
    }
}

// Поиск строки по ключу
char *lookup_slist(Elem *slist, int m, long key) {
    Elem **ptrs = (Elem **)malloc(m * sizeof(Elem *));
    skip_slist(slist, m, key, ptrs);
    Elem *x_el = succ_slist(ptrs[0]);
    free(ptrs);
    if (x_el && x_el->key == key) {
        return x_el->str;
    }
    return NULL;
}

// Порядковый номер по ключу
long rank_slist(Elem *slist, int m, long key) {
    if (key != LIM) {
        long rank = 0;
        Elem *x_el = slist;
        // по сути алгоритм как в skip_slist(), но с 
        // задействованной переменной rank для подсчета порядка
        for (int i = m - 1; i >= 0; i--) {
            while (x_el->next[i] && x_el->next[i]->key < key) {
                rank += x_el->span[i];
                x_el = x_el->next[i];
            }
        }
        return rank;
    }
    return -1;
}

// Вставка элемента
void insert_slist(Elem *slist, int m, long key, char *str) {
    Elem **ptrs = (Elem **)malloc(m * sizeof(Elem *));
    skip_slist(slist, m, key, ptrs);
    if (!(ptrs[0]->next[0] && ptrs[0]->next[0]->key == key)) {
        // порядок элемента x
        long x_rank = rank_slist(slist, m, ptrs[0]->key) + 1;
        Elem *x_el = init_slist(m);
        x_el->key = key;
        strcpy(x_el->str, str);
        int r = rand() * 2;
        for (int i = 0; i < m; i++) {
            if (r % 2 == 0) {
                x_el->next[i] = ptrs[i]->next[i];
                ptrs[i]->next[i] = x_el;
                long ptr_rank = rank_slist(slist, m, ptrs[i]->key);
                // расстояние от указателя до элемента x_el
                long dist = x_rank - ptr_rank;
                x_el->span[i] = ptrs[i]->span[i] - dist + 1;
                ptrs[i]->span[i] = dist;
                r /= 2;
            } else {
                x_el->next[i] = NULL;
                ptrs[i]->span[i]++;
            }
        }
    }
    free(ptrs);
}

// Удаление элемента
void delete_slist(Elem *slist, int m, long key) {
    Elem **ptrs = (Elem **)malloc(m * sizeof(Elem *));
    skip_slist(slist, m, key, ptrs);
    Elem *x_el = succ_slist(ptrs[0]);
    if (x_el && x_el->key == key) {
        for (int i = 0; i < m; i++) {
            if (ptrs[i]->next[i] == x_el) {
                ptrs[i]->next[i] = x_el->next[i];
                ptrs[i]->span[i] = ptrs[i]->span[i] + x_el->span[i] - 1;
            } else {
                ptrs[i]->span[i]--;
            }
        }
    }
    free(x_el->next);
    free(x_el->span);
    free(x_el->str);
    free(x_el);
    free(ptrs);
}

void clean_slist(Elem *slist) {
    Elem *x_el = slist;
    while (x_el) {
        Elem *next_el = x_el->next[0];
        free(x_el->span);
        free(x_el->str);
        free(x_el->next);
        free(x_el);
        x_el = next_el;
    }
}

long calc_hash(char *str) {
    long hash = *str;
    int length = strlen(str);
    for(int i = 0; i < length; i++) {
        hash = (hash << 2) + *str;
        str++;
    }
    return hash;
}

void handler(Elem *slist, int m, char *input) {
    long key;
    scanf("%li", &key);
    switch (calc_hash(input)) {
        case INSERT:
            scanf("%s", input);
            insert_slist(slist, m, key, input);
            break;
        
        case LOOKUP:
            printf("%s\n", lookup_slist(slist, m, key));
            break;

        case DELETE:
            delete_slist(slist, m, key);
            break;
        
        case RANK:
            printf("%li\n", rank_slist(slist, m, key));
            break;
        
        default:
            break;
    }
}

int main(int argc, char **argv) {
    Elem *slist = init_slist(M);
    char *input = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
    scanf("%s", input);

    while (strcmp(input, "END")) {
        handler(slist, M, input);
        scanf("%s", input);
    }

    clean_slist(slist);
    free(input);
    return 0;
}