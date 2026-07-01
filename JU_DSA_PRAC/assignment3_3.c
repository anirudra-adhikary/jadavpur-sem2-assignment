#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

int stack[MAX];
int top = -1;

void push(int value) {
    if (top < MAX - 1)
        stack[++top] = value;
}

int pop() {
    return stack[top--];
}

int main() {
    FILE *fp;
    int num;

    fp = fopen("numbers.txt", "r");

    if (fp == NULL) {
        printf("Unable to open file\n");
        return 1;
    }

    while (fscanf(fp, "%d", &num) == 1)
        push(num);

    fclose(fp);

    printf("Integers in reverse order:\n");

    while (top != -1)
        printf("%d ", pop());

    printf("\n");

    return 0;
}