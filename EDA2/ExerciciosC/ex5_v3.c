#include <stdio.h>
#include <stdlib.h>

/* Verifica se uma casa e isolada
 * Se encontrar alguma casa nas 8 posições possiveis
 * retorna 0 (false). 
 * Se nao encontrar nenhuma retorna 1 (true).
 * n -> tamanho do array
 * j -> posição (linha) da casa
 * k -> posição (coluna) da casa
 */
int isolada(int n, char zona[n][n], int j, int k)
{
	// Procura casa a esquerda
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
	int *isox = malloc(sizeof(int));
	int *isoy = malloc(sizeof(int));
	
	for (int i=0; i<dim; i++)
		scanf("%s", zona[i]);
				
	for (int j=dim-1; j>=0; j--)
		for (int k=0; k<dim; k++)
			if (zona[j][k] == 'X' && isolada(dim, zona, j, k))
			{
				isox = realloc(isox, (n_isoladas+1) * sizeof(int));
				isoy = realloc(isoy, (n_isoladas+1) * sizeof(int));
				isox[n_isoladas] = dim-j;
				isoy[n_isoladas++] = k+1;
			}
		
	if (n_isoladas>0)
	{
		printf("existem %d habitacoes isoladas:", n_isoladas);
				
		for (int i=0; i<n_isoladas; i++)
			printf(" (%d,%d)", isox[i], isoy[i]);
	}
	else
		printf("nao existem habitacoes isoladas");
	
	free(isox);
	free(isoy);
	printf("\n");
}