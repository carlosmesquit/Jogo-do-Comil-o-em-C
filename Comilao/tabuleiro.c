#include "tabuleiro.h"


//reserva memória para o tabuleiro e preenche todas as celulas do tabuleiro com o valor "1" (não comido)
void inicia_tabuleiro(int **tabuleiro, int nlin, int ncol)
{
		int i, j;

		for(i=0;i<nlin;i++)
			tabuleiro[i] = (int *) malloc(ncol*sizeof(int)); // em cada linha alocar memoria
			                                                 //percorro as linhas e defino o numero de colunas
                                                            // preenche linhas com comida = valor 1
		for(i=0;i<nlin;i++)
			for(j=0;j<ncol;j++)
				tabuleiro[i][j] = 1; // preenche linhas com comida = valor 1
}

// faz as alterações no tabuleiro e retorna o novo tabuleiro
int **aumenta_tabuleiro(int **tabuleiro, int *nlin, int *ncol)
{
     int j;
	(*nlin)++;
	(*ncol)++;

	tabuleiro = (int **)realloc(tabuleiro, (*nlin)*sizeof(int **));//realocar no tabuleiro o novo valor de linhas e mantem os valores de memoria que estao para tras
	tabuleiro[(*nlin)-1] = (int *) malloc((*ncol)*sizeof(int)); //em termos de coluna é usamos o malloc pois estamos a fazer o malloc numa nova linha, alocar memoria onde nao estava

    for (j=0;j<(*ncol);j++)
        tabuleiro[(*nlin)-1][j] = 1;

	return tabuleiro;
}

//aplica a regra do jogo ou seja, tudo o que está para cima e para trás da linha e coluna atual do tabuleiro, ficam cpom célula vazia (comida)
void atualiza_tabuleiro(int **tabuleiro, int nlin, int ncol, int posactl, int posactc)
{
	int i, j;

	for (i=0;i<posactl;i++)
		for (j=0;j<posactc;j++)
			tabuleiro[i][j] = 0;
}


//envio o tabuleiro como ponteiro, pois o seu valor vai ser alterado em atualiza_tabuleiro

void desenha_tabuleiro(int **tabuleiro, int nlin, int ncol, int jogador, int posactl, int posactc)
{
	int i, j; // mando a n de linhas e colunas para evitar calculos adicionais, atraves do ponteiro tabuleiro conseguiamos ter n de linhas e colunas, mas teriamos os calculos adicionais e aumentava o tempo de execução do programa

	atualiza_tabuleiro(tabuleiro, nlin, ncol, posactl, posactc); // posactl > linha e posactc coluna
    // atualiza o ponteiro tabuleiro com as referencias de localização e remove a comida conforme se desloca
	printf("JOGADOR: %d\n", jogador);
	printf("---");
	for(i=0;i<ncol;i++)
		printf("--");
	printf("\n| |");
	for(i=0;i<ncol;i++)
		printf("%c|", (char)(65+i));

	for(i=0;i<nlin;i++)
	{
		printf("\n|%d|", i+1);
		for(j=0;j<ncol;j++)
		{
			if (posactl == i+1 && posactc == j+1) //verifica se o i+1 e j+1 igual a posicao atual da linha e coluna
 				printf("a"); // se sim a posição for correspondente a igualdade coloca o a no tabuleiro
			else if (i == nlin-1 && j == ncol-1) //se estamos na ultima posicao do tabuleiro
				printf("x"); //se nao estamos no lugar do veneno
			else
			{
				if (tabuleiro[i][j])
					printf("*"); //se for 1 coloca comida
				else
					printf(" ");// se nao coloca vazio que significa que ja foi comido
			}
			printf("|");
		}
	}

	printf("\n---");
	for(j=0;j<ncol;j++)
		printf("--");
	printf("\n\n");
}
