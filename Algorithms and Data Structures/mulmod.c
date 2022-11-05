#include <stdio.h>
#include <math.h>

int main(int argc, char **argv)
{
    unsigned long long a, b, m, step_result;
    scanf("%llu%llu%llu", &a, &b, &m);
    
    unsigned long long i = 1;
    unsigned long long mod_result = 0;
    int rem;

    while (b > 0) {
        rem = b % 2;
        b = b / 2;
        step_result = (rem % m) * (i % m) * (a % m);
        mod_result += step_result % m;
        i *= 2;
    }

    mod_result %= m;
    printf("%llu", mod_result);
    return 0;
}