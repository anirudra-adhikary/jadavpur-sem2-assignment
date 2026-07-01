#include <stdio.h>

int main()
{
    int n, indexBlock, blocks[50];

    printf("Enter the number of blocks available on disk: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        blocks[i] = 0;

    printf("Enter the index block: ");
    scanf("%d", &indexBlock);

    if (blocks[indexBlock] == 1)
    {
        printf("Index block is already allocated.\n");
        return 0;
    }

    blocks[indexBlock] = 1;

    int numBlocks;
    printf("Enter the number of blocks needed for the file: ");
    scanf("%d", &numBlocks);

    int allocated[numBlocks];

    printf("Enter the block numbers:\n");

    for (int i = 0; i < numBlocks; i++)
    {
        scanf("%d", &allocated[i]);

        if (allocated[i] >= n || blocks[allocated[i]] == 1)
        {
            printf("Block %d cannot be allocated.\n", allocated[i]);
            return 0;
        }

        blocks[allocated[i]] = 1;
    }

    printf("\nIndexed File Allocation\n");
    printf("Index Block: %d\n", indexBlock);

    printf("Allocated Blocks: ");
    for (int i = 0; i < numBlocks; i++)
    {
        printf("%d ", allocated[i]);
    }

    printf("\n");

    return 0;
}