#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        // Παιδί
        printf("Είμαι το παιδί με PID = %d και θα εκτελέσω την ls\n", getpid());
        execlp("ls", "ls", NULL); // Τρέχει την εντολή ls

        // Αν φτάσουμε εδώ, σημαίνει ότι η execlp απέτυχε
        perror("execlp failed");
        exit(1);
    } else {
        // Γονέας
        printf("Είμαι ο γονέας με PID = %d, παιδί PID = %d\n", getpid(), pid);
        wait(NULL); // Περιμένει να τελειώσει το παιδί
        printf("Ο γονέας τελείωσε μετά το παιδί\n");
    }

    return 0;
}
