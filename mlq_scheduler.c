#include <stdio.h>

#define MAX_PROCESSES 20
#define AGE_THRESHOLD 5

void multilevelQueueScheduling(int processIds[], int burstTime[], int processTypes[], int numProcesses) {
    int systemQueue[20], userQueue[20];
    int systemFront = -1, systemRear = -1, userFront = -1, userRear = -1;

    int waitingTime[20], turnaroundTime[20], agingCounter[20];  // Arrays for waiting time, turnaround time, and aging
    float avgWaitingTime = 0, avgTurnaroundTime = 0;    // Initialize averages

    // Initialize aging for user processes
    int i;
    for (i = 0; i < numProcesses; i++) {
        agingCounter[i] = 0;
    }

    int currentTime = 0;

    // Distribute processes into system and user queues
    for (i = 0; i < numProcesses; i++) {
        if (processTypes[i] == 0) {
            // System process
            systemQueue[++systemRear] = i;
        } else {
            // User process
            userQueue[++userRear] = i;
        }
    }

    // Multilevel Queue Scheduling
    while (systemFront <= systemRear || userFront <= userRear) {
        int currentProcess = -1;

        // Check for system process
        if (systemFront <= systemRear) {
            currentProcess = systemQueue[++systemFront];
        }

        // If no system process, check for user process
        if (currentProcess == -1 && userFront <= userRear) {
            currentProcess = userQueue[++userFront];
        }

        if (currentProcess != -1) {
            // Move user process to a higher-priority queue with aging
            if (processTypes[currentProcess] == 1) {
                agingCounter[currentProcess]++;
                if (agingCounter[currentProcess] >= AGE_THRESHOLD && systemFront <= systemRear) {
                    systemQueue[++systemRear] = currentProcess;
                }
            }

            // Update waiting time and turnaround time
            waitingTime[currentProcess] = currentTime;
            turnaroundTime[currentProcess] = waitingTime[currentProcess] + burstTime[currentProcess];
            avgWaitingTime += waitingTime[currentProcess];
            avgTurnaroundTime += turnaroundTime[currentProcess];

            // Update current time
            currentTime += burstTime[currentProcess];
        }
    }

    // Print the results
    printf("\n-------------------------------------------------------------------------------------------");
    printf("\nPROCESS\t\t SYSTEM/USER PROCESS\t    BURST TIME\t   WAITING TIME\t   TURNAROUND TIME\n");
    printf("-------------------------------------------------------------------------------------------");
    for (i = 0; i < numProcesses; i++)
        printf("\n%d \t\t\t %d \t\t\t %d \t\t %d \t\t %d ", processIds[i], processTypes[i], burstTime[i],
               waitingTime[i], turnaroundTime[i]);
    printf("\n-------------------------------------------------------------------------------------------");
    printf("\n\n\nAverage Waiting Time is : %f ms", avgWaitingTime / numProcesses);
    printf("\nAverage Turnaround Time is: %f ms\n", avgTurnaroundTime / numProcesses);
}

int main() {
    int processIds[MAX_PROCESSES], burstTime[MAX_PROCESSES], processTypes[MAX_PROCESSES], numProcesses;

    // Prompt until a valid input is provided
    while (1) {
        printf("\nEnter the number of processes:");
        if (scanf("%d", &numProcesses) == 1 && numProcesses > 0 && numProcesses <= MAX_PROCESSES) {
            break;  // Break the loop if a valid input is provided
        } else {
            // Clear the input buffer in case of invalid input
            while (getchar() != '\n');
            printf("Error: Please enter a valid positive integer less than or equal to %d.\n", MAX_PROCESSES);
        }
    }
    int i;
    for (i = 0; i < numProcesses; i++) {
        processIds[i] = i;
        printf("\nEnter the Burst Time of Process %d (in milliseconds):", i);
        if (scanf("%d", &burstTime[i]) != 1 || burstTime[i] < 0) {
            printf("Error: Burst time must be a non-negative integer. Exiting.\n");
            return 1;
        }

        printf("Enter 0 for System Process 1 for User Process: ");
        if (scanf("%d", &processTypes[i]) != 1 || (processTypes[i] != 0 && processTypes[i] != 1)) {
            printf("Error: Invalid process type. Exiting.\n");
            return 1;
        }
    }

    multilevelQueueScheduling(processIds, burstTime, processTypes, numProcesses);

    return 0;
}