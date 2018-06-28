#include "list.h"

typedef struct node
{
	unsigned int instante;
	coord *latitude;
	coord *longitude;
	struct node *next;
}node;

static struct node *node_new(unsigned int inst, coord *lat, coord *lon, struct node *next)
{
	node *node = malloc(sizeof(struct node));
	if (node != NULL)
	{
		node->instante = inst;
		node->latitude = lat;
		node->longitude = lon;
		node->next = next;
	}
	return node;
}

typedef struct list
{
	int size;
	struct node *head;
}list;

list *list_new()
{
	list *list = malloc(sizeof(struct list));
	if (list != NULL)
	{
		list -> head = NULL;
		list -> size = 0;
	}
	return list;
}

bool list_insert(struct list *list, unsigned int inst, coord *lat, coord *lon)
{
	node *node = node_new(inst, lat, lon, list->head);
	
	if (node == NULL)
		return false;
		
	list->head = node;
	list->size++;
	
	return true;
}

void list_destroy(list *list)
{
	node * current = list->head;
	node * next = current;
	
	while (current)
	{
		next = current->next;
		free(current->latitude);
		free(current->longitude);
		free(current);
		current = next;
	}
	free(list);
}

bool list_empty(list *lista)
{
	return (lista -> size == 0);
}

list *checkSuspeitos(list *a, list *b)
{
	list *resultado = list_new();
	node *aAtual = a->head;
	node *bAtual = b->head;
	
	while (aAtual && bAtual)
	{
		if (aAtual->instante == bAtual->instante)
		{
			bool c1 = checkCoordenada(aAtual->latitude, bAtual->latitude);
			bool c2 = checkCoordenada(aAtual->longitude, bAtual->longitude);
			if (c1 && c2)
				list_insert(resultado, aAtual->instante, aAtual->latitude, aAtual->longitude);
			aAtual = aAtual->next;
			bAtual = bAtual->next;
		}
		else
			if (aAtual->instante > bAtual->instante)
				aAtual = aAtual->next;
			else
				bAtual = bAtual->next;
	} 
	return resultado;
}

void printComum(list *c, int c1, int c2)
{
	if (list_empty(c))
		printf("+ %05d e %05d nunca se encontraram (aparentemente)\n", c1, c2);
	else
	{
		printf("+ %05d e %05d podem ter-se encontrado em:\n", c1, c2);
		while (c->head)
		{
			printf ("%u %hd %hu' %hu\" %hd %hu' %hu\"\n", c->head->instante, c->head->latitude->graus, 
			c->head->latitude->min, c->head->latitude->seg, c->head->longitude->graus, 
			c->head->longitude->min, c->head->longitude->seg);
			c->head = c->head->next;
		}
	}
}
