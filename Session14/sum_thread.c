#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
void * work_thread(void * arg); 

int num_threads;
int max_num; 

int main(int argc, char *argv[])
{
	pthread_t *thread;
	int *index; 
	int sum = 0;

	printf("Number of threads: ");
	scanf("%d", &num_threads); // N
	printf("Maximum integer (> Number of threads):");
	scanf("%d", &max_num); // x

	// TODO: pthread & index array
	thread = (pthread_t*) malloc(sizeof(pthread_t)*num_threads);
	int num = max_num / num_threads;
	if(max_num % num_threads != 0)
		num++;
	index = (int*) malloc(sizeof(int)*num_threads);

	// TODO: pthread create	
	for (int i = 0; i < num_threads; i++)
	{	
		index[i] = i * num + 1;
		pthread_create(&thread[i], NULL, work_thread, (void *) &index[i]);

		// TODO: pthread_join
		int* reval;
		pthread_join(thread[i], (void**) &reval);
		// printf("reval: %d\n", (int) *reval);
		sum += *reval;
	}
	
	printf("result: %d \n", sum);
	return 0;
}

void * work_thread(void *arg){
	int start = ((int*)arg)[0];
	int num = max_num / num_threads;
	if(max_num % num_threads != 0)
		num++;

	int sum = 0;
	int *p = (int*) malloc(sizeof(int));

	for(int i = start; i <= max_num && i < start+num; i++){
		sum += i;
		// printf("i:%d\n",i);
	}

	*p = sum;
	// printf("sum:%d\n",sum);
	return (void *) p;
}
