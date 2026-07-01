#include <stdio.h>
#include <stdlib.h>

#define PRIORITY 5

struct Node {
    int data;
    struct Node *next;
};

struct Node *front[PRIORITY] = {NULL};
struct Node *rear[PRIORITY] = {NULL};

void insert(int data, int priority) {
    if (priority >= PRIORITY) {
        printf("Invalid Priority\n");
        return;
    }

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;

    if (front[priority] == NULL) {
        front[priority] = rear[priority] = newNode;
    } else {
        rear[priority]->next = newNode;
        rear[priority] = newNode;
    }
}

void delete() {
    for (int i = 0; i < PRIORITY; i++) {
        if (front[i] != NULL) {
            struct Node *temp = front[i];

            printf("Deleted: %d\n", temp->data);

            front[i] = front[i]->next;

            if (front[i] == NULL)
                rear[i] = NULL;

            free(temp);
            return;
        }
    }

    printf("Queue Empty\n");
}

void display() {
    for (int i = 0; i < PRIORITY; i++) {
        printf("Priority %d: ", i);

        struct Node *temp = front[i];

        while (temp != NULL) {
            printf("%d ", temp->data);
            temp = temp->next;
        }

        printf("\n");
    }
}

int main() {
    insert(10,2);
    insert(20,0);
    insert(30,1);
    insert(40,0);

    display();

    delete();

    display();

    return 0;
}