#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed\n");
        return 1;
    }

    if (pid == 0) {
        // Child Process
        printf("Child Process:\n");
        printf("PID = %d\n", getpid());
        printf("Parent PID = %d\n", getppid());

        exit(25); // Child exits with status 25
    }
    else {
        // Parent Process
        int status;

        wait(&status);

        printf("\nParent Process:\n");
        printf("PID = %d\n", getpid());
        printf("Parent PID = %d\n", getppid());

        if (WIFEXITED(status)) {
            printf("Child Exit Status = %d\n",
                   WEXITSTATUS(status));
        }
    }

    return 0;
}