// Name: Mert Can Bilgin
// Student ID: 2453025
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define N 5 // Number of elements for the array

int *ptr;

void *child_thread(void *arg) {
    printf("Updating the values of the array elements :\n");
    for (int i = 0; i < N; i++)
        ptr[i] = 462;
    pthread_exit(NULL);
}

int main() {
    // Allocate memory for the array
    ptr = (int *)malloc(N * sizeof(int));
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Initialize the array elements to 334
    for (int i = 0; i < N; i++)
        ptr[i] = 334;

    printf("The values of the array elements :\n");
    for (int i = 0; i < N; i++)
        printf(" %d \n", ptr[i]);

    pthread_t tid;
    int ret = pthread_create(&tid, NULL, child_thread, NULL);
    if (ret != 0) {
        printf("Thread creation failed\n");
        return 1;
    }

    pthread_join(tid, NULL);

    printf("The values of the array elements again:\n");
    for (int i = 0; i < N; i++)
        printf("%d \n", ptr[i]);

    free(ptr); // Free allocated memory

    return 0;
}
