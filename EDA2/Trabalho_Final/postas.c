#include "mem.h"
#include "hashtable.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define FILENAME "memoria.dat"

// Inserir elemento usando o insertSorted
int insertSorted(aseguir arr[], int n, aseguir elm)
{
	if (n >= MAXSEGUIR)
		return -1;

	int i;

	for (i = n-1; i>=0 && strcmp(arr[i].pessoa, elm.pessoa)>0; i--)
		arr[i+1] = arr[i];

	arr[i+1] = elm;

	return (n+1);
}

// Faz uma procura binria nos seguidores
int procuraSeguidor(aseguir arr[], int l, int r, char nome[TAMANHONICK])
{
	if (r >= l)
	{
		int meio = l+(r-l)/2;

		if (strcmp(arr[meio].pessoa, nome) == 0)
			return meio;

		if (strcmp(arr[meio].pessoa, nome) > 0)
			return procuraSeguidor(arr, l, meio-1, nome);

		return procuraSeguidor(arr, meio+1, r, nome);
	}

	return -1;
}

// Apaga o seguidor, se existir, e move os elementos para a esquerda
int apagaSeguidor(aseguir arr[], char nome[TAMANHONICK], int tam)
{
	int pos = procuraSeguidor(arr, 0, tam-1, nome);

	if (pos == -1)
		return pos;

	for (int i = pos; i<tam; i++)
	{
		arr[pos] = arr[pos+1];
		pos++;
	}

	return 1;
}

int enviaMensagem(utilizador *x)
{
	if (x == NULL)
		return 0;

	x->mensagens_enviadas++;
	
	return 1;
}

void printUtilizador(utilizador *x)
{
	printf("utilizador %s (%s)\n", x->nick, x->nome);	
	printf("%d mensagens, %d seguidores, segue %d utilizadores\n", x->mensagens_enviadas, x->seguidores, x->seguidos);

	for (int i = 0; i < x->seguidos; i++)
		printf("%s (%d lidas)\n", x->lseguidos[i].pessoa, x->lseguidos[i].lastRead);
}

// Utilizador X vai seguir Y
int segueUtilizador(utilizador *x, utilizador *y)
{
	if (procuraSeguidor(x->lseguidos, 0, x->seguidos-1, y->nick) != -1)
	{
		printf("+ utilizador %s segue %s\n", x->nick, y->nick);
		return -1;
	}

	if (x->seguidos == MAXSEGUIR)
	{
		printf("+ utilizador %s segue o limite\n", x->nick);
		return -1;
	}

	aseguir novoaseguir = {{}, y->mensagens_enviadas};
	strcpy(novoaseguir.pessoa,y->nick);

	insertSorted(x->lseguidos, x->seguidos, novoaseguir);

	x->seguidos++;
	y->seguidores++;

	printf("+ %s passou a seguir %s\n", x->nick, y->nick);

	return 1;
}

//Utilizador X vai deixar de seguir Y
int unfollowUtilizador(utilizador *x, utilizador *y)
{
	if (procuraSeguidor(x->lseguidos, 0, x->seguidos-1, y->nick) == -1)
	{
		printf("+ utilizador %s nao segue %s\n", x->nick, y->nick);
		return -1;
	}

	apagaSeguidor(x->lseguidos, y->nick, x->seguidos);

	x->seguidos--;
	y->seguidores--;

	if (y->ativo == 1)
		printf("+ %s deixou de seguir %s\n", x->nick, y->nick);

	return 1;
}

int leMensagens(utilizador *x,cache *ch,FILE *fd)
{
	if (x->seguidos == 0)
	{
		printf("+ utilizador %s sem seguidos\n", x->nick);
		return -1;
	}

	for (int i=0; i < x->seguidos; i++)
	{
		if (isAtivo(ch, x->lseguidos[i].pessoa) == false)
		{
			printf("utilizador %s desactivado\n", x->lseguidos[i].pessoa);
			apagaSeguidor(x->lseguidos, x->lseguidos[i].pessoa, x->seguidos);
			x->seguidos--;
			i--;
		}
		else
		{
			utilizador temp;
			int pos;

			pos = pesquisa_elemento(ch,x->lseguidos[i].pessoa);
			temp = get_utilizador(fd,pos);

			if (x->lseguidos[i].lastRead == temp.mensagens_enviadas)
				printf("sem mensagens novas de %s (%s)\n", temp.nick, temp.nome);
			if (temp.mensagens_enviadas - x->lseguidos[i].lastRead == 1)
				printf("mensagem nova de %s (%s): %d\n", temp.nick, temp.nome, temp.mensagens_enviadas);
			if (temp.mensagens_enviadas - x->lseguidos[i].lastRead > 1)
				printf("mensagens novas de %s (%s): %d a %d\n", 
						temp.nick, temp.nome, x->lseguidos[i].lastRead+1, temp.mensagens_enviadas);

			x->lseguidos[i].lastRead = temp.mensagens_enviadas;
		}
	}

	return 1;
}

