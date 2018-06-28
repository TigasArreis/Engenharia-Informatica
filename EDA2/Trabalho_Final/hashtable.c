#include "hashtable.h"

unsigned int hash(char *string)
{
	
	unsigned int hash = 5381;
    int c;

    while ((c = *string++))
        hash = ((hash << 5) + hash) + c; 
		
	hash %= CAPACIDADEHT;
	
	return hash;
}


cache* new_cache()
{
	cache *ch = malloc(sizeof(cache));
	
	ch -> tabela = malloc(sizeof(consulta*)*CAPACIDADEHT);

	int i = 0;

	for( i = 0; i < CAPACIDADEHT; i++ )
		ch->tabela[i] = NULL;

	ch -> ocupacao = 0;

	return ch;
	
}
consulta* new_consulta(char *nick)
{
	consulta * novo = malloc(sizeof(consulta));
	
	strcpy(novo->nick,nick);
	
	return novo;
	
}
void destroy_cache(cache *ch)
{
	if(ch == NULL) return;

	for (int i=0; i < CAPACIDADEHT; i++)
	{
		if (ch -> tabela[i] != NULL)
			free(ch -> tabela[i]);
	}
	free(ch -> tabela);
	free(ch);
}
	
void adiciona_elemento(cache * ch,char *nick,bool ativo,int i)
{
	consulta * novo = new_consulta(nick);
	
	novo -> posicao = i;
	novo -> ativo = ativo;
	int pos = hash(nick);
	
	while(1)
	{
		if(ch -> tabela[pos]!=NULL)
			pos++;
		else
			break;
	}
	ch -> tabela[pos] = novo;
}

int pesquisa_elemento(cache * ch,char *nick)
{
	int pos = hash(nick);
	
	while(1)
	{
		if(ch -> tabela[pos] == NULL)
			return -1;
		if(strcmp(nick, ch -> tabela[pos] -> nick)==0)
			return ch -> tabela[pos] -> posicao;
		
		pos++;
	}
}

consulta *getElemento(cache * ch,char *nick)
{
	int pos = hash(nick);
	
	while(1)
	{
		if(ch -> tabela[pos] == NULL)
			return NULL;
		if(strcmp(nick, ch -> tabela[pos] -> nick)==0)
			return ch -> tabela[pos];
		
		pos++;
	}
}

bool isAtivo(cache *ch, char *nick)
{
	int pos = hash(nick);

	while(1)
	{
		if(ch -> tabela[pos] == NULL)
			return false;

		if(strcmp(nick, ch -> tabela[pos] -> nick)==0)
			return ch -> tabela[pos] -> ativo;

		pos++;
	}
}