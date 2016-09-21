#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main()
{
	FILE *fp;
	int i;
	char a;
	fp = fopen("fork.txt","r");
	if(fork()==0)
	{	
		printf("This is child buddy\n");
		for(i=0;i<5;i++)
		{
			fscanf(fp,"%c",&a);
			printf("%c",a);
		}
	}
	else
	{
		 printf("This is parent buddy\n");
		 for(i=0;i<5;i++)
                {
                        fscanf(fp,"%c",&a);
                        printf("%c",a);
                }

	}
	return 0; 
}
