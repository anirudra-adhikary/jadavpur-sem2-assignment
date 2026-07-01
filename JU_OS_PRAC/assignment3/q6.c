#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, head, totalSeek = 0;

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int request[n];

    printf("Enter the disk request queue:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &request[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    printf("\nSeek Sequence: %d", head);

    for (int i = 0; i < n; i++)
    {
        totalSeek += abs(request[i] - head);
        head = request[i];
        printf(" -> %d", head);
    }

    printf("\n\nTotal Seek Time = %d", totalSeek);
    printf("\nAverage Seek Time = %.2f\n", (float)totalSeek / n);

    return 0;
}