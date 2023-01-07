#include <stdio.h>

void swap(char *elem1, char *elem2, size_t width) {
    for (size_t i = 0; i < width; i++) {
        char temp_elem = *elem1;
        *elem1 = *elem2;
        *elem2 = temp_elem;
        elem1++;
        elem2++;
    }
}

void revarray(void *base, size_t nel, size_t width) {
    for (size_t i = 0; i < nel / 2; i++) {
        char *index1 = (char *)base + width * i;
        char *index2 = (char *)base + (nel * width - width * (i + 1));
        swap(index1, index2, width);
    }
}

int main(int argc, char **argv) {
    long mas[4] = {-1, 2, -34, 4};
    void *p = mas;
    revarray(p, 4, sizeof(long));
    for (int i = 0; i < 4; i++) printf("%li ", mas[i]);
    return 0;
}