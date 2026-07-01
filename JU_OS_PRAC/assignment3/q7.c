#include <stdio.h>

void LRU(int pages[], int n, int framesCount) {
    int frames[10];
    int lastUsed[10];
    int faults = 0;

    for (int i = 0; i < framesCount; i++) {
        frames[i] = -1;
        lastUsed[i] = -1;
    }

    printf("\nLRU with %d Frames\n", framesCount);
    printf("--------------------------\n");

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        for (int j = 0; j < framesCount; j++) {
            if (frames[j] == page) {
                found = 1;
                lastUsed[j] = i;
                break;
            }
        }

        if (!found) {
            faults++;

            int replaceIndex = -1;

            // Find empty frame
            for (int j = 0; j < framesCount; j++) {
                if (frames[j] == -1) {
                    replaceIndex = j;
                    break;
                }
            }

            if (replaceIndex == -1) {
                int min = lastUsed[0];
                replaceIndex = 0;

                for (int j = 1; j < framesCount; j++) {
                    if (lastUsed[j] < min) {
                        min = lastUsed[j];
                        replaceIndex = j;
                    }
                }
            }

            frames[replaceIndex] = page;
            lastUsed[replaceIndex] = i;
        }

        printf("%2d -> ", page);
        for (int j = 0; j < framesCount; j++) {
            if (frames[j] == -1)
                printf("- ");
            else
                printf("%d ", frames[j]);
        }
        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", faults);
}

int main() {
    int pages[] = {9, 8, 11, 7, 12, 8, 7, 6, 8, 12,
                   5, 4, 12, 3, 10, 11, 12, 4, 9, 4};

    int n = sizeof(pages) / sizeof(pages[0]);

    LRU(pages, n, 4);
    LRU(pages, n, 5);

    return 0;
}