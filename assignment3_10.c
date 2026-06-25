#include <stdio.h>

#define MAXQ 10
#define SIZE 5

int queue[MAXQ][SIZE];
int front[MAXQ], rear[MAXQ];
int n;

void initialize() {
    int i;
    for (i = 0; i < n; i++) {
        front[i] = -1;
        rear[i] = -1;
    }
}

void enqueue(int q, int value) {
    if (rear[q] == SIZE - 1) {
        printf("Queue Overflow\n");
        return;
    }

    if (front[q] == -1)
        front[q] = 0;

    queue[q][++rear[q]] = value;
}

void dequeue(int q) {
    if (front[q] == -1 || front[q] > rear[q]) {
        printf("Queue Underflow\n");
        return;
    }

    printf("Deleted element: %d\n", queue[q][front[q]++]);

    if (front[q] > rear[q])
        front[q] = rear[q] = -1;
}

void display(int q) {
    int i;

    if (front[q] == -1) {
        printf("Queue is empty\n");
        return;
    }

    printf("Queue %d: ", q + 1);

    for (i = front[q]; i <= rear[q]; i++)
        printf("%d ", queue[q][i]);

    printf("\n");
}

int main() {
    int choice, q, value;

    printf("Enter number of queues (1-%d): ", MAXQ);
    scanf("%d", &n);

    if (n < 1 || n > MAXQ) {
        printf("Invalid number of queues.\n");
        return 0;
    }

    initialize();

    while (1) {
        printf("\n1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 4)
            break;

        if (choice >= 1 && choice <= 3) {
            printf("Enter queue number (1-%d): ", n);
            scanf("%d", &q);

            if (q < 1 || q > n) {
                printf("Invalid queue number.\n");
                continue;
            }

            q--;

            switch (choice) {
                case 1:
                    printf("Enter value: ");
                    scanf("%d", &value);
                    enqueue(q, value);
                    break;

                case 2:
                    dequeue(q);
                    break;

                case 3:
                    display(q);
                    break;
            }
        } else {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}