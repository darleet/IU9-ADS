#include <stdio.h>
#include <math.h>

unsigned long long rec(unsigned long long b_int, unsigned long long a, unsigned long long m) {
    unsigned long long b_rem = b_int % 2;
    b_int /= 2;

    if (b_int > 0) {
        return (a * b_rem) % m + (2 * (rec(b_int, a, m) % m)) % m;
    } else return a * b_rem;

}

int main(int argc, char **argv)
{
    unsigned long long a, b, m;
    scanf("%llu%llu%llu", &a, &b, &m);

    unsigned long long mod_result = 0;
    mod_result = rec(b, a, m) % m;

    printf("%llu", mod_result);

    return 0;
}