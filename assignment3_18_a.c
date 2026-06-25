#include <stdio.h>

#define MAX 100

typedef struct {
    int data;
    int priority;
} Node;

Node pq[MAX];
int size = 0;

void insert(int data, int priority) {
    if (size == MAX) {
        printf("Queue Overflow\n");
        return;
    }

    int i = size - 1;

    while (i >= 0 && pq[i].priority > priority) {
        pq[i + 1] = pq[i];
        i--;
    }

    pq[i + 1].data = data;
    pq[i + 1].priority = priority;
    size++;
}

void delete() {
    if (size == 0) {
        printf("Queue Underflow\n");
        return;
    }

    printf("Deleted: %d\n", pq[0].data);

    for (int i = 1; i < size; i++)
        pq[i - 1] = pq[i];

    size--;
}

void display() {
    for (int i = 0; i < size; i++)
        printf("%d(P%d) ", pq[i].data, pq[i].priority);
    printf("\n");
}

int main() {
    insert(10, 2);
    insert(20, 1);
    insert(30, 3);

    display();

    delete();

    display();

    return 0;
}