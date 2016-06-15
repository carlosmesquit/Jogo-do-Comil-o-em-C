#include <stdio.h>
#include <stdlib.h>     /* malloc, realloc */

void inicia_tabuleiro(int **tabuleiro, int nlin, int ncol);
int **aumenta_tabuleiro(int **tabuleiro, int *nlin, int *ncol); // array dinamico bidimensional
void atualiza_tabuleiro(int **tabuleiro, int nlin, int ncol, int posactl, int posactc);
void desenha_tabuleiro(int **tabuleiro, int nlin, int ncol, int jogador, int posactl, int posactc);
