#include <stdio.h>

int main(int argc, char **argv)
{
    int n;
    long a, x;
    scanf("%d%ld%ld", &n, &x, &a);

    long expr_value = a;
    long der_value = a * n;

    for (int i = 1; i < n; i++) {
        scanf("%ld", &a);
        expr_value = (expr_value * x) + a;
        der_value = (der_value * x) + a * (n - i);
    }
    
    scanf("%ld", &a);
    expr_value = (expr_value * x) + a;
    printf("%ld %ld", expr_value, der_value);
    return 0;
}