#include <stdio.h>

void FIFO(int pages[], int n, int frameCount) {
    int frames[10];
    int front = 0;
    int faults = 0;

    for (int i = 0; i < frameCount; i++)
        frames[i] = -1;

    for (int i = 0; i < n; i++) {
        int found = 0;

        for (int j = 0; j < frameCount; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            frames[front] = pages[i];
            front = (front + 1) % frameCount;
            faults++;
        }
    }

    printf("Frames = %d, Page Faults = %d\n", frameCount, faults);
}

int main() {
    int pages[] = {9, 10, 7, 12, 7, 6, 12, 6, 5, 4,
                   3, 10, 11, 12, 4, 5, 6, 9, 4, 5};

    int n = sizeof(pages) / sizeof(pages[0]);

    FIFO(pages, n, 3);
    FIFO(pages, n, 4);

    return 0;
}