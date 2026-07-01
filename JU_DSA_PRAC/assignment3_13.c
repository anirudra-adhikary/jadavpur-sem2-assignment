#include <stdio.h>

#define MAX 100

int queue[MAX];
int stack[MAX];
int front = 0, rear = -1, top = -1;

void enqueue(int value) {
    if (rear == MAX - 1) {
        printf("Queue Overflow\n");
        return;
    }
    queue[++rear] = value;
}

int dequeue() {
    if (front > rear) {
        printf("Queue Underflow\n");
        return -1;
    }
    return queue[front++];
}

void push(int value) {
    stack[++top] = value;
}

int pop() {
    return stack[top--];
}

void reverseQueue() {
    while (front <= rear)
        push(dequeue());

    front = 0;
    rear = -1;

    while (top != -1)
        enqueue(pop());
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
    int n, value, i;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter queue elements:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &value);
        enqueue(value);
    }

    printf("Original Queue: ");
    display();

    reverseQueue();

    printf("Reversed Queue: ");
    display();

    return 0;
}