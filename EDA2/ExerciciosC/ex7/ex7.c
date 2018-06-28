#include <stdio.h>

void printLab(int A, int L, char lab[][L])
{
	for (int i=0; i<A; i++)
	{	
		for (int j=0; j<L; j++)
			printf("%c", lab[i][j]);
		printf("\n");
	}
}

/* Procura solução
 * A -> Altura do labirinto
 * L -> Largura do labirinto
 * lab -> Matriz com o labirinto.
 * aux -> Matriz auxilar com os sitios já percorridos
 * x e y -> chamados a 0 é a posição inicial onde se começa a procurar
 * 
 * O algoritmo funciona de forma muito simples, recursivamente vai 
 * verificar, avançando no labirinto através de x e y, se é possivel encontrar solução
 * (chegar à posição (A-1, L-1) do labirinto) através de casas acessiveis
 * que são o '.'. Caso encontre um obstaculo retorna false (0) e procura
 * outro caminho. da mesma forma, se já não houver caminhos, retorna false.
 **/

int resolveLab(int A, int L, char (*lab)[L], int (*aux)[L], int x, int y)
{
	if (lab[x][y] != '.' || aux[x][y])
		return 0;
		
	aux[x][y] = 1;
	
	if (x == A-1 && y == L-1)
	{
		lab[x][y] = 'o';
		return 1;
	}
	if (y != 0)
		if (resolveLab(A, L, lab, aux, x, y-1))
		{
			lab[x][y] = 'o';
			return 1;
		}
	if (y != L-1)
		if (resolveLab(A, L, lab, aux, x, y+1))
		{
			lab[x][y] = 'o';
			return 1;
		}
	if (x != 0)
		if (resolveLab(A, L, lab, aux, x-1, y))
		{
			lab[x][y] = 'o';
			return 1;
		}
	if (x != A-1)
		if (resolveLab(A, L, lab, aux, x+1, y))
		{
			lab[x][y] = 'o';
			return 1;
		}
	return 0;
}

int main(void)
{
	short L, A;
	scanf("%hd %hd", &L, &A);
	
	char lab[A][L];
	
	for (int i=0; i<A; i++)
		scanf("%s", lab[i]);
		
	int aux[A][L];
	
	for (int i=0; i<A; i++)
		for (int j=0; j<L; j++)
			aux[i][j] = 0;
			
	if (resolveLab(A, L, lab, aux, 0, 0))
		printLab(A, L, lab);
	else
		printf("+ sem caminho\n");
}
