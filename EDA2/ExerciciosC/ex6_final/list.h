#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct coordenada
{
	short int graus;
	unsigned short int min;
	unsigned short int seg;
}coord;

struct list;
struct list *list_new();
typedef struct list list;
bool list_insert(struct list *list, unsigned int inst, coord *lat, coord *lon);
void list_destroy(struct list *list);
list *checkSuspeitos(list *a, list *b);
bool checkCoordenada(coord *a, coord *b);
void printComum(list *c, int c1, int c2);
bool list_empty(struct list *lista);
