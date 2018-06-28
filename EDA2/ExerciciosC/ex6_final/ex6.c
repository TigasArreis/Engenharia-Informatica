#include "list.h"

#define MAX 99999

coord *newCoord(short g, unsigned short m, unsigned short s)
{
	coord *novo = malloc(sizeof(coord));
	novo->graus = g;
	novo->min = m;
	novo->seg = s;
	
	return novo;
}

bool checkCoordenada(coord *a, coord *b)
{
	bool graus = a->graus == b->graus;
	bool min = a->min == b->min;
	bool seg = a->seg == b->seg;

	return graus && min && seg;
}

int main(void)
{
	list *suspeitos[MAX] = {NULL};
	int cod;
	unsigned int inst;
	short int graus;
	unsigned short mins, segs;
	
	while (1)
	{
		scanf("%d", &cod);
		if (cod == 0)
			break;
			
		list *atual = suspeitos[cod-1];
			
		if (!atual)
			suspeitos[cod-1] = atual = list_new();
			
		scanf(" %u %hd %hu' %hu\"", &inst, &graus, &mins, &segs);
		coord *lat = newCoord(graus, mins, segs);
		
		scanf(" %hd %hu' %hu\"", &graus, &mins, &segs);
		coord *lon = newCoord(graus, mins, segs);
		
		list_insert(atual, inst, lat, lon);
	}
	
	int cod1, cod2;
	
	while (scanf("%d %d", &cod1, &cod2) != EOF)
	{
		list *a = suspeitos[cod1-1];
		list *b = suspeitos[cod2-1];
		
		if (a == NULL || b == NULL)
		{
			if (a == NULL && b != NULL)
				printf("+ sem dados sobre o suspeito %05d\n", cod1);
			else
				if (a != NULL && b == NULL)
					printf("+ sem dados sobre o suspeito %05d\n", cod2);
				else
					printf("+ sem dados sobre os suspeitos %05d e %05d\n", cod1, cod2);
		}
		else
		{
			list *comum = checkSuspeitos(a,b);
			printComum(comum, cod1, cod2);
			list_destroy(comum);
		}
	}
	for (int i=0; i<MAX; i++)
		if (suspeitos[i])
			list_destroy(suspeitos[i]);
}
