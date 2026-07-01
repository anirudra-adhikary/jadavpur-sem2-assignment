#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int isPrime(int n) {
    if (n < 2)
        return 0;

    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0)
            return 0;
    }

    return 1;
}

int main() {

    for (int i = 0; i < 10; i++) {

        pid_t pid = fork();

        if (pid == 0) {

            int start = i * 100000 + 1;
            int end = (i + 1) * 100000;

            int count = 0;
            int printed = 0;

            printf("\nChild %d (PID = %d)\n",
                   i + 1, getpid());
            printf("Range: %d - %d\n",
                   start, end);

            printf("Sample primes: ");

            for (int j = start; j <= end; j++) {

                if (isPrime(j)) {

                    count++;

                    if (printed < 10) {
                        printf("%d ", j);
                        printed++;
                    }
                }
            }

            printf("\nTotal primes in range = %d\n", count);

            exit(0);
        }
    }

    // Parent waits for all children
    for (int i = 0; i < 10; i++)
        wait(NULL);

    printf("\nParent (PID = %d): All child processes completed.\n",
           getpid());

    return 0;
}