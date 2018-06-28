#include <stdio.h>
#include <stdlib.h>

long long int max_soma(long int *seq, int nsub, int nseq)
{	
	long long int resultado = 0;
	
	for (int i=0; i<nseq; i+=nsub)
	{
		int indice = i;
		for (int j=i; j<i+nsub && j<nseq; j++)
			if (seq[j]>seq[indice])
				indice = j;
		resultado += seq[indice];
	}
	return resultado;
}

long long int min_soma(long int *seq, int nsub, int nseq)
{
	long long int resultado = 0;
	
	for (int i=0; i<nseq; i+=nsub)
	{
		int indice = i;
		for (int j=i; j<i+nsub && j<nseq; j++)
			if (seq[j]<seq[indice])
				indice = j;
		resultado += seq[indice];
	}
	return resultado;
}

int main(void)
{
	int total;
	if (scanf("%d",&total) < 1 || total < 1)
		return 0;
	
	long int seq[total];
	
	for (int i=0; i<total; i++)
		scanf("%ld\n",&seq[i]);
	
	char tipo;
	int subseqs;
	
	while (scanf(" %c %d", &tipo, &subseqs) != EOF)
	{
		if (tipo == 'M')
			printf("+ max %lld\n", max_soma(seq, subseqs, total));
		else
			printf("+ min %lld\n", min_soma(seq, subseqs, total));
	}
}
