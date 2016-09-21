#define _GNU_SOURCE
#include <signal.h>
#include <stdlib.h>
#include <sched.h>
#include <stdio.h>
#define CHILD_STACK 16384
int count = 0;
int loop (void *arg)
{
	while(1);
}
void catcher (int signo)
{
	count++;
}
int main (void)
{
	int i, pid;
	void *child_stack;
	for (i=1; i<=19; i++) {
		signal(i, catcher);
	}
	child_stack = malloc(CHILD_STACK);
	pid = clone (loop, child_stack+CHILD_STACK, SIGCHLD | CLONE_VM, NULL);
	wait(NULL);
	return 0;
}
