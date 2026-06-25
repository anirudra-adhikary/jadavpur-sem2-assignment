#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *arr;
    int top;
    int size;
} Stack;

int main() {
    int n, size, choice, stackNo, value;

    printf("Enter number of stacks: ");
    scanf("%d", &n);

    Stack *stacks = (Stack *)malloc(n * sizeof(Stack));

    for (int i = 0; i < n; i++) {
        printf("Enter size of Stack %d: ", i + 1);
        scanf("%d", &size);

        stacks[i].arr = (int *)malloc(size * sizeof(int));
        stacks[i].size = size;
        stacks[i].top = -1;
    }

    while (1) {
        printf("\n--- N Stacks Menu ---\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 5)
            break;

        printf("Enter stack number (1-%d): ", n);
        scanf("%d", &stackNo);

        if (stackNo < 1 || stackNo > n) {
            printf("Invalid stack number\n");
            continue;
        }

        Stack *s = &stacks[stackNo - 1];

        switch (choice) {
            case 1:
                if (s->top == s->size - 1) {
                    printf("Stack Overflow\n");
                } else {
                    printf("Enter value: ");
                    scanf("%d", &value);
                    s->arr[++s->top] = value;
                    printf("%d pushed into Stack %d\n", value, stackNo);
                }
                break;

            case 2:
                if (s->top == -1) {
                    printf("Stack Underflow\n");
                } else {
                    printf("Popped element: %d\n", s->arr[s->top--]);
                }
                break;

            case 3:
                if (s->top == -1) {
                    printf("Stack is empty\n");
                } else {
                    printf("Top element: %d\n", s->arr[s->top]);
                }
                break;

            case 4:
                if (s->top == -1) {
                    printf("Stack is empty\n");
                } else {
                    printf("Stack %d elements: ", stackNo);
                    for (int i = s->top; i >= 0; i--)
                        printf("%d ", s->arr[i]);
                    printf("\n");
                }
                break;

            default:
                printf("Invalid choice\n");
        }
    }

    for (int i = 0; i < n; i++)
        free(stacks[i].arr);

    free(stacks);

    return 0;
}