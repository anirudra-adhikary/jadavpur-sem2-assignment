#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX 100

int stack[MAX];
int top = -1;

void push(int x) {
    stack[++top] = x;
}

int pop() {
    return stack[top--];
}

int main() {
    char postfix[200];
    char *token;

    printf("Enter postfix expression: ");
    fgets(postfix, sizeof(postfix), stdin);

    token = strtok(postfix, " \n");

    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            push(atoi(token));
        } else {
            int b = pop();
            int a = pop();

            switch (token[0]) {
                case '+': push(a + b); break;
                case '-': push(a - b); break;
                case '*': push(a * b); break;
                case '/': push(a / b); break;
                case '%': push(a % b); break;
                case '^': push((int)pow(a, b)); break;
            }
        }

        token = strtok(NULL, " \n");
    }

    printf("Result = %d\n", pop());

    return 0;
}