#include <stdio.h>

int main(int argc, char **argv) {

    unsigned long a = 0;
    unsigned long b = 0;

    int a_size;
    scanf("%i", &a_size);

    for (int i = 0; i < a_size; i++) {
        int input_number;
        scanf("%i", &input_number);
        a = a | (1 << input_number);
    }

    int b_size;
    scanf("%i", &b_size);

    for (int i = 0; i < b_size; i++) {
        int input_number;
        scanf("%i", &input_number);
        b = b | (1 << input_number);
    }

    for (int i = 0; i < 32; i++) {
        int a_bit = a & (1 << i);
        int b_bit = b & (1 << i);
        if (a_bit & b_bit) printf("%i ", i);
    }

    return 0;
}