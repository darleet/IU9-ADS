#include <stdio.h>

int main(int argc, char **argv) {

    int lines, columns;
    scanf("%i%i", &lines, &columns);

    int mas[lines][columns];

    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++) {
            scanf("%i", &mas[i][j]);
        }
    }

    int mas_values[columns];
    int mas_indices[columns];

    for (int i = 0; i < columns; i++) mas_indices[i] = -1;
    // Коды: 
    // -2 - записано маленькое число
    // -1 - не было записано числа

    for (int i = 0; i < lines; i++) {
        int max_el = mas[i][0];
        int max_ind = 0;
        if (mas_indices[0] != -1 && max_el < mas_values[0]) {
            mas_indices[0] = -2;
            mas_values[0] = max_el;
        } else if (mas_indices[0] == -1) {
            mas_indices[0] = -2;
            mas_values[0] = max_el;
        }

        for (int j = 1; j < columns; j++){
            int el = mas[i][j];
            if (mas_indices[j] != -1 && el < mas_values[j]) {
                mas_indices[j] = -2;
                mas_values[j] = el;
            } else if (mas_indices[j] == -1) {
                mas_indices[j] = -2;
                mas_values[j] = el;
            }
            if (el > max_el) {
                max_ind = j;
                max_el = el;
            }
        }

        if (mas_indices[max_ind] == -1) {
            mas_indices[max_ind] = i;
            mas_values[max_ind] = max_el;
        } else if (mas_indices[max_ind] == -2 && max_el <= mas_values[max_ind]) {
            mas_indices[max_ind] = i;
            mas_values[max_ind] = max_el;
        }
    }

    int completed = 0;

    for (int i = 0; i < columns; i++) {
        if (mas_indices[i] >= 0) {
            printf("%i %i", mas_indices[i], i);
            completed = 1;
            break;
        }
    }

    if (!completed) printf("%s", "none");
    return 0;

}