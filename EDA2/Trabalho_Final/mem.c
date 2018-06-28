#include "mem.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


FILE *criar_mem(char *nomeFicheiro)
{
	FILE *fd;
	utilizador util;

	memset(&util, 0 ,sizeof(utilizador));
	
	fd = fopen(nomeFicheiro, "wb");
	
	if(fd == NULL)
	{
		perror("erro a criar tabela\n");
		exit(0);
	}
	return fd;
}

void insere_elemento(FILE *fd,char nick[6], char nome[26],int ocupados)
{
	utilizador util = {};

	strcpy(util.nome,nome);
	strcpy(util.nick,nick);
	util.usado = 1;
	util.ativo = true;
	util.mensagens_enviadas = 0;
	util.seguidores = 0;
	util.seguidos = 0;
	
	fseek(fd,ocupados*sizeof(utilizador), SEEK_SET);
	fwrite(&util, sizeof(utilizador),1,fd);
}

utilizador get_utilizador(FILE *fd,int posicao)
{
	utilizador util;
	
	fseek(fd,posicao*sizeof(utilizador), SEEK_SET);
	fread(&util, sizeof(utilizador),1,fd);
	
	return util;
}

utilizador get_utilizador_posicao(FILE *fd,int indice)
{
	utilizador util;

	fseek(fd,indice*sizeof(utilizador), SEEK_SET);
	fread(&util, sizeof(utilizador),1,fd);
	
	return util;
}
void set_utilizador(FILE *fd,utilizador util,int posicao)
{	
	fseek(fd,posicao*sizeof(utilizador), SEEK_SET);
	fwrite(&util, sizeof(utilizador),1,fd);
}