#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
} Node;

Node *head = NULL;

Node* createNode(int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void createList() {
    int n, x;
    printf("Enter number of nodes: ");
    scanf("%d", &n);

    head = NULL;

    for(int i = 0; i < n; i++) {
        printf("Enter data: ");
        scanf("%d", &x);

        Node *newNode = createNode(x);

        if(head == NULL)
            head = newNode;
        else {
            Node *temp = head;
            while(temp->next)
                temp = temp->next;

            temp->next = newNode;
            newNode->prev = temp;
        }
    }
}

void display() {
    Node *temp = head;

    if(head == NULL) {
        printf("List Empty\n");
        return;
    }

    while(temp) {
        printf("%d<->", temp->data);
        temp = temp->next;
    }
    printf("null\n");
}

void insertFront(int data) {
    Node *newNode = createNode(data);

    newNode->next = head;

    if(head)
        head->prev = newNode;

    head = newNode;
}

void insertEnd(int data) {
    Node *newNode = createNode(data);

    if(head == NULL) {
        head = newNode;
        return;
    }

    Node *temp = head;

    while(temp->next)
        temp = temp->next;

    temp->next = newNode;
    newNode->prev = temp;
}

Node* getKthNode(int k) {
    Node *temp = head;
    int count = 1;

    while(temp && count < k) {
        temp = temp->next;
        count++;
    }

    return temp;
}

void insertAfterK(int k, int data) {
    Node *temp = getKthNode(k);

    if(temp == NULL) {
        printf("Invalid Position\n");
        return;
    }

    Node *newNode = createNode(data);

    newNode->next = temp->next;
    newNode->prev = temp;

    if(temp->next)
        temp->next->prev = newNode;

    temp->next = newNode;
}

void insertAfterValue(int value, int data) {
    Node *temp = head;

    while(temp && temp->data != value)
        temp = temp->next;

    if(temp == NULL) {
        printf("Value not found\n");
        return;
    }

    Node *newNode = createNode(data);

    newNode->next = temp->next;
    newNode->prev = temp;

    if(temp->next)
        temp->next->prev = newNode;

    temp->next = newNode;
}


void insertBeforeK(int k, int data) {

    if(k == 1) {
        insertFront(data);
        return;
    }

    Node *temp = getKthNode(k);

    if(temp == NULL) {
        printf("Invalid Position\n");
        return;
    }

    Node *newNode = createNode(data);

    newNode->prev = temp->prev;
    newNode->next = temp;

    temp->prev->next = newNode;
    temp->prev = newNode;
}

void insertBeforeValue(int value, int data) {

    Node *temp = head;

    while(temp && temp->data != value)
        temp = temp->next;

    if(temp == NULL) {
        printf("Value not found\n");
        return;
    }

    if(temp == head) {
        insertFront(data);
        return;
    }

    Node *newNode = createNode(data);

    newNode->prev = temp->prev;
    newNode->next = temp;

    temp->prev->next = newNode;
    temp->prev = newNode;
}

void deleteFirst() {

    if(head == NULL)
        return;

    Node *temp = head;

    head = head->next;

    if(head)
        head->prev = NULL;

    free(temp);
}

void deleteLast() {

    if(head == NULL)
        return;

    if(head->next == NULL) {
        free(head);
        head = NULL;
        return;
    }

    Node *temp = head;

    while(temp->next)
        temp = temp->next;

    temp->prev->next = NULL;

    free(temp);
}

void deleteKth(int k) {

    Node *temp = getKthNode(k);

    if(temp == NULL) {
        printf("Invalid Position\n");
        return;
    }

    if(temp == head) {
        deleteFirst();
        return;
    }

    if(temp->next)
        temp->next->prev = temp->prev;

    temp->prev->next = temp->next;

    free(temp);
}

void deleteAfterK(int k) {

    Node *temp = getKthNode(k);

    if(temp == NULL || temp->next == NULL) {
        printf("Deletion not possible\n");
        return;
    }

    Node *del = temp->next;

    temp->next = del->next;

    if(del->next)
        del->next->prev = temp;

    free(del);
}

void deleteBeforeK(int k) {

    if(k <= 1) {
        printf("Deletion not possible\n");
        return;
    }

    Node *temp = getKthNode(k);

    if(temp == NULL || temp->prev == NULL) {
        printf("Deletion not possible\n");
        return;
    }

    Node *del = temp->prev;

    if(del == head) {
        deleteFirst();
        return;
    }

    del->prev->next = temp;
    temp->prev = del->prev;

    free(del);
}


void deleteValue(int value) {

    Node *temp = head;

    while(temp && temp->data != value)
        temp = temp->next;

    if(temp == NULL) {
        printf("Value not found\n");
        return;
    }

    if(temp == head) {
        deleteFirst();
        return;
    }

    if(temp->next)
        temp->next->prev = temp->prev;

    temp->prev->next = temp->next;

    free(temp);
}

void reverseList() {

    Node *curr = head;
    Node *temp = NULL;

    while(curr) {
        temp = curr->prev;
        curr->prev = curr->next;
        curr->next = temp;
        curr = curr->prev;
    }

    if(temp)
        head = temp->prev;
}

int main() {

    int choice, data, k, value;

    while(1) {

        printf("\n------ MENU ------\n");
        printf("1. Create List\n");
        printf("2. Display List\n");
        printf("3. Insert Front\n");
        printf("4. Insert End\n");
        printf("5. Insert After Kth Node\n");
        printf("6. Insert After Value\n");
        printf("7. Insert Before Kth Node\n");
        printf("8. Insert Before Value\n");
        printf("9. Delete First\n");
        printf("10. Delete Last\n");
        printf("11. Delete After Kth Node\n");
        printf("12. Delete Before Kth Node\n");
        printf("13. Delete Kth Node\n");
        printf("14. Delete By Value\n");
        printf("15. Reverse List\n");
        printf("16. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {

        case 1:
            createList();
            break;

        case 2:
            display();
            break;

        case 3:
            scanf("%d", &data);
            insertFront(data);
            break;

        case 4:
            scanf("%d", &data);
            insertEnd(data);
            break;

        case 5:
            scanf("%d%d", &k, &data);
            insertAfterK(k, data);
            break;

        case 6:
            scanf("%d%d", &value, &data);
            insertAfterValue(value, data);
            break;

        case 7:
            scanf("%d%d", &k, &data);
            insertBeforeK(k, data);
            break;

        case 8:
            scanf("%d%d", &value, &data);
            insertBeforeValue(value, data);
            break;

        case 9:
            deleteFirst();
            break;

        case 10:
            deleteLast();
            break;

        case 11:
            scanf("%d", &k);
            deleteAfterK(k);
            break;

        case 12:
            scanf("%d", &k);
            deleteBeforeK(k);
            break;

        case 13:
            scanf("%d", &k);
            deleteKth(k);
            break;

        case 14:
            scanf("%d", &value);
            deleteValue(value);
            break;

        case 15:
            reverseList();
            break;

        case 16:
            exit(0);

        default:
            printf("Invalid Choice\n");
        }
    }
}