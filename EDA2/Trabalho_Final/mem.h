#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define TAMANHONICK 6
#define TAMANHONOME 26
#define CAPACIDADEMEM 1100000
#define MAXSEGUIR 100

typedef struct aseguir
{
	char pessoa[TAMANHONICK];
	int lastRead;
}aseguir;

typedef struct utilizador{
	int usado;
	char nick[TAMANHONICK];
	char nome[TAMANHONOME];
	aseguir lseguidos[MAXSEGUIR];
	bool ativo;
	int mensagens_enviadas;
	int seguidores;
	int seguidos;
} utilizador;

FILE *criar_mem(char *nomeFicheiro);
void insere_elemento(FILE *fd, char chave[6] , char nome[26],int ocupados);
utilizador get_utilizador(FILE *fd,int posicao); //retorna o utlizador na posicao da memoria dada pela cache
utilizador get_utilizador_posicao(FILE *fd, int indice); //(para preencher a cache) retorna o utlizador na posicao indice mas assume o ficheiro ja aberto 
void set_utilizador(FILE *fd,utilizador util,int posicao); //reescreve o utilizador dessa posicao da memoria