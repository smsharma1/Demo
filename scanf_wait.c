#include<stdio.h>
#include<stdlib.h>
int main()
{
	int a;
	if(fork()==0)
	{
		printf("I am child bro\n");
		scanf("%d",&a);
	}
	else
	{
		sleep(5);
		printf("dude I am parent\n");
		wait(NULL);
		printf("I am parent bro\n");
	}
	return 0;
}
