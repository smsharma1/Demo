#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define N 1000
#define K 20
#define SHM_KEY 19
int main(void)
{
	int i, j, shm_id;
	unsigned *shm;
	unsigned count=0;
	unsigned long long sum=0;
	signal(SIGCHLD, SIG_IGN); // Ignore death of children
	shm_id = shmget(SHM_KEY, 4096, 0777 | IPC_CREAT);
	for (i=1; i<K; i++) 
	{
		if (fork() == 0) 
		{
			for (j=0; j<N; j++) 
			{
				count++;
			}
			shm = (unsigned*)shmat(shm_id, 0, 0);
			shm[i] = count;
			shmdt(shm);
			exit(0);
		}		
	}
	for (j=0; j<N; j++) sum++;
	wait(NULL);
	shm = (unsigned*)shmat(shm_id, 0, 0);
	for (i=1; i<K; i++) sum += shm[i];
	shmdt(shm);
	shmctl(shm_id, IPC_RMID, NULL);
	printf("%llu\n", sum);
	return 0;
}	
