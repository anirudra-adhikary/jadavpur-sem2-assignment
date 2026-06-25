#include <stdio.h>
#include <stdbool.h>

#define MAX 100

typedef struct {
    int arr[MAX];
    int top;
} Stack;

bool areEqual(Stack s1, Stack s2) {
    if (s1.top != s2.top)
        return false;

    for (int i = 0; i <= s1.top; i++) {
        if (s1.arr[i] != s2.arr[i])
            return false;
    }

    return true;
}

int main() {
    Stack s1, s2;
    int n1, n2;

    s1.top = -1;
    s2.top = -1;

    printf("Enter number of elements in Stack 1: ");
    scanf("%d", &n1);

    printf("Enter elements of Stack 1:\n");
    for (int i = 0; i < n1; i++) {
        scanf("%d", &s1.arr[++s1.top]);
    }

    printf("Enter number of elements in Stack 2: ");
    scanf("%d", &n2);

    printf("Enter elements of Stack 2:\n");
    for (int i = 0; i < n2; i++) {
        scanf("%d", &s2.arr[++s2.top]);
    }

    if (areEqual(s1, s2))
        printf("Stacks are equal\n");
    else
        printf("Stacks are not equal\n");

    return 0;
}