#include <stdio.h>
#include <stdlib.h>

int main()
{
	if(fork() == 0 )
	{
		sleep(10);
		printf("I am child %d of parent %d\n",getpid(),getppid());	
	}
	else
	{
		printf("I am the process %d\n",getpid());
	}
	return 0;
}
