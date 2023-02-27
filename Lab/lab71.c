#include<stdio.h>
#include<omp.h>
#define N 5

int main()
{
	double a[N], b[N];
	int i;
	a[0] = 2;
#pragma omp parallel
	{
	#pragma omp for nowait
		for (i = 1; i < N; i++)
		{
			a[i] = a[i - 1] * a[i - 1];
			b[i] = a[i] + 1;
			printf("a:%g\tb:%g\n", a[i],b[i]);
		}
	}
	b[0] = a[N - 1];
	return 0;
}
