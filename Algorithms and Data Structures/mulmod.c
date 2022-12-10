#include <stdio.h>
#include <math.h>

unsigned long rec(unsigned long b_int, unsigned long a, unsigned long m) {
    unsigned long b_rem = b_int % 2;
    b_int /= 2;

    if (b_int > 0) {
        return (a * b_rem) % m + (2 * (rec(b_int, a, m) % m)) % m;
    } else return a * b_rem;

}

int main(int argc, char **argv)
{
    unsigned long a, b, m;
    scanf("%lu%lu%lu", &a, &b, &m);

    unsigned long mod_result = 0;
    mod_result = rec(b, a, m) % m;

    printf("%lu", mod_result);

    return 0;
}