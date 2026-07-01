#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void write_processes(FILE *file, int num_processes) {
    for (int i = 1; i <= num_processes; i++) {
        int priority = (rand() % 10) + 1;       // Priority 1-10
        int arrival_time = rand() % 50;         // Arrival 0-49
        int cpu1 = (rand() % 20) + 1;           // CPU burst 1-20
        int io1 = (rand() % 10) + 1;            // IO burst 1-10
        int cpu2 = (rand() % 20) + 1;           
        int io2 = (rand() % 10) + 1;
        int cpu3 = (rand() % 20) + 1;

        
        fprintf(file, "%d %d %d %d %d %d %d %d -1\n", 
                i, priority, arrival_time, cpu1, io1, cpu2, io2, cpu3);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <no.of.processes>\n", argv[0]);
        return 1;
    }

    int num_processes = atoi(argv[1]);
    if (num_processes <= 0) {
        printf("Please enter a valid number of processes.\n");
        return 1;
    }

    FILE *file = fopen("process.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    srand(time(NULL)); 
    write_processes(file, num_processes);
    
    fclose(file);
    printf("Successfully generated %d processes in process.txt\n", num_processes);
    return 0;
}