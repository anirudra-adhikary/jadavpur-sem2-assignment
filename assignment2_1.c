#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;


struct Node* head1 = NULL;
struct Node* head2 = NULL;

Node* createNode(int data) {
    Node* newNode = (Node *)malloc(sizeof(Node));

    if(newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void printList(Node *head) {

    if(head == NULL) {
        printf("List is empty\n");
        return;
    }

    Node* temp = head;
    
    while(temp != NULL) {
        printf("%d", temp->data);
        printf("->");
        temp = temp->next;
    }

    printf("NULL\n");
}

void insertFront(Node** head, int data) {
    Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

void insertEnd(Node** head, int data) {
    Node* newNode = createNode(data);
    if(*head == NULL) {
        *head = newNode;
        return;
    }
    Node *temp = *head;
    while(temp->next != NULL)
        temp = temp->next;
    temp->next = newNode;
}

void insertAfterK(Node** head, int k, int data) {

    if(*head == NULL || k <= 0) {
        printf("Invalid k\n");
        return;
    }

    Node *temp = *head;
    while(temp != NULL && k > 1)
    {
        temp = temp->next;
        k--;
    }

    if(temp == NULL) {
        printf("Invalid k\n");
        return;
    }

    Node *newNode = createNode(data);
    newNode->next = temp->next;
    temp->next = newNode;
}

void insertAfterValue(Node** head, int value, int data) {

    Node* temp = *head;

    while(temp != NULL && temp->data != value)
        temp = temp->next;

    if(temp == NULL) {
        printf("Value not found\n");
        return;
    }

    Node* newNode = createNode(data);

    newNode->next = temp->next;
    temp->next = newNode;
}

void insertBeforeK(Node** head, int k, int data) {

    if(k <= 1) {
        insertFront(head, data);
        return;
    }

    Node* temp = *head;
    int count = 1;

    while(temp != NULL && count < k - 1) {
        temp = temp->next;
        count++;
    }

    if(temp == NULL) {
        printf("Invalid k\n");
        return;
    }

    Node* newNode = createNode(data);

    newNode->next = temp->next;
    temp->next = newNode;
}

void insertBeforeValue(Node** head, int value, int data) {

    if(*head == NULL)
        return;

    if((*head)->data == value) {

        insertFront(head, data);
        return;
    }

    Node* temp = *head;

    while(temp->next != NULL &&
          temp->next->data != value)
        temp = temp->next;

    if(temp->next == NULL) {

        printf("Value not found\n");
        return;
    }

    Node* newNode = createNode(data);

    newNode->next = temp->next;
    temp->next = newNode;
}

void deleteFirst(Node** head) {

    if(*head == NULL) {
        printf("List empty\n");
        return;
    }

    Node* temp = *head;
    *head = (*head)->next;
    free(temp);
}

void deleteLast(Node** head) {

    if(*head == NULL)
        return;

    if((*head)->next == NULL) {

        free(*head);
        *head = NULL;
        return;
    }

    Node* temp = *head;

    while(temp->next->next != NULL)
        temp = temp->next;

    free(temp->next);

    temp->next = NULL;
}

void deleteAfterK(Node** head, int k) {

    Node* temp = *head;
    int count = 1;

    while(temp != NULL &&
          count < k) {

        temp = temp->next;
        count++;
    }

    if(temp == NULL ||
       temp->next == NULL) {

        printf("Deletion not possible\n");
        return;
    }

    Node* del = temp->next;

    temp->next = del->next;

    free(del);
}

void deleteBeforeK(Node** head, int k) {

    if(k <= 2 || *head == NULL)
        return;

    if(k == 3) {
        deleteFirst(head);
        return;
    }

    Node* temp = *head;
    int count = 1;

    while(temp->next != NULL && temp->next->next != NULL && count < k - 3) {
        temp = temp->next;
        count++;
    }

    if(temp->next == NULL || temp->next->next == NULL) {
        printf("Deletion not possible\n");
        return;
    }

    Node* del = temp->next;
    temp->next = del->next;
    free(del);
}

void deleteKth(Node** head, int k) {

    if(*head == NULL)
        return;

    if(k == 1) {
        deleteFirst(head);
        return;
    }

    Node* temp = *head;
    int count = 1;

    while(temp->next != NULL && count < k - 1) {
        temp = temp->next;
        count++;
    }

    if(temp->next == NULL) {

        printf("Invalid k\n");
        return;
    }

    Node* del = temp->next;
    temp->next = del->next;
    free(del);
}


void deleteValue(Node** head,
                 int value) {

    if(*head == NULL)
        return;

    if((*head)->data == value) {

        deleteFirst(head);
        return;
    }

    Node* temp = *head;

    while(temp->next != NULL &&
          temp->next->data != value)
        temp = temp->next;

    if(temp->next == NULL) {

        printf("Value not found\n");
        return;
    }

    Node* del = temp->next;

    temp->next = del->next;

    free(del);
}

/* Reverse List */
void reverseList(Node** head) {

    Node* prev = NULL;
    Node* curr = *head;
    Node* next = NULL;

    while(curr != NULL) {

        next = curr->next;

        curr->next = prev;

        prev = curr;
        curr = next;
    }

    *head = prev;
}

/* Sort List */
void sortList(Node** head) {

    if(*head == NULL)
        return;

    Node* i;
    Node* j;

    int temp;

    for(i = *head;
        i != NULL;
        i = i->next) {

        for(j = i->next;
            j != NULL;
            j = j->next) {

            if(i->data > j->data) {

                temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}

/* Search Element */
void searchElement(Node* head,
                   int key) {

    int pos = 1;

    while(head != NULL) {

        if(head->data == key) {

            printf("Found at position %d\n",
                   pos);

            return;
        }

        head = head->next;
        pos++;
    }

    printf("Not found\n");
}

Node* mergeLists(Node* h1,
                 Node* h2) {


    sortList(&h1);
    sortList(&h2);

    Node dummy;
    Node* tail = &dummy;

    dummy.next = NULL;

    while(h1 != NULL &&
          h2 != NULL) {

        if(h1->data < h2->data) {

            tail->next = h1;
            h1 = h1->next;
        }

        else {

            tail->next = h2;
            h2 = h2->next;
        }

        tail = tail->next;
    }

    if(h1 != NULL)
        tail->next = h1;

    else
        tail->next = h2;

    return dummy.next;
}

/* Concatenate Lists */
void concatenate(Node** h1,
                 Node* h2) {

    if(*h1 == NULL) {

        *h1 = h2;
        return;
    }

    Node* temp = *h1;

    while(temp->next != NULL)
        temp = temp->next;

    temp->next = h2;
}

/* Compare Lists */
int areEqual(Node* h1,
             Node* h2) {

    while(h1 != NULL &&
          h2 != NULL) {

        if(h1->data != h2->data)
            return 0;

        h1 = h1->next;
        h2 = h2->next;
    }

    return (h1 == NULL &&
            h2 == NULL);
}


void createList(Node **head) {
    int n, data;
    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        printf("Enter node %d: ", (i+1));
        scanf("%d", &data);
        insertEnd(head, data);
    }
}

void freeList(Node** head) {
    Node *temp;
    while(*head != NULL) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

int main()
{
    int choice;
    int data;
    int k;
    int value;

    while(1) {
        
        printf("\n____________________ LINKED LIST ____________________\n");

        printf("1. Create List\n");
        printf("2. Print List\n");
        printf("3. Insert Front\n");
        printf("4. Insert End\n");
        printf("5. Insert After kth Node\n");
        printf("6. Insert After a given value:\n");
        printf("7. Insert Before kth Node\n");
        printf("8. Insert Before Value\n");
        printf("9. Delete First\n");
        printf("10. Delete Last\n");
        printf("11. Delete After kth Node\n");
        printf("12. Delete Before kth Node\n");
        printf("13. Delete kth Node\n");
        printf("14. Delete by Value\n");
        printf("15. Reverse List\n");
        printf("16. Sort List\n");
        printf("17. Search Element\n");
        printf("18. Merge Two Sorted Lists\n");
        printf("19. Concatenate Two Lists\n");
        printf("20. Compare Two Lists\n");
        printf("0. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                createList(&head1);
                break;
            case 2:
                printList(head1);
                break;
            case 3:
                printf("Enter data: ");
                scanf("%d", &data);
                insertFront(&head1, data);
                break;
            case 4:
                printf("Enter data: ");
                scanf("%d", &data);
                insertEnd(&head1, data);
                break;
            case 5:
                printf("Insert k: ");
                scanf("%d", &k);
                printf("Insert data: ");
                scanf("%d", &data);
                insertAfterK(&head1, k, data);
                break;
            case 6:
                printf("Enter value: ");
                scanf("%d", &value);
                printf("Enter data: ");
                scanf("%d", &data);
                insertAfterValue(&head1, value, data);
                break;
            case 7:
                printf("Enter k: ");
                scanf("%d", &k);
                printf("Enter data: ");
                scanf("%d", &data);
                insertBeforeK(&head1, k, data);
                break;
            case 8:
                printf("Enter value: ");
                scanf("%d",&value);
                printf("Enter data: ");
                scanf("%d", &data);
                insertBeforeValue(&head1, value, data);
                break;
            case 9:
                deleteFirst(&head1);
                break;
            case 10:
                deleteLast(&head1);
                break;
            case 11:
                printf("Enter k: ");
                scanf("%d", &k);
                deleteAfterK(&head1, k);
                break;
            case 12:
                printf("Enter k: ");
                scanf("%d", &k);
                deleteBeforeK(&head1, k);
                break;
            case 13:
                printf("Enter k: ");
                scanf("%d", &k);
                deleteKth(&head1, k);
                break;
            case 14:
                printf("Enter value: ");
                scanf("%d", &value);
                deleteValue(&head1, value);
                break;
            case 15:
                reverseList(&head1);
                break;
            case 16:
                sortList(&head1);
                break;
            case 17:
                printf("Enter element: ");
                scanf("%d", &data);
                searchElement(head1, data);
                break;
            case 18:
                freeList(&head2);
                printf("Create List 2:\n");
                createList(&head2);
                head1 = mergeLists(head1, head2);
                printf("Merged List:\n");
                printList(head1);
                break;
            case 19:
                freeList(&head2);
                printf("Create List 2:\n");
                createList(&head2);
                concatenate(&head1, head2);
                printf("Concatenated List:\n");
                printList(head1);
                break;
            case 20:
                freeList(&head2);
                printf("Create List 2:\n");
                createList(&head2);
                if(areEqual(head1, head2))
                    printf("Lists are Equal\n");
                else
                    printf("Lists are Not Equal\n");
                break;
            case 0:
                freeList(&head1);
                freeList(&head2);
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
}