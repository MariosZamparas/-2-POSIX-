#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Χρήση: %s <ακέραιος>\n", argv[0]);
        return 1;
    }

    long long N = atoll(argv[1]);
    long long sum = 0;

    for (long long i = 1; i <= N; i++) {
        sum += i;
    }

    printf("Το άθροισμα από 1 έως %lld είναι %lld\n", N, sum);
    return 0;
}
