#include <signal.h>
#include <sched.h>
#include <stdlib.h>
#include <sys/syscall.h>
//int p;
void * h;
int main(){
int p=5;
h=&p;
if(fork() == 0){
	*(int *)h=10;	
}
else{
	wait(NULL);
}
printf("%d\n",p);
return 0;
}

