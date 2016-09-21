#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#define N 10
unsigned a[1];
jmp_buf envf, envg;
void schedule (int x)
{
	if (x == 1) 
	{
		if (a[0] > N) printf("\n");
		else longjmp(envg, 2);
	}
	else if (x == 2) 
	{
		if (a[0] > N) printf("\n");
		else longjmp(envf, 1);
	}
}
void f(void)
{
	int i;
	i = setjmp(envf);
	printf("%u ", a[0]);
	a[0]++;
	schedule(i);
}
void g(void)
{
	int i;
	i = setjmp(envg);
	printf("%u ", a[0]);
	a[0] = a[0] + 2;
	schedule(i);
}
main()
{
	a[0] = 0;
	f();
	g();
	schedule(2);
}
