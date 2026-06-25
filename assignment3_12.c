#include <stdio.h>

#define MAX 100

int q1[MAX], q2[MAX];
int f1 = 0, r1 = -1;
int f2 = 0, r2 = -1;

void enqueue(int queue[], int *rear, int value) {
    queue[++(*rear)] = value;
}

int eq() {
    int i, j;

    if ((r1 - f1) != (r2 - f2))
        return 0;

    i = f1;
    j = f2;

    while (i <= r1) {
        if (q1[i] != q2[j])
            return 0;
        i++;
        j++;
    }

    return 1;
}

void display(int queue[], int front, int rear) {
    int i;
    for (i = front; i <= rear; i++)
        printf("%d ", queue[i]);
    printf("\n");
}

int main() {
    int n1, n2, value, i;

    printf("Enter number of elements in Queue 1: ");
    scanf("%d", &n1);

    printf("Enter elements of Queue 1:\n");
    for (i = 0; i < n1; i++) {
        scanf("%d", &value);
        enqueue(q1, &r1, value);
    }

    printf("Enter number of elements in Queue 2: ");
    scanf("%d", &n2);

    printf("Enter elements of Queue 2:\n");
    for (i = 0; i < n2; i++) {
        scanf("%d", &value);
        enqueue(q2, &r2, value);
    }

    printf("\nQueue 1: ");
    display(q1, f1, r1);

    printf("Queue 2: ");
    display(q2, f2, r2);

    if (eq())
        printf("True - Queues are equal.\n");
    else
        printf("False - Queues are not equal.\n");

    return 0;
}