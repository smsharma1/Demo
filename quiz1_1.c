#include<stdio.h>
#include<stdlib.h>

typedef struct {
int x;
} global_t;

global_t * g;

int main(void){
	g=(global_t*)malloc((sizeof(global_t)));
	g->x=7;
	if(fork()==0)
	{
		g->x--;
		if (fork() == 0) 
		{
			g->x++;
			printf("%d,", g->x);
		}
		else 
		{
			g->x--;
		}
		wait(NULL);
		g->x++;
		printf("%d,", g->x);
	}
	else 
	{
		g->x = 3*g->x + 2;
		wait(NULL);
		g->x--;
		printf("%d,", g->x);
	}
	g->x++;
	printf("%d,", g->x);
	return 0;
}
