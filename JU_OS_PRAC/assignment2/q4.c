#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int isPalindrome(char str[]) {
    int left = 0;
    int right = strlen(str) - 1;

    while (left < right) {
        if (str[left] != str[right])
            return 0;

        left++;
        right--;
    }

    return 1;
}

int main() {
    int p1[2], p2[2];

    pipe(p1); // Parent -> Child
    pipe(p2); // Child -> Parent

    pid_t pid = fork();

    if (pid == 0) {
        // Child Process

        close(p1[1]);
        close(p2[0]);

        char str[100];
        char result[10];

        while (1) {
            read(p1[0], str, sizeof(str));

            if (strcmp(str, "quit") == 0)
                break;

            if (isPalindrome(str))
                strcpy(result, "YES");
            else
                strcpy(result, "NO");

            write(p2[1], result, sizeof(result));
        }

        close(p1[0]);
        close(p2[1]);
    }
    else {
        // Parent Process

        close(p1[0]);
        close(p2[1]);

        char str[100];
        char result[10];

        while (1) {
            printf("Enter string: ");
            scanf("%s", str);

            write(p1[1], str, sizeof(str));

            if (strcmp(str, "quit") == 0)
                break;

            read(p2[0], result, sizeof(result));

            printf("Palindrome? %s\n", result);
        }

        wait(NULL);

        close(p1[1]);
        close(p2[0]);
    }

    return 0;
}