/**
 * Print odd & even numbers in sync with 2 threads
 *
 * Example:
 * thread 1: 1
 * thread 2: 2
 * thread 1: 3
 * thread 2: 4
 */

#include <pthread.h>
#include <stdio.h>

/* threads synchronization primitives */
pthread_mutex_t mx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv = PTHREAD_COND_INITIALIZER;

/* shared data between threads */
static int sd = 1;

#define MAX_DATA 10

#define is_odd(d) (d % 2)
#define is_even(d) (!is_odd(d))

void *print_odd(void *args)
{
	int tidx = *(int *)args;
	while (sd < MAX_DATA) {
		pthread_mutex_lock(&mx);
		/* Use predicate in while loop to handle spurious wake up */
		while (is_even(sd)) pthread_cond_wait(&cv, &mx);
		printf("thread %d: %d\n", tidx, sd++);
		pthread_cond_signal(&cv);
		pthread_mutex_unlock(&mx);
	}
	return NULL;
}

void *print_even(void *args)
{
	int tidx = *(int *)args;
	while (sd < MAX_DATA) {
		pthread_mutex_lock(&mx);
		/* Use predicate in while loop to handle spurious wake up */
		while (is_odd(sd)) pthread_cond_wait(&cv, &mx);
		printf("thread %d: %d\n", tidx, sd++);
		pthread_cond_signal(&cv);
		pthread_mutex_unlock(&mx);
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t tid[2];
	int tidx[2] = {0, 1};
	pthread_create(&tid[0], NULL, print_odd, &tidx[0]);
	pthread_create(&tid[1], NULL, print_even, &tidx[1]);
	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	return 0;
}
