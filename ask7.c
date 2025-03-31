#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

long in_circle(long points) {
    long count = 0;
    for (long i = 0; i < points; i++) {
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;
        if (x*x + y*y <= 1.0) count++;
    }
    return count;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Χρήση: %s <αριθμός_σημείων>\n", argv[0]);
        return 1;
    }

    long total = atol(argv[1]);
    long half = total / 2;

    int fd[2];
    pipe(fd);
    pid_t pid = fork();

    if (pid == 0) {
        // Παιδί
        close(fd[0]);
        srand(time(NULL) ^ getpid());
        long count = in_circle(half);
        write(fd[1], &count, sizeof(count));
        close(fd[1]);
        exit(0);
    }

    // Γονέας
    close(fd[1]);
    srand(time(NULL));
    long parent_count = in_circle(half);

    long child_count;
    read(fd[0], &child_count, sizeof(child_count));
    close(fd[0]);

    wait(NULL);

    long total_in = parent_count + child_count;
    double pi = 4.0 * total_in / total;
    printf("Υπολογισμένο π ≈ %.10f\n", pi);

    return 0;
}
