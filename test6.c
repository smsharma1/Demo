#define _GNU_SOURCE
#include <stdio.h>
#include <signal.h>
#include <sched.h>
#include <stdlib.h>
#include <sys/syscall.h>
#define MSGKEY 25
int a;
typedef struct {
	long type;
	char buf[64];
} msg_t;

int f(void * m)
{
a=20;
printf("THis is sibling\n");
while(1);
}

int main()
{
msg_t msg;
a=2;
void *child_stack = malloc(16384);
printf("This is main Thread:%d\n",getpid());
clone(f, child_stack+16384, CLONE_VM | CLONE_THREAD | CLONE_SIGHAND, NULL);
//sleep(1);
if(fork() == 0)
{
sleep(1);
 printf("%d\n",a);	
}
//sleep(1);
else{
printf("%d\n",a);
}
return 0;
}
