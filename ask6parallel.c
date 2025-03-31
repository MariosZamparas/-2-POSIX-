#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

long long compute_sum(long long start, long long end) {
    long long sum = 0;
    for (long long i = start; i <= end; i++) {
        sum += i;
    }
    return sum;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Χρήση: %s <ακέραιος>\n", argv[0]);
        return 1;
    }

    long long N = atoll(argv[1]);
    int fd1[2], fd2[2];

    pipe(fd1);
    pipe(fd2);

    pid_t pid1 = fork();

    if (pid1 == 0) {
        // Πρώτο παιδί
        close(fd1[0]);
        long long sum1 = compute_sum(1, N / 2);
        write(fd1[1], &sum1, sizeof(sum1));
        close(fd1[1]);
        exit(0);
    }

    pid_t pid2 = fork();

    if (pid2 == 0) {
        // Δεύτερο παιδί
        close(fd2[0]);
        long long sum2 = compute_sum(N / 2 + 1, N);
        write(fd2[1], &sum2, sizeof(sum2));
        close(fd2[1]);
        exit(0);
    }

    // Γονέας
    close(fd1[1]);
    close(fd2[1]);

    long long sum1, sum2;
    read(fd1[0], &sum1, sizeof(sum1));
    read(fd2[0], &sum2, sizeof(sum2));
    close(fd1[0]);
    close(fd2[0]);

    wait(NULL);
    wait(NULL);

    long long total = sum1 + sum2;
    printf("Το συνολικό άθροισμα από 1 έως %lld είναι %lld\n", N, total);

    return 0;
}
