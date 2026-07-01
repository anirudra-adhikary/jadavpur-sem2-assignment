#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BURSTS 100
#define MAX_JOBS 100

typedef struct {
    int pid;
    int priority;
    int arrival_time;
    int bursts[MAX_BURSTS];
    int burst_count;
    
    // Simulation tracking states
    int current_burst_idx;
    int current_burst_remaining;
    int ready_time;
    int finish_time;
    int total_cpu_time;
    int total_io_time;
    int is_completed;
    int in_io;
    int io_end_time;
} Process;

// Global process arrays
Process master_jobs[MAX_JOBS];
Process jobs[MAX_JOBS];
int job_count = 0;

// Parse the specialized space-separated file format
void parse_input_file() {
    FILE *file = fopen("process.txt", "r");
    if (!file) {
        printf("Error: Could not open file %s\n", filename);
        exit(1);
    }

    int val;
    while (fscanf(file, "%d", &val) != EOF) {
        Process p;
        p.pid = val;
        
        if (fscanf(file, "%d %d", &p.priority, &p.arrival_time) != 3) {
            // Safe fallback if format mismatches mid-read
            break;
        }

        p.burst_count = 0;
        p.total_cpu_time = 0;
        p.total_io_time = 0;
        
        while (fscanf(file, "%d", &val) == 1 && val != -1) {
            if (p.burst_count < MAX_BURSTS) {
                p.bursts[p.burst_count] = val;
                if (p.burst_count % 2 == 0) {
                    p.total_cpu_time += val;
                } else {
                    p.total_io_time += val;
                }
                p.burst_count++;
            }
        }
        
        master_jobs[job_count++] = p;
        if (job_count >= MAX_JOBS) break;
    }
    fclose(file);
}

// Reset process dynamic states before each simulation run
void reset_jobs() {
    for (int i = 0; i < job_count; i++) {
        jobs[i] = master_jobs[i];
        jobs[i].current_burst_idx = 0;
        jobs[i].current_burst_remaining = jobs[i].bursts[0];
        jobs[i].ready_time = jobs[i].arrival_time;
        jobs[i].finish_time = 0;
        jobs[i].is_completed = 0;
        jobs[i].in_io = 0;
        jobs[i].io_end_time = 0;
    }
}

// Print results calculation table
void print_results(const char *algo_title) {
    printf("\n==================== %s ====================\n", algo_title);
    printf("%-6s%-10s%-10s%-12s%-10s\n", "PID", "Priority", "Arrival", "Turnaround", "Waiting");
    
    double total_tat = 0, total_wt = 0;
    
    // Sort by PID just for neat output display
    for (int i = 0; i < job_count; i++) {
        int tat = jobs[i].finish_time - jobs[i].arrival_time;
        int wt = tat - (jobs[i].total_cpu_time + jobs[i].total_io_time);
        
        printf("%-6d%-10d%-10d%-12d%-10d\n", 
               jobs[i].pid, jobs[i].priority, jobs[i].arrival_time, tat, wt);
               
        total_tat += tat;
        total_wt += wt;
    }
    
    printf("----------------------------------------------------------\n");
    printf("Average Turnaround Time: %.2f\n", total_tat / job_count);
    printf("Average Waiting Time:    %.2f\n\n", total_wt / job_count);
}

// Main Simulation Engine
void run_simulation(const char *algo_type, int time_slice) {
    reset_jobs();
    
    int current_time = 0;
    int completed_count = 0;
    int active_idx = -1;
    int quantum_left = time_slice;

    while (completed_count < job_count) {
        // 1. Check and resolve any I/O completions at current timestamp
        for (int i = 0; i < job_count; i++) {
            if (jobs[i].in_io && jobs[i].io_end_time <= current_time) {
                jobs[i].in_io = 0;
                jobs[i].ready_time = current_time;
            }
        }

        // 2. Select the next process if CPU is idle
        if (active_idx == -1) {
            int best_idx = -1;
            
            for (int i = 0; i < job_count; i++) {
                // Process must be ready and not finished or blocked in IO
                if (!jobs[i].is_completed && !jobs[i].in_io && jobs[i].ready_time <= current_time) {
                    if (best_idx == -1) {
                        best_idx = i;
                    } else {
                        if (strcmp(algo_type, "FCFS") == 0 || strcmp(algo_type, "RR") == 0) {
                            if (jobs[i].ready_time < jobs[best_idx].ready_time) {
                                best_idx = i;
                            }
                        } else if (strcmp(algo_type, "Priority") == 0) {
                            if (jobs[i].priority < jobs[best_idx].priority) {
                                best_idx = i;
                            } else if (jobs[i].priority == jobs[best_idx].priority) {
                                if (jobs[i].ready_time < jobs[best_idx].ready_time) {
                                    best_idx = i;
                                }
                            }
                        }
                    }
                }
            }
            
            if (best_idx != -1) {
                active_idx = best_idx;
                quantum_left = time_slice;
            }
        }

        // 3. Step execution time
        if (active_idx != -1) {
            jobs[active_idx].current_burst_remaining--;
            quantum_left--;
            current_time++;

            // Handle current CPU burst completion
            if (jobs[active_idx].current_burst_remaining == 0) {
                jobs[active_idx].current_burst_idx++; // advance past CPU burst
                
                // Check if an IO burst follows
                if (jobs[active_idx].current_burst_idx < jobs[active_idx].burst_count) {
                    int io_duration = jobs[active_idx].bursts[jobs[active_idx].current_burst_idx];
                    jobs[active_idx].in_io = 1;
                    jobs[active_idx].io_end_time = current_time + io_duration;
                    
                    jobs[active_idx].current_burst_idx++; // advance past IO burst to next CPU burst
                    if (jobs[active_idx].current_burst_idx < jobs[active_idx].burst_count) {
                        jobs[active_idx].current_burst_remaining = jobs[active_idx].bursts[jobs[active_idx].current_burst_idx];
                    }
                } else {
                    // Job finished execution entirely
                    jobs[active_idx].is_completed = 1;
                    jobs[active_idx].finish_time = current_time;
                    completed_count++;
                }
                active_idx = -1; // Yield CPU
            } 
            // Handle Round Robin context expiration
            else if (strcmp(algo_type, "RR") == 0 && quantum_left == 0) {
                jobs[active_idx].ready_time = current_time;
                active_idx = -1; // Yield CPU back to ready queue
            }
        } else {
            // CPU is completely idle, advance global clock tick
            current_time++;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <input_profile_file>\n", argv[0]);
        return 1;
    }

    parse_input_file(argv[1]);
    
    if (job_count == 0) {
        printf("No valid job profiles found in file.\n");
        return 1;
    }

    run_simulation("FCFS", 0);
    print_results("First-Come, First-Served (FCFS)");

    run_simulation("Priority", 0);
    print_results("Non-Preemptive Priority");

    run_simulation("RR", 15);
    print_results("Round Robin (RR, Quantum=15)");

    return 0;
}