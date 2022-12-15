#include <stdio.h>

int main(int argc, char **argv) {

    int mas_size, k;
    scanf("%i", &mas_size);
    int mas[mas_size];

    for (int i = 0; i < mas_size; i++) {
        scanf("%i", &mas[i]);
    }

    scanf("%i", &k);

    int max_sum = 0;
    int step_sum = 0;

    for (int i = 0; i < k; i++) {
        max_sum += mas[i];
    }

    step_sum = max_sum;

    for (int i = k; i < mas_size; i++) {
        step_sum -= mas[i-k];
        step_sum += mas[i];
        if (step_sum > max_sum) max_sum = step_sum;
    }

    printf("%i", max_sum);

    return 0;
}