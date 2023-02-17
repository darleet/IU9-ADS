#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1000

// Хэш-коды команд

#define ASSIGN 360890
#define AT 1384

#define hash(i, m) (i % m)

typedef struct list {
    long key;
    long value;
    struct list *next;
} list;

typedef struct hash {
    list **elems;
} hash;

// Инициализация списка
list *init_list() {
    list *new_list = (list *)malloc(sizeof(list));
    return new_list;
}

// Поиск элемента по ключу
list *search_list(list *list_ent, long key) {
    while (list_ent) {
        if (list_ent->key == key) {
            return list_ent;
        }
        list_ent = list_ent->next;
    }
    return NULL;
}

// Вставка нового элемента в список
list *insert_list(list *list_ent, long key, long value) {
    list *new_el = init_list();
    new_el->key = key;
    new_el->value = value;
    new_el->next = list_ent;
    return new_el;
}

// Инициализация хэш-таблицы
hash *init_hash(long m) {
    hash *new_hash = (hash *)malloc(sizeof(hash));
    new_hash->elems = (list **)calloc(m, sizeof(list *));
    return new_hash;
}

// Изменение значения в хэш-таблице
void assign_hash(hash *hash_ent, long key, long value, long m) {
    list *list_ent = hash_ent->elems[hash(key, m)];
    list *list_elem = search_list(list_ent, key);
    if (!list_elem) {
        hash_ent->elems[hash(key, m)] = insert_list(list_ent, key, value);
    } else {
        list_elem->value = value;
    }
}

// Поиск значения в хэш-таблице
long at_hash(hash *hash_ent, long key, long m) {
    list *list_ent = hash_ent->elems[hash(key, m)];
    list *list_elem = search_list(list_ent, key);
    if (list_elem) {
        return list_elem->value;
    }
    return 0;
}

// Очистка хэш-таблицы
void clean_hash(hash *hash_ent, long m) {
    for (int i = 0; i < m; i++) {
        list *list_ent = hash_ent->elems[i];
        while (list_ent) {
            list *next_el = list_ent->next;
            free(list_ent);
            list_ent = next_el;
        }
    }
    free(hash_ent->elems);
    free(hash_ent);
}

// Получение хэша команд
long cmd_hash(char *str) {
    long hash = *str;
    size_t length = strlen(str);
    for(size_t i = 0; i < length; i++) {
        hash = (hash << 2) + *str;
        str++;
    }
    return hash;
}

// Обработчик команд
void handle(hash *hash_ent, char *input, long m) {
    long i, v;
    switch (cmd_hash(input)) {
        case ASSIGN:
            scanf("%li%li", &i, &v);
            assign_hash(hash_ent, i, v, m);
            break;
        
        case AT:
            scanf("%li", &i);
            printf("%li\n", at_hash(hash_ent, i, m));
            break;

        default:
            break;
    }
}

int main(int argc, char **argv) {
    long m;
    scanf("%li", &m);
    char *input = (char *)malloc(BUFFER_SIZE * sizeof(char));
    scanf("%s", input);
    hash *hash_ent = init_hash(m);

    while (strcmp(input, "END")) {
        handle(hash_ent, input, m);
        scanf("%s", input);
    }

    clean_hash(hash_ent, m);
    free(input);
    return 0;
}