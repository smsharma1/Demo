#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define SIZE 1000000000

int *a, num_threads;
unsigned long long *private_sum;

void *solver(void * param)
{
	int i, id = *(int*)(param), j;
	private_sum[id] = 0;
	for(i=(SIZE/num_threads)*id;i<(SIZE/num_threads)*(id+1);i++)
	{
		private_sum[id]+=a[i];
	}
}
int main(int argc,char* argv[])
{
	int i,j;
	int *tid;
	long long sum=0;
	if (argc != 2) {
		printf ("Need number of threads.\n");
		exit(1);
	}
	a = (int*)malloc(SIZE*sizeof(int));
	pthread_t *threads;
	pthread_attr_t attr;
	num_threads = atoi(argv[1]);
	tid=(int *)malloc(num_threads*sizeof(int));
	threads=(pthread_t *)malloc(num_threads*sizeof(pthread_t));
	private_sum = (unsigned long long*)malloc(num_threads*sizeof(unsigned long long));
	for (i=0; i<num_threads; i++) tid[i] = i;
	for (i=0; i<SIZE; i++) a[i] = i;
	pthread_attr_init(&attr);
	for (i=1; i<num_threads; i++) {
		pthread_create(&threads[i], &attr, solver, &tid[i]);
   	}
	if (num_threads == 1) {
           	for (i=0; i<SIZE; i++) {
                	sum += a[i];
           	}
        }
	else
	{
		j=SIZE/num_threads;
		for(i=0;i<j;i++)
		{
			sum+=a[i];
		}	
	}
	for (i=1; i<num_threads; i++) {
		pthread_join(threads[i], NULL);
		sum += private_sum[i];
	}
	printf("SUM:%lld\n",sum);	
}
