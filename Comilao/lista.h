#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <dirent.h>

typedef struct objeto jogada, *pjogada;

struct objeto
{
    int jogador; //1 ou 2...A ou B
    int linha; //linha
    int col; //e coluna atualmente selecionada
    pjogada prox; //apontador para o proximo elemento da lista
};

int lista_vazia (pjogada lista);
pjogada lista_inserir(pjogada lista, int j, int linha, int col);
int lista_gravar(char *nomefich, pjogada lista, int automatico, int nlin, int ncol);
pjogada lista_ler(char *nomefich, int *automatico, int *nlin, int *ncol);
int lista_tamanho(pjogada lista);
void lista_libertar(pjogada lista);
