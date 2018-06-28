#include <stdio.h>
#include <stdlib.h>

struct pedido
{
	char tipo;
	int subseq;
};

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
	int nseq;
	if (scanf("%d",&nseq) < 1 || nseq <1)
		return 0;
	
	long int seq[nseq];
	
	for (int i=0; i<nseq; i++)
		scanf("%ld\n",&seq[i]);
	
	int n_pedido = 0;
	struct pedido *pedidos = malloc(sizeof(struct pedido));
	
	while (scanf(" %c %d", &pedidos[n_pedido].tipo, &pedidos[n_pedido].subseq) != EOF)
	{
		malloc(sizeof(struct pedido));
		n_pedido++;
	}
	for (int i=0; i<n_pedido; i++)
		if (pedidos[i].tipo == 'M')
			printf("+ max %lld\n", max_soma(seq, pedidos[i].subseq, nseq));
		else
			printf("+ min %lld\n", min_soma(seq, pedidos[i].subseq, nseq));
}
