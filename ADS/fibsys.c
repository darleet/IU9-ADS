#include <stdio.h>

void fib(unsigned long x) {

    if (x != 0) {
        unsigned long fib_nums[100]; // т.к. ФСС(100) > 2^63
        fib_nums[0] = 1;
        fib_nums[1] = 1;

        int i = 1;

        while (fib_nums[i] <= x) {
            i++;
            fib_nums[i] = fib_nums[i-1] + fib_nums[i-2];
        }

        i--;

        for (i; i > 0; i--) {
            if (fib_nums[i] <= x) {
                printf("%i", 1);
                x -= fib_nums[i];
            } else printf("%i", 0);
        }
    } else printf("%i", 0);
    
}

int main(int argc, char **argv) {

    unsigned long x;
    scanf("%lu", &x);
    fib(x);
    
    return 0;
}