#include<setjmp.h>
#include <stdlib.h>
#include <stdio.h>
int g = 1;
int main()
{
	jmp_buf env;
	int i;
	int *p;
	int a[10];
	register int k;
	for (i=0; i<10; i++) a[i] = i;
	p = (int*)malloc(sizeof(int));
	k = a[9];
	(*p) = 0;
	i=setjmp(env);
	printf("i=%d, a[5]=%d, k=%d, *p=%d, g=%d\n", i, a[5], k, *p, g);
	if (i==0) {
		for (i=0; i<10; i++) a[i]++;
		k++;
		(*p)++;
		g++;
	}
	else{
		exit(0);
	}
	printf("a[6]=%d\n", a[6]);
	longjmp(env,2);
	printf("a[7]=%d\n", a[7]);
	return 0;
}
