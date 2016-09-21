#define _GNU_SOURCE
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/syscall.h>
#define N 1000
#define K 20
#define SHM_KEY 19
#define STACK 16384
int l;
void m(int n)
{
	printf("I am initial\n");
}
void k(int p)
{
	printf("I am final\n");
	printf("%d\n",syscall(SYS_gettid));
}
FILE *f;

int add (void *arg)
{
        
	int i;
        l=3;
        printf("I am child\n");
        signal(2,m);
        kill(getpid(),2);
	fclose(f);
        while(1);
        return 1;
}


int main(){
	int i;
	char z='a';
	void *child_stack;
	child_stack=malloc(STACK);
	l=2;
	f=fopen("test.txt","r");
	printf("%d\n",syscall(SYS_gettid));
	signal(2,m);
	printf("This is clone status:%d",clone (add, child_stack+STACK,CLONE_VM | CLONE_FS, NULL));
	while(z!="\n"){
		fscanf(f,"%c",&z);
	}
	signal(2,k);
	kill(getpid(),2);
	while(1);
	printf("%d",l);
	return 0;
}

