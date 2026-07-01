#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_JOBS 100

// Define the Process Structure
typedef struct {
    int job_id;
    int priority;
    int arrival_time;
    int cpu1, io1, cpu2, io2, cpu3;
    
    // Tracking variables for simulation
    int current_state;       // 0: Not Arrived, 1: Ready, 2: IO Wait, 3: Terminated
    int current_burst_stage; // 0: cpu1, 1: io1, 2: cpu2, 3: io2, 4: cpu3
    int remaining_time;      
    
    // Metrics
    int waiting_time;
    int turnaround_time;
    int completion_time;
} Process;

Process jobs[MAX_JOBS];
int job_count = 0;

// Subroutine: Read processes from file
void load_processes(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    int end_marker;
    job_count = 0;
    while (fscanf(file, "%d %d %d %d %d %d %d %d %d", 
                  &jobs[job_count].job_id, &jobs[job_count].priority, 
                  &jobs[job_count].arrival_time, &jobs[job_count].cpu1, 
                  &jobs[job_count].io1, &jobs[job_count].cpu2, 
                  &jobs[job_count].io2, &jobs[job_count].cpu3, &end_marker) == 9) {
        job_count++;
    }
    fclose(file);
}

// Subroutine: Reset jobs state before running a new algorithm
void reset_jobs() {
    for (int i = 0; i < job_count; i++) {
        jobs[i].current_state = 0; 
        jobs[i].current_burst_stage = 0;
        jobs[i].remaining_time = jobs[i].cpu1;
        jobs[i].waiting_time = 0;
        jobs[i].turnaround_time = 0;
        jobs[i].completion_time = 0;
    }
}

// Subroutine: Print final metrics
void print_metrics(const char* algo_name) {
    float total_wait = 0, total_turnaround = 0;
    printf("\n--- Results for %s ---\n", algo_name);
    printf("Job ID\tWait Time\tTurnaround Time\tCompletion Time\n");
    for (int i = 0; i < job_count; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", jobs[i].job_id, jobs[i].waiting_time, 
               jobs[i].turnaround_time, jobs[i].completion_time);
        total_wait += jobs[i].waiting_time;
        total_turnaround += jobs[i].turnaround_time;
    }
    printf("\nAverage Waiting Time: %.2f\n", total_wait / job_count);
    printf("Average Turnaround Time: %.2f\n", total_turnaround / job_count);
    printf("----------------------------------------\n");
}

// Subroutine: FCFS Scheduling Algorithm
void run_fcfs() {
    int time = 0, completed_jobs = 0, running_job = -1;
    reset_jobs();

    while (completed_jobs < job_count) {
        for (int i = 0; i < job_count; i++) {
            if (jobs[i].current_state == 0 && jobs[i].arrival_time <= time) {
                jobs[i].current_state = 1; 
            }
            if (jobs[i].current_state == 2) {
                jobs[i].remaining_time--;
                if (jobs[i].remaining_time == 0) {
                    jobs[i].current_burst_stage++; 
                    if (jobs[i].current_burst_stage == 2) jobs[i].remaining_time = jobs[i].cpu2;
                    if (jobs[i].current_burst_stage == 4) jobs[i].remaining_time = jobs[i].cpu3;
                    jobs[i].current_state = 1; 
                }
            }
            if (jobs[i].current_state == 1 && running_job != i) {
                jobs[i].waiting_time++;
            }
        }

        if (running_job == -1) {
            for (int i = 0; i < job_count; i++) {
                if (jobs[i].current_state == 1) {
                    running_job = i; break;
                }
            }
        }

        if (running_job != -1) {
            jobs[running_job].remaining_time--;
            if (jobs[running_job].remaining_time == 0) {
                if (jobs[running_job].current_burst_stage == 0) {
                    jobs[running_job].current_state = 2; jobs[running_job].remaining_time = jobs[running_job].io1; jobs[running_job].current_burst_stage = 1;
                } else if (jobs[running_job].current_burst_stage == 2) {
                    jobs[running_job].current_state = 2; jobs[running_job].remaining_time = jobs[running_job].io2; jobs[running_job].current_burst_stage = 3;
                } else if (jobs[running_job].current_burst_stage == 4) {
                    jobs[running_job].current_state = 3; jobs[running_job].completion_time = time + 1;
                    jobs[running_job].turnaround_time = jobs[running_job].completion_time - jobs[running_job].arrival_time; completed_jobs++;
                }
                running_job = -1; 
            }
        }
        time++;
    }
    print_metrics("First Come First Serve (FCFS)");
}

