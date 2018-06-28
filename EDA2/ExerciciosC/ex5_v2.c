#include <stdio.h>
#include <stdlib.h>

/* Função que verifica se uma casa  é isolada
 * Se encontrar alguma casa nas 8 posições possiveis
 * retorna 0 (false). 
 * Se não encontrar nenhuma retorna 1 (true).
 * n -> tamanho do array
 * j -> posição (linha) da casa
 * k -> posição (coluna) da casa
 */
int isolada(int n, char zona[n][n], int j, int k)
{
	// Procura casa à esquerda
	if (k-1>=0 && zona[j][k-1] == 'X')
		return 0;
		
	// Procura casa no canto superior esquerdo
	if (j+1<n && k-1>=0 && zona[j+1][k-1] == 'X')
		return 0;

	// Procura casa na posição a cima
	if (j+1<n && zona[j+1][k] == 'X')
		return 0;
	
	// Procura casa no canto superior direito
	if (j+1<n && k+1<n && zona[j+1][k+1] == 'X')
		return 0;

	// Procura casa a direita
	if (k+1<n && zona[j][k+1] == 'X')
		return 0;
		
	// Procura casa no canto inferior direito
	if (j-1>=0 && k+1<n && zona[j-1][k+1] == 'X')
		return 0;
	
	// Procura casa em baixo
	if (j-1>=0 && zona[j-1][k] == 'X')
		return 0;

	// Procura casa no canto inferior esquerdo
	if (j-1>=0 && k-1>=0 && zona[j-1][k-1] == 'X')
		return 0;
		
	return 1;
}

int main(void)
{
	int dim, n_isoladas = 0;
	scanf("%d", &dim);
	
	char zona[dim][dim];
	
	for (int i=0; i<dim; i++)
		scanf("%s", zona[i]);
		
	for (int j=dim-1; j>=0; j--)
		for (int k=0; k<dim; k++)
			if (zona[j][k] == 'X' && isolada(dim, zona, j, k))
				n_isoladas+=1;
	
	if (n_isoladas == 0)
	{
		printf("nao existem habitacoes isoladas\n");
		return 0;
	}
	printf("existem %d habitacoes isoladas:", n_isoladas);
	
	for (int j=dim-1;j>=0;j--)
		for (int k=0; k<dim; k++)
			if (zona[j][k] == 'X' && isolada(dim, zona, j, k) == 1)
				printf(" (%d,%d)", dim-j, k+1);
	printf("\n");
}
