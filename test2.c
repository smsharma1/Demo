#define _GNU_SOURCE
#include <stdio.h>
#include <signal.h>
#include <sched.h>
#include <stdlib.h>
#include <sys/syscall.h>
int p;
int f(void * k){
printf("pid of child:%d\n",getpid());
printf("%d\n",(int)(int *)k);
*(int*)k=10;
p=102;
sleep(10);
return 0;

}
int main(){
int p=5;
printf("This is parent:%d\n",getpid());
void *child_stack = malloc(16384);
void *  o = &p;
//printf("%d\n",(int)(int *)o);
printf("clone status:%d\n",clone (f, child_stack+16384,CLONE_SIGHAND|CLONE_VM|CLONE_THREAD,o));
sleep(5);
printf("THis is parent:%d\n",p);
while(1);
wait(NULL);
printf("%d\n",p);
return 0;
}