// Subroutine: Priority Scheduling Algorithm (Non-Preemptive)
void run_priority() {
    int time = 0, completed_jobs = 0, running_job = -1;
    reset_jobs();

    while (completed_jobs < job_count) {
        // 1. Process Arrivals and I/O
        for (int i = 0; i < job_count; i++) {
            if (jobs[i].current_state == 0 && jobs[i].arrival_time <= time) jobs[i].current_state = 1;
            
            if (jobs[i].current_state == 2) {
                jobs[i].remaining_time--;
                if (jobs[i].remaining_time == 0) {
                    jobs[i].current_burst_stage++; 
                    if (jobs[i].current_burst_stage == 2) jobs[i].remaining_time = jobs[i].cpu2;
                    if (jobs[i].current_burst_stage == 4) jobs[i].remaining_time = jobs[i].cpu3;
                    jobs[i].current_state = 1;
                }
            }
            if (jobs[i].current_state == 1 && running_job != i) jobs[i].waiting_time++;
        }

        // 2. Select highest priority job (lowest priority number) if CPU is idle
        if (running_job == -1) {
            int highest_priority = 9999; 
            for (int i = 0; i < job_count; i++) {
                if (jobs[i].current_state == 1 && jobs[i].priority < highest_priority) {
                    highest_priority = jobs[i].priority;
                    running_job = i;
                }
            }
        }

        // 3. Execute Job
        if (running_job != -1) {
            jobs[running_job].remaining_time--;
            if (jobs[running_job].remaining_time == 0) {
                if (jobs[running_job].current_burst_stage == 0) {
                    jobs[running_job].current_state = 2; jobs[running_job].remaining_time = jobs[running_job].io1; jobs[running_job].current_burst_stage = 1;
                } else if (jobs[running_job].current_burst_stage == 2) {
                    jobs[running_job].current_state = 2; jobs[running_job].remaining_time = jobs[running_job].io2; jobs[running_job].current_burst_stage = 3;
                } else if (jobs[running_job].current_burst_stage == 4) {
                    jobs[running_job].current_state = 3; jobs[running_job].completion_time = time + 1;
                    jobs[running_job].turnaround_time = jobs[running_job].completion_time - jobs[running_job].arrival_time; completed_jobs++;
                }
                running_job = -1;
            }
        }
        time++;
    }
    print_metrics("Priority Scheduling (Non-Preemptive)");
}

// Subroutine: Round Robin Scheduling Algorithm
void run_round_robin(int time_slice) {
    int time = 0, completed_jobs = 0, running_job = -1;
    int quantum_used = 0;
    reset_jobs();

    // Circular Queue implementation for Round Robin
    int queue[MAX_JOBS];
    int head = 0, tail = 0, q_size = 0;

    while (completed_jobs < job_count) {
        // 1. Process I/O blockings & New Arrivals
        for (int i = 0; i < job_count; i++) {
            if (jobs[i].current_state == 0 && jobs[i].arrival_time == time) {
                jobs[i].current_state = 1;
                queue[tail] = i; tail = (tail + 1) % MAX_JOBS; q_size++; // Enqueue
            }
            if (jobs[i].current_state == 2) {
                jobs[i].remaining_time--;
                if (jobs[i].remaining_time == 0) {
                    jobs[i].current_burst_stage++;
                    if (jobs[i].current_burst_stage == 2) jobs[i].remaining_time = jobs[i].cpu2;
                    if (jobs[i].current_burst_stage == 4) jobs[i].remaining_time = jobs[i].cpu3;
                    jobs[i].current_state = 1;
                    queue[tail] = i; tail = (tail + 1) % MAX_JOBS; q_size++; // Enqueue
                }
            }
            if (jobs[i].current_state == 1 && running_job != i) jobs[i].waiting_time++;
        }

        // 2. Manage Time Slice Preemption
        if (running_job != -1 && quantum_used == time_slice) {
            jobs[running_job].current_state = 1;
            queue[tail] = running_job; tail = (tail + 1) % MAX_JOBS; q_size++; // Push to back of queue
            running_job = -1;
        }

        // 3. Pick next job if CPU is free
        if (running_job == -1 && q_size > 0) {
            running_job = queue[head]; head = (head + 1) % MAX_JOBS; q_size--; // Dequeue
            quantum_used = 0;
        }

        // 4. Execute Running Job
        if (running_job != -1) {
            jobs[running_job].remaining_time--;
            quantum_used++;

            if (jobs[running_job].remaining_time == 0) {
                if (jobs[running_job].current_burst_stage == 0) {
                    jobs[running_job].current_state = 2; jobs[running_job].remaining_time = jobs[running_job].io1; jobs[running_job].current_burst_stage = 1;
                } else if (jobs[running_job].current_burst_stage == 2) {
                    jobs[running_job].current_state = 2; jobs[running_job].remaining_time = jobs[running_job].io2; jobs[running_job].current_burst_stage = 3;
                } else if (jobs[running_job].current_burst_stage == 4) {
                    jobs[running_job].current_state = 3; jobs[running_job].completion_time = time + 1;
                    jobs[running_job].turnaround_time = jobs[running_job].completion_time - jobs[running_job].arrival_time; completed_jobs++;
                }
                running_job = -1; // CPU free, do not put back in queue
            }
        }
        time++;
    }
    print_metrics("Round Robin (Time Slice: 15)");
}

int main() {
    load_processes("process.txt");
    if (job_count == 0) {
        printf("No processes found. Run generator first.\n");
        return 1;
    }
    
    printf("Loaded %d processes.\n", job_count);
    
    run_fcfs();
    run_priority();
    run_round_robin(15); 
    
    return 0;
}