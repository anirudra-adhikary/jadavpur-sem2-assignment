#include <stdio.h>

#define MAX 100

int x[MAX], y[MAX];
int fx = 0, rx = -1;
int fy = 0, ry = -1;

void enqueue(int queue[], int *rear, int value) {
    if (*rear == MAX - 1) {
        printf("Queue Overflow\n");
        return;
    }
    queue[++(*rear)] = value;
}

void display(int queue[], int front, int rear) {
    int i;

    if (front > rear) {
        printf("Queue is empty\n");
        return;
    }

    for (i = front; i <= rear; i++)
        printf("%d ", queue[i]);

    printf("\n");
}

void appendQueue() {
    int i;

    if (fx > rx) {
        printf("Queue X is empty\n");
        return;
    }

    for (i = fx; i <= rx; i++) {
        if (ry == MAX - 1) {
            printf("Queue Y Overflow\n");
            return;
        }
        y[++ry] = x[i];
    }

    fx = 0;
    rx = -1;

    printf("Queue X appended to Queue Y.\n");
}

int main() {
    int n, value, i;

    printf("Enter number of elements in Queue X: ");
    scanf("%d", &n);

    printf("Enter elements of Queue X:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &value);
        enqueue(x, &rx, value);
    }

    printf("Enter number of elements in Queue Y: ");
    scanf("%d", &n);

    printf("Enter elements of Queue Y:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &value);
        enqueue(y, &ry, value);
    }

    printf("\nQueue X: ");
    display(x, fx, rx);

    printf("Queue Y: ");
    display(y, fy, ry);

    appendQueue();

    printf("Queue Y after appending Queue X: ");
    display(y, fy, ry);

    return 0;
}