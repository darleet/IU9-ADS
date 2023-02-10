#include <stdio.h>

int main(int argc, char **argv) {

    int a[8];

    for (int i = 0; i < 8; i++) {
        scanf("%i", &a[i]);
    }

    short permut_available = 1;

    for (int i = 0; i < 8; i++) {

        int element;
        scanf("%i", &element);
        short el_found = 0;

        for (int i = 0; i < 8; i++) {
            if (element == a[i]) el_found = 1;
        }

        if (!el_found) permut_available = 0;

    }

    if (permut_available) printf("%s", "yes");
    else printf("%s", "no");

    return 0;
}