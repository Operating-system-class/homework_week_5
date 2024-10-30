#include <stdio.h>

#define MAX_PROCESSES 4

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int start_time;
    int end_time;
} Process;

void srt_scheduling(Process processes[], const int n, FILE *output_file) {
    int completed = 0, time = 0;

    while (completed != n) {
        int shortest = -1;
        int min_remaining_time = __INT_MAX__;

        // Find the process with the shortest remaining time at the current time
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && processes[i].end_time == -1 && processes[i].remaining_time < min_remaining_time) {
                min_remaining_time = processes[i].remaining_time;
                shortest = i;
            }
        }

        if (shortest == -1) {
            // No process is ready to run, increase time
            time++;
            continue;
        }

        // If this is the first time the process is running, record the start time
        if (processes[shortest].remaining_time == processes[shortest].burst_time) {
            processes[shortest].start_time = time;
        }

        // Run the process for one unit of time
        processes[shortest].remaining_time--;
        time++;

        // If the process is completed, record the end time and increase the completed count
        if (processes[shortest].remaining_time == 0) {
            processes[shortest].end_time = time;
            completed++;

            printf("Process: P%d      |Start time: %d       |Run time: %d\n", processes[shortest].pid, processes[shortest].start_time, processes[shortest].end_time - processes[shortest].start_time);
            fprintf(output_file, "Process: P%d      |Start time: %d       |Run time: %d\n", processes[shortest].pid, processes[shortest].start_time, processes[shortest].end_time - processes[shortest].start_time);
        }
    }
}

int main() {
    Process processes[MAX_PROCESSES] = {
        {1, 0, 6, 6, -1, -1},
        {2, 1, 2, 2, -1, -1},
        {3, 3, 9, 9, -1, -1},
        {4, 5, 11, 11, -1, -1},
    };

    FILE *output_file = fopen("scheduling_output.txt", "w");
    if (output_file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Call the SRT scheduling function
    srt_scheduling(processes, MAX_PROCESSES, output_file);

    fclose(output_file);
    return 0;
}