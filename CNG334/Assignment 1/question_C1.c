// Name: Mert Can Bilgin
// Student ID: 2453025

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define NUM_PROCESSES 6

typedef struct {
	int id;
	int execution_time;
	int priority;
} Process;

void initializeProcesses(Process processes[]) {
	srand(time(NULL)); // Seed for random number generation
	int i;
	for (i = 0; i < NUM_PROCESSES; i++) {
		processes[i].id = i + 1;
		processes[i].execution_time = rand() % 21 + 10; // Range: [10, 30]
		processes[i].priority = rand() % 10 + 1; // Range: [1, 10]
	}
}

void printProcesses(Process processes[]) {
	printf("ID\tExecution Time\tPriority\n");
	int i;
	for (i = 0; i < NUM_PROCESSES; i++) {
		printf("%d\t%d\t\t%d\n", processes[i].id, processes[i].execution_time, processes[i].priority);
	}
}

void selectionSort(Process processes[], int n) {
	int i, j, min_index;

	for (i = 0; i < n - 1; i++) {
		min_index = i;
		for (j = i + 1; j < n; j++) {
			if (processes[j].priority < processes[min_index].priority) {
				min_index = j;
			}
		}

		if (min_index != i) {
			// Swap processes
			Process temp = processes[i];
			processes[i] = processes[min_index];
			processes[min_index] = temp;
		}
	}
}

void insertionSort(Process processes[], int n) {
	int i, j;
	for (i = 1; i < n; i++) {
		Process key = processes[i];
		int j = i - 1;
		while (j >= 0 && processes[j].execution_time > key.execution_time) {
			processes[j + 1] = processes[j];
			j--;
		}
		processes[j + 1] = key;
	}
}

void sortProcesses(Process processes[], int option) {
	printf("\nBefore sorting:\n");
	printProcesses(processes);

	if (option == 1) {
		selectionSort(processes, NUM_PROCESSES); // Sort by priority
		printf("\nAfter sorting by priority:\n");
	} else if (option == 2) {
		insertionSort(processes, NUM_PROCESSES); // Sort by execution time
		printf("\nAfter sorting by execution time:\n");
	}

	printProcesses(processes);
}

void executeProcesses(Process processes[], int option) {
    printf("\nExecuting Processes:\n");
    if (option == 1) {
        // Non-preemptive priority scheduling
        selectionSort(processes, NUM_PROCESSES); // Sort by priority
        for (int i = 0; i < NUM_PROCESSES; i++) {
            printf("Process %d (Priority %d) is executing...\n", processes[i].id, processes[i].priority);
            usleep(processes[i].execution_time * 1000); // Sleep for execution time (milliseconds to microseconds) for time saving
        }
    } else if (option == 2) {
        // Shortest process next scheduling
        insertionSort(processes, NUM_PROCESSES); // Sort by execution time
        for (int i = 0; i < NUM_PROCESSES; i++) {
            printf("Process %d (Execution Time %d ms) is executing...\n", processes[i].id, processes[i].execution_time);
            usleep(processes[i].execution_time * 1000); // Sleep for execution time (milliseconds to microseconds) for time saving
        }
    } else {
        printf("Invalid option for scheduling technique.\n");
    }
    printf("\nAll processes are executed.\n");
}


int main() {
	Process *processes;
	processes = mmap(NULL, sizeof(Process) * NUM_PROCESSES, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0);
	if(processes == MAP_FAILED){
     printf("Mapping Failed\n");
     return 1;
    }

	// Initialize processes
	initializeProcesses(processes);

	// Create a child process
	pid_t pid = fork();

	if (pid == 0) {
		// Child
		sortProcesses(processes, 1); // Sort by priority
		exit(0);
	} else if (pid > 0) {
		// Parent waits for the child to complete then execute processes
		wait(NULL);
		executeProcesses(processes, 2); // Shortest process next
	} else {
		// Forking failed
		printf("Fail to fork\n");
		exit(-1);
	}

	return 0;
}













