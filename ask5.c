#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Χρήση: %s <ακέραιος>\n", argv[0]);
        return 1;
    }

    int num = atoi(argv[1]); // Μετατροπή από string σε int
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        // Παιδί
        if (num % 2 == 0) {
            exit(0); // Άρτιος
        } else {
            exit(1); // Περιττός
        }
    } else {
        // Γονέας
        int status;
        wait(&status);

        if (WIFEXITED(status)) {
            int result = WEXITSTATUS(status);
            printf("Η διεργασία παιδί επέστρεψε: %d\n", result);
            if (result == 0) {
                printf("Ο αριθμός %d είναι άρτιος\n", num);
            } else {
                printf("Ο αριθμός %d είναι περιττός\n", num);
            }
        } else {
            printf("Το παιδί δεν τερμάτισε κανονικά\n");
        }
    }

    return 0;
}
