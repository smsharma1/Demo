#include <stdio.h>
#include <stdlib.h>
#define N 1000
#define K 20
int main (void)
{
	int i, j;
	unsigned long long sum=0;
	for (i=0; i<K; i++) 
	{
		for (j=0; j<N; j++) sum++;
	}
	printf("%llu\n", sum);
	return 0;
}
