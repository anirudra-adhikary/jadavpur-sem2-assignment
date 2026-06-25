#include <stdio.h>
#include <stdlib.h>

struct Node {
    int coeff;
    int exp;
    struct Node *next;
};

typedef struct Node Node;

Node* createNode(int coeff, int exp) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;
    return newNode;
}

void insertTerm(Node **poly, int coeff, int exp) {
    if (coeff == 0)
        return;

    Node *newNode = createNode(coeff, exp);

    if (*poly == NULL || (*poly)->exp < exp) {
        newNode->next = *poly;
        *poly = newNode;
        return;
    }

    Node *curr = *poly;
    Node *prev = NULL;

    while (curr != NULL && curr->exp > exp) {
        prev = curr;
        curr = curr->next;
    }

    if (curr != NULL && curr->exp == exp) {
        curr->coeff += coeff;
        free(newNode);

        if (curr->coeff == 0) {
            if (prev == NULL)
                *poly = curr->next;
            else
                prev->next = curr->next;

            free(curr);
        }
    }
    else {
        newNode->next = curr;
        prev->next = newNode;
    }
}

Node* createPolynomial() {
    Node *poly = NULL;
    int n, coeff, exp;

    printf("Enter number of terms: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter coefficient and exponent: ");
        scanf("%d%d", &coeff, &exp);
        insertTerm(&poly, coeff, exp);
    }

    return poly;
}

void display(Node *poly) {
    if (poly == NULL) {
        printf("0\n");
        return;
    }

    while (poly != NULL) {
        printf("%dx^%d", poly->coeff, poly->exp);

        if (poly->next != NULL)
            printf(" + ");

        poly = poly->next;
    }
    printf("\n");
}

Node* addPoly(Node *p1, Node *p2) {
    Node *result = NULL;

    while (p1 && p2) {
        if (p1->exp > p2->exp) {
            insertTerm(&result, p1->coeff, p1->exp);
            p1 = p1->next;
        }
        else if (p1->exp < p2->exp) {
            insertTerm(&result, p2->coeff, p2->exp);
            p2 = p2->next;
        }
        else {
            insertTerm(&result,
                       p1->coeff + p2->coeff,
                       p1->exp);
            p1 = p1->next;
            p2 = p2->next;
        }
    }

    while (p1) {
        insertTerm(&result, p1->coeff, p1->exp);
        p1 = p1->next;
    }

    while (p2) {
        insertTerm(&result, p2->coeff, p2->exp);
        p2 = p2->next;
    }

    return result;
}

Node* subtractPoly(Node *p1, Node *p2) {
    Node *result = NULL;

    while (p1 && p2) {
        if (p1->exp > p2->exp) {
            insertTerm(&result, p1->coeff, p1->exp);
            p1 = p1->next;
        }
        else if (p1->exp < p2->exp) {
            insertTerm(&result, -p2->coeff, p2->exp);
            p2 = p2->next;
        }
        else {
            insertTerm(&result,
                       p1->coeff - p2->coeff,
                       p1->exp);
            p1 = p1->next;
            p2 = p2->next;
        }
    }

    while (p1) {
        insertTerm(&result, p1->coeff, p1->exp);
        p1 = p1->next;
    }

    while (p2) {
        insertTerm(&result, -p2->coeff, p2->exp);
        p2 = p2->next;
    }

    return result;
}

Node* multiplyPoly(Node *p1, Node *p2) {
    Node *result = NULL;

    for (Node *i = p1; i != NULL; i = i->next) {
        for (Node *j = p2; j != NULL; j = j->next) {
            insertTerm(
                &result,
                i->coeff * j->coeff,
                i->exp + j->exp
            );
        }
    }

    return result;
}

int main() {
    Node *P1 = NULL, *P2 = NULL, *result = NULL;
    int choice;

    while (1) {
        printf("\n----- POLYNOMIAL MENU -----\n");
        printf("1. Create Polynomial 1\n");
        printf("2. Create Polynomial 2\n");
        printf("3. Display Polynomials\n");
        printf("4. Add\n");
        printf("5. Subtract (P1 - P2)\n");
        printf("6. Multiply\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                P1 = createPolynomial();
                break;

            case 2:
                P2 = createPolynomial();
                break;

            case 3:
                printf("P1 = ");
                display(P1);

                printf("P2 = ");
                display(P2);
                break;

            case 4:
                result = addPoly(P1, P2);
                printf("P1 + P2 = ");
                display(result);
                break;

            case 5:
                result = subtractPoly(P1, P2);
                printf("P1 - P2 = ");
                display(result);
                break;

            case 6:
                result = multiplyPoly(P1, P2);
                printf("P1 * P2 = ");
                display(result);
                break;

            case 7:
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}