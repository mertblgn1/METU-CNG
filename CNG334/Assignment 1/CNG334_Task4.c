#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
void *worker(void *param);

#define NUMBER_OF_DARTS		50000000
#define NUM_THREADS 4 // Use 4 threads

// to complete: variables
int circle_count = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/*
 * Generates a double precision random number
 */
double random_double()
{
	return random() / ((double)RAND_MAX + 1);
}

int main (int argc, const char * argv[]) {
	

	/* seed the random number generator */
    srandom((unsigned)time(NULL));

	// to complete: Threads Creations 
  	int i = 0;
  	int error;
  	pthread_t threads[NUM_THREADS]; // Array to store thread IDs
  	/* Create threads */
    for (i = 0; i < NUM_THREADS; i++) {
    	int *num_darts = malloc(sizeof(int));
    	*num_darts = NUMBER_OF_DARTS / NUM_THREADS; // Equal distribution of darts
        error = pthread_create(&(threads[i]), NULL, &worker, num_darts); 
        if (error != 0) {
            printf("\nThread [%d] can't be created", i);
            free(num_darts); // Free memory if thread creation fails
        }
    }

    // Wait for threads to complete their job
    for (i = 0; i < NUM_THREADS; i++) {
    	pthread_join(threads[i], NULL);
    }

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);

	/* estimate Pi */
	double estimated_pi = 4.0 * circle_count / NUMBER_OF_DARTS;

	printf("Pi = %f\n",estimated_pi);

	return 0;
}

void *worker(void *param)
{
	int number_of_darts;
	number_of_darts = *((int *)param);
	free(param); // Free the memory allocated for the number of darts
	int i;
	int hit_count = 0;
	double x,y;

	for (i = 0; i < number_of_darts; i++) {

		/* generate random numbers between -1.0 and +1.0 (exclusive) */
		x = random_double() * 2.0 - 1.0;
		y = random_double() * 2.0 - 1.0;

		if ( sqrt(x*x + y*y) < 1.0 )
			++hit_count;
	}


	
	pthread_mutex_lock(&mutex); // Lock the mutex before updating circle_count
    circle_count += hit_count;
    pthread_mutex_unlock(&mutex); // Unlock the mutex after updating circle_count


	pthread_exit(0);
}

