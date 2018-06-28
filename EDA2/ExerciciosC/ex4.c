#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	float geral;
	float saude;
	float educ;
	float alim;
}despesas;

typedef struct
{
	int NIF;
	char IC;
	despesas *despesas;
}contribuinte;

void clean (contribuinte *cs, int n)
{
	for (int i = 0; i<n; i++)
	{
		free (cs[i].despesas);
		free (cs);
	}
}

int procura(int n, contribuinte *v, int i, int j)
{
	if (i>j)
		return -1;
		
	int m = (i+j)/2;
	
	if (n<v[m].NIF)
		return procura(n,v,i,m-1);
		
	if (n>v[m].NIF)
		return procura(n,v,m+1,j);
		
	return m;
}

void adiciona_despesa(int pos, contribuinte *cs, char op, float n)
{
	if (op == 'g')
		cs[pos].despesas->geral += n;
	if (op == 's')
		cs[pos].despesas->saude += n;
	if (op == 'e')
		cs[pos].despesas->educ += n;
	if (op == 'a')
	{
		cs[pos].despesas->alim += n;
		cs[pos].despesas->geral += n;
	}
}

void set_conjunta(int c1, int c2, contribuinte *cs, int n)
{
	despesas *conjuntas = malloc(sizeof(despesas));
		
	int pos1 = procura(c1, cs, 0, n-1);
	int pos2 = procura(c2, cs, 0, n-1);
	
	cs[pos1].IC = 'C';
	cs[pos1].despesas = conjuntas;
	
	cs[pos2].IC = 'C';
	cs[pos2].despesas = conjuntas;
}

void set_individuais(contribuinte *cs, int n)
{
	for (int i=0; i<n; i++)
		if (cs[i].despesas == NULL)
			cs[i].despesas = malloc(sizeof(despesas));
}

int main(void)
{
	int ncontrib, nconjuntas;
	scanf ("%d", &ncontrib);
	
	contribuinte *contribuintes = malloc(ncontrib * sizeof(contribuinte));
	
	for (int i=0; i<ncontrib; i++)
	{
		scanf("%d", &contribuintes[i].NIF);
		contribuintes[i].IC = 'I';
	}
	scanf("%d", &nconjuntas);
	
	for (int i=0; i<nconjuntas; i++)
	{
		int c1, c2;
		scanf("%d %d", &c1, &c2);
		set_conjunta(c1, c2, contribuintes, ncontrib);
	}
	set_individuais(contribuintes, ncontrib);

	char op;
	int contrib;
	float value;
	
	while (scanf(" %c %d", &op, &contrib) != EOF)
	{
		if (op == '?')
		{
			int pos = procura(contrib, contribuintes, 0, ncontrib-1);
			if (pos == -1)
				printf("contribuinte sem informacao: %09d\n", contrib);
			else
				printf("%09d [%c] geral%9.2f, saude%9.2f, educ.%9.2f, alim.%9.2f\n", contribuintes[pos].NIF, contribuintes[pos].IC, contribuintes[pos].despesas->geral, contribuintes[pos].despesas->saude, contribuintes[pos].despesas->educ, contribuintes[pos].despesas->alim);
		}
		else
		{
			scanf(" %f", &value);
			int pos = procura(contrib, contribuintes, 0, ncontrib-1);
			adiciona_despesa(pos, contribuintes, op, value);
		}
	}
	//clean (contribuintes, ncontrib);
}
