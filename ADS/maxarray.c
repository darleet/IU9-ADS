#include <stdio.h>

int cmpfunc(void* a, void* b) {
    int val1 = *(int*)a;
    int val2 = *(int*)b;
    return (val1 - val2);
}

int maxarray(void *base, size_t nel, size_t width,
        int (*compare)(void *a, void *b)) {
    int max_index = 0;
    char *maxp = base;
    char *curp = base;
    for (int i = 1; i < nel; i++) {
        curp += width;
        if (compare(curp, maxp) > 0) {
            max_index = i;
            maxp = curp;
        }
    }
    return max_index;
}

int main(int argc, char **argv) {
    int mas[5] = {1, 4, 7, 15, 2};
    int a = maxarray((void*)mas, 5, sizeof(int), cmpfunc);
    printf("%i", a);
    return 0;
}