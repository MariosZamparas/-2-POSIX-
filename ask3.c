// file: parent_child_sum.c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int calc1() {
    int sum = 0;
    for (int i = 1; i <= 100; i++) {
        sum += i;
    }
    return sum;
}

int calc2() {
    int sum = 0;
    for (int i = 101; i <= 200; i++) {
        sum += i;
    }
    return sum;
}

int main() {
    int fd[2]; // fd[0] = read end, fd[1] = write end
    pipe(fd);

    pid_t pid = fork();

    if (pid == 0) {
        // Παιδί
        close(fd[0]); // Δεν διαβάζει
        int child_sum = calc2();
        printf("Computed sum by child process is %d\n", child_sum);
        write(fd[1], &child_sum, sizeof(child_sum));
        close(fd[1]);
        exit(0);
    } else {
        // Γονέας
        close(fd[1]); // Δεν γράφει
        int parent_sum = calc1();
        printf("Computed sum by parent process is %d\n", parent_sum);

        int received;
        read(fd[0], &received, sizeof(received));
        printf("Parent receives value %d from child\n", received);
        printf("The total sum is %d\n", parent_sum + received);

        close(fd[0]);
    }

    return 0;
}
