#include<stdio.h>
#include<stdlib.h>

void create(int **arr, int *size) {
    
    int i;

    printf("Enter the number of elements: ");
    scanf("%d", size);

    *arr = (int *)realloc(*arr, (*size) * sizeof(int));

    printf("Enter the elements: ");
    for(i = 0; i < *size; i++)
        scanf("%d", &(*arr)[i]);

}

void display(int *arr, int size) {

    int i;

    if(size == 0) {
        printf("List is empty.\n");
        return;
    }

    printf("Array Elements: ");
    for(i = 0; i < size; i++)
        printf("%d ", arr[i]);

    printf("\n");
}

void count(int size) {
    printf("Total Elements = %d\n", size);
}

void reverse(int arr[], int size) 
{
    int i, temp;

    for(i = 0; i < size/2; i++) 
    {
        temp = arr[i];
        arr[i] = arr[size - i - 1];
        arr[size - i - 1] = temp;    
    }

    printf("Reversal operation successful.\n");
}

void searchElement(int arr[], int size) {

    int key, i, found = 0;

    printf("Enter the element to search: ");
    scanf("%d", &key);

    printf("Indices: ");
    
    for(i = 0; i < size; i++) {

        if(arr[i] == key) {
            printf("%d ", i);
            found = 1;
        }
    }

    if(!found)
        printf("Element not found");


    printf("\n");
}

void indexedElement(int arr[], int size)
{
    int idx;

    printf("Enter index: ");
    scanf("%d", &idx);

    if(idx < 0 || idx >= size)
    {
        printf("Invalid index");
        return;
    }

    printf("Element = %d\n", arr[idx]);
}

void insertElement(int **arr, int *size) {
    
    int pos, value, i;

    printf("Enter position: ");
    scanf("%d", &pos);

    if(pos < 0 || pos > *size) {
        printf("Invalid Position.\n");
        return;
    }

    printf("Enter value: ");
    scanf("%d", &value);

    *arr = (int *)realloc(*arr, (*size + 1) * sizeof(int));

    for(i = *size; i > pos; i--)
        (*arr)[i] = (*arr)[i - 1];

    (*arr)[pos] = value;

    (*size)++;

    printf("Element inserted successfully.\n");
}

void deleteElement(int **arr, int *size) 
{
    int pos, i;

    if(*size == 0) {
        printf("Array is empty.\n");
        return;
    }


    printf("Enter position to delete: ");
    scanf("%d", &pos);

    if(pos < 0 || pos >= *size) {
        printf("Invalid position");
        return;
    }

    for(i = pos; i < *size - 1; i++)
        (*arr)[i] = (*arr)[i + 1];

    (*size)--;

    *arr = (int *)realloc(*arr, (*size) * sizeof(int));

    printf("Element Deleted.\n");
}

void mergeArray(int **arr, int *size) {

    int n, i;
    int *newArr;

    printf("Enter the size of the new array: ");
    scanf("%d", &n);
    
    newArr = (int *)malloc(n * sizeof(int));


    printf("Enter the elements: ");
    for(i = 0; i < n; i++) 
        scanf("%d", &newArr[i]);

    *arr = (int *)realloc(*arr, (*size + n) * sizeof(int));

    for(i = 0; i < n; i++)
        (*arr)[*size + i] = newArr[i];

    *size += n;

    free(newArr);

    printf("Arrays Merged Successfully.\n");
}

void splitArray(int arr[], int size)
{
    int pos, i;

    printf("Enter the split position: ");
    scanf("%d", &pos);

    if(pos < 0 || pos > size - 1) {
        printf("Invalid position.\n");
        return;
    }

    printf("First Part: ");
    for(i = 0; i < pos; i++)
        printf("%d ", arr[i]);

    printf("Second Part: ");
    for(i = pos; i < size; i++)
        printf("%d ", arr[i]);

    printf("\n");
}

int partition(int arr[], int low, int high) {

    int pivot = arr[high];
    int i = low - 1;
    int j, temp;
    for(j = low; j < high; j++) {

        if(arr[j] < pivot) {

            i++;

            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

void quickSort(int arr[], int low, int high) {

    if(low < high) {

        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void sortArray(int arr[], int size) {

    quickSort(arr, 0, size - 1);

    printf("Array Sorted Successfully.\n");
}


int main()
{
    int *arr = NULL;
    int size = 0;
    int choice;
    
    do {
        printf("\n\n____________________MENUn____________________\n");
        printf("1. Create\n");
        printf("2. Display\n");
        printf("3. Count\n");
        printf("4. Reverse\n");
        printf("5. Index of Element\n");
        printf("6. Indexed Element\n");
        printf("7. Insert\n");
        printf("8. Delete\n");
        printf("9. Merge\n");
        printf("10. Split\n");
        printf("11. Sort\n");
        printf("0. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                create(&arr, &size);
                break;
            case 2:
                display(arr, size);
                break;
            case 3:
                count(size);
                break;
            case 4:
                reverse(arr, size);
                break;
            case 5:
                searchElement(arr, size);
                break;
            case 6:
                indexedElement(arr, size);
                break;
            case 7:
                insertElement(&arr, &size);
                break;
            case 8:
                deleteElement(&arr, &size);
                break;
            case 9:
                mergeArray(&arr, &size);
                break;
            case 10:
                splitArray(arr, size);
                break;
            case 11:
                sortArray(arr, size);
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while(choice != 0);

    free(arr);

    return 0;
}