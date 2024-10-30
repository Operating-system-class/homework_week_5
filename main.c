#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int processID;
    int arrivalTime;
    int burstTime;
    int startTime;
    int endTime;
    bool isCompleted;
} Process;

void sortByArrival(Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].arrivalTime > p[j].arrivalTime) {
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

int main() {
    int n = 5;  // Số lượng process
    Process processes[] = {
        {1, 0, 8, 0, 0, false},
        {2, 1, 4, 0, 0, false},
        {3, 2, 9, 0, 0, false},
        {4, 3, 5, 0, 0, false},
        {5, 4, 2, 0, 0, false}
    };

    // Sắp xếp các process theo arrival time
    sortByArrival(processes, n);

    int currentTime = 0;
    int completedProcesses = 0;

    printf("Process\tStart Time\tBurst Time\n");

    while (completedProcesses < n) {
        int idx = -1;
        int minBurst = 100000;

        // Tìm process với burst time nhỏ nhất tại thời điểm hiện tại
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && !processes[i].isCompleted && processes[i].burstTime < minBurst) {
                minBurst = processes[i].burstTime;
                idx = i;
            }
        }

        if (idx != -1) {
            processes[idx].startTime = currentTime;
            processes[idx].endTime = currentTime + processes[idx].burstTime;
            processes[idx].isCompleted = true;
            currentTime = processes[idx].endTime;
            completedProcesses++;

            // In ra thông tin về quá trình thực hiện
            printf("P%d\t%d\t\t%d\n", processes[idx].processID, processes[idx].startTime, processes[idx].burstTime);
        } else {
            currentTime++;
        }
    }

    return 0;
}
