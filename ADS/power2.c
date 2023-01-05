#include <stdio.h>

int comb(long *arr, int index, int n, long sum){
    if ((sum & (sum - 1)) == 0 && sum != 0) {
        return 1;
    }
    if (index + 1 == n) {
        return 0;
    }
    long counter = 0;
    for (int i = index + 1; i < n; i++) {
        counter += comb(arr, i, n, sum + arr[i]);
    }
    return counter;

}

int main(int argc, char *argv) {
    int n;
    int answer = 0;
    scanf("%i", &n);
    long arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%li", &arr[i]);
    }
    for (int i = 0; i < n; i++) {
        answer += comb(arr, i, n, arr[i]);
    }
    printf("%i", answer);
    return 0;
}