#include <stdio.h>

#define MAX 100

int queue[MAX];
int front = 0, rear = -1;

void enqueue(int value) {
    if (rear == MAX - 1) {
        printf("Queue Overflow\n");
        return;
    }
    queue[++rear] = value;
}

void replace(int e, int x) {
    int i;

    for (i = front; i <= rear; i++) {
        if (queue[i] == e)
            queue[i] = x;
    }
}

void display() {
    int i;

    if (front > rear) {
        printf("Queue is empty\n");
        return;
    }

    for (i = front; i <= rear; i++)
        printf("%d ", queue[i]);

    printf("\n");
}

int main() {
    int n, value, e, x, i;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter queue elements:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &value);
        enqueue(value);
    }

    printf("Original Queue: ");
    display();

    printf("Enter element to replace: ");
    scanf("%d", &e);

    printf("Enter new value: ");
    scanf("%d", &x);

    replace(e, x);

    printf("Queue after replacement: ");
    display();

    return 0;
}