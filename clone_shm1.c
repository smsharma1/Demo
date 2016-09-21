#define _GNU_SOURCE
#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/time.h>


#define CHILD_STACK 16384
#define SIZE 1000000000
#define KEY 19
int *a;
unsigned long long child_sum=0, parent_sum=0;
int shmid ;
int add (void *arg)
{
	char *shm;
        int i;
	shm=(char *)shmat(shmid,0,0);
        for (i=0; i<SIZE/2; i++) child_sum += a[i];
        printf("Child saying: my sum is %llu and my parent is %d\n", child_sum,getppid());
//	*(unsigned long long*)shm=child_sum;
	shmdt(shm);
}

int main (void)
{
	shmid= shmget(KEY,8,0777|IPC_CREAT);
        int i;
        void *child_stack;
        struct timeval tp_start, tp_end;

        a = (int*)malloc(SIZE*sizeof(int));
        for (i=0; i<SIZE; i++) a[i] = i;

        child_stack = malloc(CHILD_STACK);

        gettimeofday(&tp_start, NULL);

        clone (add, child_stack+CHILD_STACK,CLONE_VM | SIGCHLD, NULL);
        for (i=SIZE/2; i<SIZE; i++) parent_sum += a[i];
        printf("Parent saying: my sum is %llu and my pid is %d\n", parent_sum,getpid());
        // wait for child
        wait (NULL);
	char * shm=shmat(shmid,0,0);
        printf("Total sum: %llu\n",/* (*(unsigned long long *)shm)*/child_sum+parent_sum);
        gettimeofday(&tp_end, NULL);
        printf("Total time: %lld microseconds\n", tp_end.tv_sec*1000000+tp_end.tv_usec - (tp_start.tv_sec*1000000+tp_start.tv_usec));
        return 0;
}

