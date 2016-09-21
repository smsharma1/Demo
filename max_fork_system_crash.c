#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main()
{
	int i;
	for(i=0;i<5;i++)
	{
		if(fork()==0)
		{
			printf("This is child %d of parent %d in if\n",getpid(),getppid());	
		}
		else
		{
			wait(NULL);
			printf("This is child %d of parent %d in else\n",getpid(),getppid());
		}
	}
	return 0;
}
