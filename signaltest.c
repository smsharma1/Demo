#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/time.h>

int main()
{
	int i;
	signal(SIGCHLD,1);
	for(i=0;i<5;i++){
		if(fork()==0)
		{
			printf("I am a child %d of parent %d\n",getpid(),getppid());
			exit(0);
		}
	}
	printf("This is parent before main\n");
	printf("%d\n",wait(NULL));
	printf("I am a process %d\n",getpid());
	return 0;
}
