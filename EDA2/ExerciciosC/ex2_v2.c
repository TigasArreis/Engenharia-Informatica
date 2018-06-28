#include <stdio.h>

int main(void)
{
	int n;
	scanf("%d", &n);
	
	long int seq1[n];
	
	for (int i=1; i<=n; i++)
		scanf("%ld", &seq1[i]);
	
	int m;
	scanf("%d", &m);
	
	int seq2[m];
	
	for (int j=1; j<=m; j++)
		scanf("%d", &seq2[j]);
		
	for (int k=1; k<=m; k++)
		if (seq2[k]>0 && seq2[k]<=n)
			printf("valor @ %d = %ld\n", seq2[k], seq1[seq2[k]]);
		else
			printf("valor @ %d = -\n", seq2[k]);
}