void carregar_cache(FILE *fd,cache *ch)
{
	int ocupacao = 0;
	utilizador util;

	while(fread(&util , sizeof(utilizador), 1, fd) != 0)
	{
		adiciona_elemento(ch, util.nick, util.ativo, ocupacao);
		ocupacao++;
	}
	ch->ocupacao = ocupacao;
}

int main()
{	
	FILE *fd = fopen(FILENAME,"rb+");
	
	if (!fd)
	{
		fd = criar_mem(FILENAME);
		fclose(fd);
		fd = fopen(FILENAME,"rb+");
	}
	
	char nome[TAMANHONOME];
	char nick[TAMANHONICK];
	char nick2[TAMANHONICK];

	utilizador temporario;
	utilizador temporario2;
	int pos;
	int pos2;
	
	cache * cache;
	cache = new_cache();
	carregar_cache(fd,cache);	//carrega a cache com os dados da memoria secundaria
	
	char opcao;

	while(scanf("%c", &opcao)!=EOF)
	{	
		switch(opcao) 
		{
			case 'U':	//criar utilizador
				scanf("%5s %25[^\n]", nick,nome);

				if(pesquisa_elemento(cache,nick)==-1)
				{
					insere_elemento(fd,nick,nome,cache -> ocupacao);
					adiciona_elemento(cache,nick,true, cache -> ocupacao);
					cache -> ocupacao++;
					printf("+ utilizador %s criado\n", nick);
				}
				else
					printf("+ nick %s usado previamente\n", nick);
				break;
			
			case 'R':	//remover utilizador
				scanf("%s", nick);
				if (isAtivo(cache, nick))
				{
					pos = pesquisa_elemento(cache,nick);
					{
						if (pos != -1)
						{
							temporario = get_utilizador(fd,pos);
							temporario.ativo = false;
							getElemento(cache,nick)->ativo = false;
							set_utilizador(fd, temporario, pos);
							printf("+ utilizador %s removido\n", nick);
						}
						else
							printf("+ utilizador %s inexistente\n", nick);
					}
				}
				else
					printf("+ utilizador %s inexistente\n", nick);
				break;

			case 'S':	//seguir utilizador
				scanf("%s %s", nick, nick2);

				if (isAtivo(cache,nick))
				{
					if (!isAtivo(cache,nick2))
						printf("+ utilizador %s inexistente\n", nick2);
					else
					{
						pos = pesquisa_elemento(cache,nick);
						pos2 = pesquisa_elemento(cache,nick2);

						temporario = get_utilizador(fd,pos);
						temporario2 = get_utilizador(fd,pos2);

						int podeSeguir = segueUtilizador(&temporario, &temporario2);

						if (podeSeguir != -1)
						{
							if (strcmp(nick, nick2) == 0)
							{
								temporario.seguidores++;
								set_utilizador(fd, temporario, pos);
							}
							else
							{
								set_utilizador(fd, temporario, pos);
								set_utilizador(fd, temporario2, pos2);
							}
						}
					}
				}
				else
					printf("+ utilizador %s inexistente\n", nick);

				break;
			case 'D': //deixar de seguir utilizador
				scanf("%s %s", nick, nick2);

				if (isAtivo(cache,nick))
				{
					if (!isAtivo(cache,nick2))
						printf("+ utilizador %s inexistente\n", nick2);
					else
					{
						pos = pesquisa_elemento(cache,nick);
						pos2 = pesquisa_elemento(cache,nick2);

						temporario = get_utilizador(fd,pos);
						temporario2 = get_utilizador(fd,pos2);

						int podeNSeguir = unfollowUtilizador(&temporario, &temporario2);

						if (podeNSeguir != -1)
						{
							if (strcmp(nick, nick2) == 0)
							{
								temporario.seguidores--;
								set_utilizador(fd, temporario, pos);
							}
							else
							{
								set_utilizador(fd, temporario, pos);
								set_utilizador(fd, temporario2, pos2);
							}
						}
					}
				}
				else
					printf("+ utilizador %s inexistente\n", nick);
				break;

			case 'P':	//enviar mensagem
				scanf("%s", nick);

				if (isAtivo(cache,nick))
				{
					pos = pesquisa_elemento(cache,nick);
					temporario = get_utilizador(fd,pos);
					enviaMensagem(&temporario);
					set_utilizador(fd, temporario, pos);
				}
				else 
					printf("+ utilizador %s inexistente\n", nick);
				break;

			case 'L':	//ler mensagem
				scanf("%s", nick);

				if (isAtivo(cache,nick))
				{
					pos = pesquisa_elemento(cache,nick);
					temporario = get_utilizador(fd,pos);
					leMensagens(&temporario, cache,fd);
					set_utilizador(fd, temporario, pos);
				}
				else 
					printf("+ utilizador %s inexistente\n", nick);
				break;
			case 'I':	//obter informacoes
				scanf("%s", nick);

				if (isAtivo(cache,nick))
				{
					pos = pesquisa_elemento(cache,nick);
					utilizador temporario = get_utilizador(fd,pos);
					printUtilizador(&temporario);
				}
				else 
					printf("+ utilizador %s inexistente\n", nick);

				break;
			case 'X':	//sair
				destroy_cache(cache);
				fclose(fd);
				return 0;
		}			
	}
}
