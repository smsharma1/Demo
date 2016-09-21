#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/time.h>

#define SIZE 1000000000

int main (void)
{
	int *a, i, shm_id;
	char *shm;
	unsigned long long child_sum=0, parent_sum=0;
        struct timeval tp_start, tp_end;
        key_t key;

        a = (int*)malloc(SIZE*sizeof(int));

	for (i=0; i<SIZE; i++) a[i] = i;

        /* ftok takes the path of an existing file (possibly a file belonging
           to your project) and a non-zero byte, and returns an integer key.
           See `man ftok' for more detail on how the key is generated.
        */
        key = ftok("/home/shubham/Documents/OS/codes/fork_shm_ftok.c", 1);

	shm_id = shmget(key, 4096, 0777 | IPC_CREAT);

        gettimeofday(&tp_start, NULL);
 
	if (fork() == 0) {
		// This is child
		for (i=0; i<SIZE/2; i++) child_sum += a[i];
		printf("Child saying: my sum is %llu\n", child_sum);
		shm = (char*)shmat(shm_id, 0, 0);
		*(unsigned long long*)shm = child_sum;
        }
        else {
		for (i=SIZE/2; i<SIZE; i++) parent_sum += a[i];
		printf("Parent saying: my sum is %llu\n", parent_sum);
		shm = (char*)shmat(shm_id, 0, 0);
		wait(NULL);
                printf("Total sum: %llu\n", *((unsigned long long*)shm)+parent_sum);
                gettimeofday(&tp_end, NULL);
		shmctl(shm_id, IPC_RMID, NULL);
                printf("Total time: %lld microseconds\n", tp_end.tv_sec*1000000+tp_end.tv_usec - (tp_start.tv_sec*1000000+tp_start.tv_usec));
	}
	shmdt(shm);
	return 0;
}
