#include <stdio.h>
#include <stdlib.h>

/* Singly Circular Node */
struct SNode
{
    int data;
    struct SNode *next;
};

/* Doubly Circular Node */
struct DNode
{
    int data;
    struct DNode *prev;
    struct DNode *next;
};

/* Function Prototypes */
void pushArray(int n, int k);
void pushSLL(int n, int k);
void pushDLL(int n, int k);

int main()
{
    int choice;
    int n, k;

    while(1)
    {
        printf("\n============ OPTIONS ============\n");
        printf("1. Solve using 2D Array\n");
        printf("2. Solve using Circular Singly Linked List\n");
        printf("3. Solve using Circular Doubly Linked List\n");
        printf("4. Exit\n");
        printf("=====================================\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        if(choice == 4)
        {
            printf("Program Terminated.\n");
            break;
        }

        printf("Enter number of people (n): ");
        scanf("%d", &n);

        printf("Enter skip count (k): ");
        scanf("%d", &k);

        switch(choice)
        {
            case 1:
                pushArray(n, k);
                break;

            case 2:
                pushSLL(n, k);
                break;

            case 3:
                pushDLL(n, k);
                break;

            default:
                printf("Invalid Choice!\n");
        }
    }

    return 0;
}

/* ================================= */
/* JOSEPHUS USING 2D ARRAY */
/* ================================= */

void pushArray(int n, int k)
{
    int people[100][2];
    int alive = n;
    int count = 0;
    int i;

    for(i = 0; i < n; i++)
    {
        people[i][0] = i + 1;
        people[i][1] = 1;
    }

    i = 0;

    printf("\nElimination Order:\n");

    while(alive > 1)
    {
        if(people[i][1] == 1)
        {
            count++;

            if(count == k)
            {
                printf("%d ", people[i][0]);

                people[i][1] = 0;
                alive--;
                count = 0;
            }
        }

        i = (i + 1) % n;
    }

    printf("\n");

    for(i = 0; i < n; i++)
    {
        if(people[i][1] == 1)
        {
            printf("Safe Person = %d\n", people[i][0]);
            break;
        }
    }
}

/* ================================= */
/* JOSEPHUS USING CIRCULAR SLL */
/* ================================= */

void pushSLL(int n, int k)
{
    struct SNode *head = NULL;
    struct SNode *tail = NULL;
    struct SNode *newNode;

    int i;

    for(i = 1; i <= n; i++)
    {
        newNode = (struct SNode*)malloc(sizeof(struct SNode));

        newNode->data = i;

        if(head == NULL)
        {
            head = tail = newNode;
            newNode->next = head;
        }
        else
        {
            tail->next = newNode;
            newNode->next = head;
            tail = newNode;
        }
    }

    struct SNode *curr = head;
    struct SNode *prev = tail;

    printf("\nElimination Order:\n");

    while(curr->next != curr)
    {
        for(i = 1; i < k; i++)
        {
            prev = curr;
            curr = curr->next;
        }

        printf("%d ", curr->data);

        prev->next = curr->next;

        struct SNode *temp = curr;
        curr = curr->next;

        free(temp);
    }

    printf("\nSafe Person = %d\n", curr->data);

    free(curr);
}

/* ================================= */
/* JOSEPHUS USING CIRCULAR DLL */
/* ================================= */

void pushDLL(int n, int k)
{
    struct DNode *head = NULL;
    struct DNode *tail = NULL;
    struct DNode *newNode;

    int i;

    for(i = 1; i <= n; i++)
    {
        newNode = (struct DNode*)malloc(sizeof(struct DNode));

        newNode->data = i;

        if(head == NULL)
        {
            head = tail = newNode;

            newNode->next = newNode;
            newNode->prev = newNode;
        }
        else
        {
            newNode->prev = tail;
            newNode->next = head;

            tail->next = newNode;
            head->prev = newNode;

            tail = newNode;
        }
    }

    struct DNode *curr = head;

    printf("\nElimination Order:\n");

    while(curr->next != curr)
    {
        for(i = 1; i < k; i++)
        {
            curr = curr->next;
        }

        printf("%d ", curr->data);

        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;

        struct DNode *temp = curr;
        curr = curr->next;

        free(temp);
    }

    printf("\nSafe Person = %d\n", curr->data);

    free(curr);
}