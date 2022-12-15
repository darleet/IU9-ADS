#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, char **argv) {

    signed char *sieve;
    long x;
    scanf("%li", &x);
    if (x < 0) x = -x;

    sieve = (signed char*)malloc((x + 1) * sizeof(signed char));
    // Так как необходимая длина решета может быть очень большой,
    // выделили память под решето в динамической памяти.
    sieve[1] = 1;

    for (int i = 2; i <= x; i++) sieve[i] = 0;
    // 0 - простое число, 1 - составное

    for (int i = 2; i <= x; i++) {
        if (sieve[i] != 1) {
            long j = i * 2;
            while (j <= x) {
                sieve[j] = 1;
                j += i;
            }

        }
    }

    long max_div = -1;

    for (int i = 1; i <= (long)sqrt(x); i++) {
        long m = x / i;
        if (m > max_div && x % m == 0 && sieve[m] == 0) {
            max_div = m;
        } else if (i > max_div && x % i == 0 && sieve[i] == 0) {
            max_div = i;
        }
    }

    printf("%li", max_div);
    return 0;
}