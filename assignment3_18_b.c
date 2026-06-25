#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    int priority;
    struct Node *next;
};

struct Node *front = NULL;

void insert(int data, int priority) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->priority = priority;
    newNode->next = NULL;

    if (front == NULL || priority < front->priority) {
        newNode->next = front;
        front = newNode;
        return;
    }

    struct Node *temp = front;

    while (temp->next != NULL &&
           temp->next->priority <= priority)
        temp = temp->next;

    newNode->next = temp->next;
    temp->next = newNode;
}

void delete() {
    if (front == NULL) {
        printf("Queue Empty\n");
        return;
    }

    struct Node *temp = front;

    printf("Deleted: %d\n", temp->data);

    front = front->next;

    free(temp);
}

void display() {
    struct Node *temp = front;

    while (temp != NULL) {
        printf("%d(P%d) ", temp->data, temp->priority);
        temp = temp->next;
    }

    printf("\n");
}

int main() {
    insert(10,2);
    insert(20,1);
    insert(30,3);

    display();

    delete();

    display();

    return 0;
}