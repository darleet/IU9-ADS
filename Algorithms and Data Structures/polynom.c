#include <stdio.h>

int main(int argc, char **argv)
{
    int n;
    long long a, x;
    scanf("%i%lld%lld", &n, &x, &a);

    long long expr_value = a;
    long long der_value = a * n;

    for (int i = 1; i < n; i++) {
        scanf("%lld", &a);
        expr_value = (expr_value * x) + a;
        der_value = (der_value * x) + a * (n - i);
    }
    
    scanf("%lld", &a);
    expr_value = (expr_value * x) + a;
    printf("%lld %lld", expr_value, der_value);
    return 0;
}