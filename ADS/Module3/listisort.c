#include <stdio.h>
#include <stdlib.h>

typedef struct Elem {
    struct Elem *prev;
    struct Elem *next;
    int v;
} Elem;

// В сортировке я не сравниваю числа с ограничителем,
// так что он может быть любым.
#define INIT_NUMBER 0

// Инициализация списка
Elem *init_dlist() {
    Elem *dlist = (Elem *)malloc(sizeof(Elem));
    dlist->next = (Elem *)dlist;
    dlist->prev = (Elem *)dlist;
    dlist->v = INIT_NUMBER;
    return dlist;
}

// Вставка элемента после другого элемента
Elem *insert_after(Elem *x, Elem *pivot) {
    Elem *next_el = pivot->next;
    next_el->prev = x;
    pivot->next = x;
    x->next = next_el;
    x->prev = pivot;
    return x;
}

// Перемещение элемента на позицию после другого элемента
void move_after(Elem *x, Elem *pivot) {
    // сначала удалим элемент из кольца
    x->next->prev = x->prev;
    x->prev->next = x->next;
    // затем вставим на нужную позицию
    insert_after(x, pivot);
}

// Очищение списка
void clean_dlist(Elem *dlist) {
    while (dlist->next != dlist) {
        Elem *next_el = dlist->next;
        dlist->prev->next = dlist->next;
        dlist->next->prev = dlist->prev;
        free(dlist);
        dlist = next_el;
    }
    free(dlist);
}

// Сортировка вставками
void isort(Elem *dlist, int n) {
    Elem *x_el = dlist->next;
    while (x_el != dlist) {
        Elem *cmp_el = x_el->prev;
        Elem *next_el = x_el->next;
        while (cmp_el != dlist && cmp_el->v > x_el->v) {
            cmp_el = cmp_el->prev;
        }
        move_after(x_el, cmp_el);
        x_el = next_el;
    }
}

// Вывод списка в консоль
void print_dlist(Elem *dlist) {
    Elem *x_el = dlist->next;
    while (x_el != dlist) {
        printf("%i ", x_el->v);
        x_el = x_el->next;
    }
}

int main(int argc, char **argv) {
    int n;
    scanf("%i", &n);
    Elem *dlist = init_dlist();

    Elem *pivot = dlist;
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%i", &x);
        Elem *x_el = (Elem *)malloc(sizeof(Elem));
        x_el->v = x;
        pivot = insert_after(x_el, pivot);
    }

    isort(dlist, n);
    print_dlist(dlist);
    clean_dlist(dlist);
    return 0;
}