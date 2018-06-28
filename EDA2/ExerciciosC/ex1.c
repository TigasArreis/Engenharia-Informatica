#include <stdio.h>

int div_natural(int x,int n)
{
	if (n%x==0)
		return 1;
	else
		return 0;
}

int main(void)
{
	int n=15180;
	int divisores=0;
	for (int i=2;i<n;i++)
		if (div_natural(i,n))
		{
			printf("%d\n",i);
			divisores+=1;
		}
	printf("+ %d tem %d divisores\n",n,divisores);
	return 0;
}
