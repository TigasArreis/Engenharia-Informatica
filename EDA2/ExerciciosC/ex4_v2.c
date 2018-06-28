#include <stdio.h>
#include <stdlib.h>

typedef struct despesas
{
	float geral;
	float saude;
	float educ;
	float alim;
}despesas;

typedef struct contribuinte
{
	int NIF;
	char IC;
	despesas *despesas;
}contribuinte;

despesas *newDespesas()
{
	despesas *novo = malloc(sizeof(despesas));
	if (novo == NULL)
		return NULL;
	novo->geral = 0; 
	novo->saude = 0;
	novo->educ = 0;
	novo->alim = 0;
	return novo;
}

contribuinte *newContrib()
{
	contribuinte *novo = malloc(sizeof(contribuinte));
	if (novo == NULL)
		return NULL;
	novo->NIF = 0;
	novo->IC = 'I';
	novo->despesas = NULL;
	return novo;
}

int procura(int n, contribuinte *v[], int i, int j)
{
	if (i>j)
		return -1;
		
	int m = (i+j)/2;
	
	if (n<v[m]->NIF)
		return procura(n,v,i,m-1);
		
	if (n>v[m]->NIF)
		return procura(n,v,m+1,j);
		
	return m;
}

void clean (contribuinte *cs[], int n)
{
	for (int i=0; i<n; i++)
		if (cs[i]->IC == 'C' && cs[i]->despesas->geral>=0)
		{
			cs[i]->despesas->geral = -1;
			free (cs[i]);
		}
		else
		{
			free (cs[i]->despesas);
			free (cs[i]);
		}
}

void addDespesa(despesas *c, char op, float n)
{
	if (op == 'g')
		c->geral += n;
	if (op == 's')
		c->saude += n;
	if (op == 'e')
		c->educ += n;
	if (op == 'a')
	{
		c->alim += n;
		c->geral += n;
	}
}

void setConjunta(contribuinte *c1, contribuinte *c2)
{		
	c1->IC = c2->IC = 'C';
	c1->despesas = newDespesas();
	c2->despesas = c1->despesas;
}

int main(void)
{
	int ncontrib, nconjuntas=0;
	scanf ("%d", &ncontrib);
	
	contribuinte *lista[ncontrib];
	
	for (int i=0; i<ncontrib; i++)
	{
		lista[i] = newContrib();
		scanf("%d", &lista[i]->NIF);
	}
	scanf("%d", &nconjuntas);
	
	for (int i=0; i<nconjuntas; i++)
	{
		int c1, c2;
		scanf("%d %d", &c1, &c2);
		int pos1 = procura(c1, lista, 0, ncontrib-1);
		int pos2 = procura(c2, lista, 0, ncontrib-1);
		setConjunta(lista[pos1], lista[pos2]);
	}
	for (int i=0; i<ncontrib && lista[i]->IC == 'I'; i++)
		if(lista[i]->IC == 'I')
			lista[i]->despesas = newDespesas();

	char op;
	int contrib;
	float value;
	
	while (scanf(" %c %d", &op, &contrib) != EOF)
	{
		if (op == '?')
		{
			int pos = procura(contrib, lista, 0, ncontrib-1);
			if (pos == -1)
				printf("contribuinte sem informacao: %09d\n", contrib);
			else
				printf("%09d [%c] geral%9.2f, saude%9.2f, educ.%9.2f, alim.%9.2f\n", lista[pos]->NIF, lista[pos]->IC, lista[pos]->despesas->geral, lista[pos]->despesas->saude, lista[pos]->despesas->educ, lista[pos]->despesas->alim);
		}
		else
		{
			scanf(" %f", &value);
			int pos = procura(contrib, lista, 0, ncontrib-1);
			addDespesa(lista[pos]->despesas, op, value);
		}
	}
	clean(lista, ncontrib);
}			
