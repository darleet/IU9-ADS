#include <stdio.h>

unsigned long binsearch(unsigned long nel, int (*compare)(unsigned long i)) {
    unsigned long left_border = 0;
    unsigned long right_border = nel - 1;
    while (left_border < right_border) {
        unsigned long median = (left_border + right_border) / 2;
        char result = compare(median);
        if (result == 0) {
            return median;
        } else if (result > 0) {
            right_border = median - 1;
        } else {
            left_border = median + 1;
        }
    }
    if (compare(left_border) == 0) {
        return left_border;
    }
    return nel;
}

int arr[10] = {1, 5, 7, 8, 12, 13, 17, 18, 20, 22};
int x = 1;

int cmpfunc(unsigned long i) {
    if (arr[i] < x) return -1;
    if (x == arr[i]) return 0;
    return 1;
}

int main(int argc, char **argv) {
    unsigned long a = binsearch(10, cmpfunc);
    printf("%lu", a);
    return 0;
}