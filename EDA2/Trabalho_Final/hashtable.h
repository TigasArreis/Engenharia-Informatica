#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define TAMANHONICK 6
#define CAPACIDADEHT 2400019

typedef struct consulta{
	char nick[TAMANHONICK];
	int posicao;	//posicao na memoria secundaria
	bool ativo;
	
} consulta;

typedef struct cache{
	
	consulta ** tabela;
	int ocupacao;
} cache;

unsigned int hash(char *);
cache* new_cache();
void destroy_cache(cache *);
void adiciona_elemento(cache * ch,char *nick,bool ativo,int i); //adiciona elemento a cache , incrementa a sua ocupacao
int pesquisa_elemento(cache *,char *nick); //retorna -1 se nao houver e a posciao na memoria secundaria se houver
bool isAtivo(cache *, char *);
consulta *getElemento(cache * ch,char *nick);