#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, char **argv) {

    long x;
    scanf("%li", &x);
    if (x < 0) x = -x;
    long x_sqrt = (long)sqrt(x) + 1;
    char *sieve;
    sieve = (char *)calloc(x_sqrt + 1, sizeof(char));

    // 0 - простое число, 1 - составное.
    sieve[0] = 1;
    sieve[1] = 1;

    for (long i = 2; i <= x_sqrt; i++) {
        if (sieve[i] != 1) {
            long j = i * 2;
            while (j <= x_sqrt) {
                sieve[j] = 1;
                j += i;
            }
        }
    }

    for (long i = 2; i < x_sqrt; i++) {
        if (x == 2 || x <= x_sqrt && sieve[x] == 0) break;
        if (x % i == 0 && sieve[i] == 0) {
            x /= i;
            i = 1;
        }
    }

    free(sieve);
    printf("%li\n", x);
    return 0;
}