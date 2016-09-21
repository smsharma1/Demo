#define _GNU_SOURCE
#include <stdio.h>
#include <signal.h>
#include <sched.h>
#include <stdlib.h>
#include <sys/syscall.h>

int p=10;
int f2(void *k)
{
	printf("Second sibling\n");
	wait(NULL);
}
int f1(void *k)
{
	printf("This is child of sibling%d\n",getpid());
	p=100;
	while(1);
	return;
}
int f(void* k)
{
	if(fork()==0){
		printf("I am child with pid %d with ppid:%d\n",getpid(),getppid());
		while(1);
	}
	void *child_stack = malloc(16384);
	printf("This is sibling of parent%d\n",getpid());
	clone(f1, child_stack+16384, CLONE_VM | SIGCHLD, NULL);
	//sleep(1);
	wait(NULL);
	printf("I am not waiting\n");
}
int main(){
	printf("this is main process %d\n",getpid());
	void *child_stack = malloc(16384);
	clone (f, child_stack+16384, CLONE_VM | CLONE_THREAD | CLONE_SIGHAND, NULL);
	void *child_stack1 = malloc(16384);
	sleep(0.0000000000000005);
	printf("Hello");
	//wait(NULL);
	clone(f2, child_stack1+16384, CLONE_VM | CLONE_THREAD | CLONE_SIGHAND, NULL);
	sleep(0.0000000000000000005);
	printf("%d\n",p);
	//while(1);
	return 0;

}
