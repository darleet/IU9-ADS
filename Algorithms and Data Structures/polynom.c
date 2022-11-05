#include <stdio.h>

int main(int argc, char **argv)
{
    int n;
    long a, x;
    scanf("%d%ld%ld", &n, &x, &a);

    long expr_value = 0;
    long der_value = 0;

    for (int i = 0; i < n; i++) {
        expr_value = (expr_value + a) * x;
        der_value = (der_value + a * (n - i)) * x;
        scanf("%ld", &a);
    }

    expr_value += a;
    printf("%ld %ld", expr_value, der_value);
    return 0;
}
    
