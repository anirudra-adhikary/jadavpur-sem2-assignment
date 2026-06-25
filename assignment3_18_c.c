#include <stdio.h>

#define PRIORITY 5
#define MAX 10

int pq[PRIORITY][MAX];
int rear[PRIORITY] = {0};

void insert(int data, int priority) {
    if (priority >= PRIORITY) {
        printf("Invalid Priority\n");
        return;
    }

    pq[priority][rear[priority]++] = data;
}

void delete() {
    for (int i = 0; i < PRIORITY; i++) {
        if (rear[i] > 0) {
            printf("Deleted: %d\n", pq[i][0]);

            for (int j = 1; j < rear[i]; j++)
                pq[i][j - 1] = pq[i][j];

            rear[i]--;
            return;
        }
    }

    printf("Queue Empty\n");
}

void display() {
    for (int i = 0; i < PRIORITY; i++) {
        printf("Priority %d: ", i);
        for (int j = 0; j < rear[i]; j++)
            printf("%d ", pq[i][j]);
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