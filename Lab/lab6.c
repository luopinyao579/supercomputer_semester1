#include<stdio.h>
#include<omp.h>

int main(void)
{
	int i, n = 0;
	int sum = 0;
	printf("entre the values of i and n:\n");
	scanf("%d%d", &i, &n);
#pragma omp parellel for
	for (i; i <= n; i++)
	{
		if (i % 2 == 0)
		{
			sum += i;
			printf("The correct number is  :%d\n", i);
		}
	}
	printf("result:%d\n", sum);
		return 0;
}
