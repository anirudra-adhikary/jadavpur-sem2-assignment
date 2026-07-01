#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

void push(Node **top, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = *top;
    *top = newNode;
}

void pop(Node **top) {
    if (*top == NULL) {
        printf("Stack Underflow\n");
        return;
    }

    Node *temp = *top;
    printf("Popped element: %d\n", temp->data);
    *top = (*top)->next;
    free(temp);
}

void peek(Node *top) {
    if (top == NULL)
        printf("Stack is empty\n");
    else
        printf("Top element: %d\n", top->data);
}

void display(Node *top) {
    if (top == NULL) {
        printf("Stack is empty\n");
        return;
    }

    printf("Stack elements: ");
    while (top != NULL) {
        printf("%d ", top->data);
        top = top->next;
    }
    printf("\n");
}

int main() {
    int n, choice, stackNo, value;

    printf("Enter number of stacks: ");
    scanf("%d", &n);

    Node **stacks = (Node **)malloc(n * sizeof(Node *));

    for (int i = 0; i < n; i++)
        stacks[i] = NULL;

    while (1) {
        printf("\n--- N Dynamic Stacks Menu ---\n");
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

        Node **top = &stacks[stackNo - 1];

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                push(top, value);
                break;

            case 2:
                pop(top);
                break;

            case 3:
                peek(*top);
                break;

            case 4:
                display(*top);
                break;

            default:
                printf("Invalid choice\n");
        }
    }

    for (int i = 0; i < n; i++) {
        while (stacks[i] != NULL) {
            Node *temp = stacks[i];
            stacks[i] = stacks[i]->next;
            free(temp);
        }
    }

    free(stacks);

    return 0;
}