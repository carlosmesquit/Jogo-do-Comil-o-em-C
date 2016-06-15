/*


           _
          (_) ___   __ _  ___
          | |/ _ \ / _` |/ _ \
          | | (_) | (_| | (_) |
         _/ |\___/ \__, |\___/
        |__/       |___/
                             _ _
          ___ ___  _ __ ___ (_) | __ _  ___
         / __/ _ \| '_ ` _ \| | |/ _` |/ _ \
        | (_| (_) | | | | | | | | (_| | (_) |
         \___\___/|_| |_| |_|_|_|\__,_|\___/



       INSTITUTO SUPERIOR DE ENGENHARIA DE COIMBRA - 2015/2016
       PROGRAMAÇÃO 2º SEMESTRE - TRABALHO PRÁTICO
       TEMA: JOGO DO COMILÃO
       ALUNO: 21240707
       EMAIL: A21240707@ALUNOS.ISEC.PT


*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "lista.h"
#include "tabuleiro.h"

#define MIN_LIN 4
#define MAX_LIN 8
#define MIN_COL 6
#define MAX_COL 10

// inicio do jogo
void inicio(int *l, int *c)
{
	do {
        system("cls");
        printf("\n   ============ INICIO DO JOGO DO COMILAO ===============\n\n");

		printf("\nQUAL O NUMERO DE LINHAS (Entre %d e %d): ", MIN_LIN, MAX_LIN);
		scanf("%d", l);
	} while (*l < MIN_LIN || *l > MAX_LIN);

	do {
		printf("\nQUAL O NUMERO DE COLUNAS (Entre %d e %d e > %d): ", MIN_COL, MAX_COL, *l);
		scanf("%d", c);
	} while (*c < MIN_COL || *c > MAX_COL || *c <= *l);
	printf("\n\n");
	fflush(stdin); //para limpar o buffer
}


//equivale ao lista_mostrar
void mostrar_jogadas(pjogada lista, int **tabuleiro, int nlin, int ncol)
{
	while(lista != NULL)
	{
		desenha_tabuleiro(tabuleiro, nlin, ncol, lista->jogador, lista->linha, lista->col);
		lista = lista->prox;
	}

}

/*
vai perguntar ao jogador qual a jogada, e retorna nas variaveis enviadas por referência (ponteiro) a linha e coluna selecionada
enviamos o tabuleiro como ponteiro, pois foi assim que o professor deu nas aulas teóricas como a melhor maneira de enviar um array dinâmico
*/

int set_jogada(int **tabuleiro, int nlin, int ncol, int automatico, int jogador, int *posactl, int *posactc)
{
	int l=0, c=0, maxl, maxc;
	char col;
	int valida;
	int terminou = 0;

	if (automatico)
	{
		printf("JOGADOR %d (automático)\n", jogador);

		srand (time(NULL));
		do
		{
			if (*posactl + 2 > nlin)
				maxl = nlin + 1;
			else
				maxl = *posactl + 2;

			if (*posactc + 2 > ncol)
				maxc = ncol + 1;
			else
				maxc = *posactc + 2;

			l = rand() % maxl; //gera uma linha aleatoria na linha atual + 1 (a mais proxima)
			c = rand() % maxc; //gera uma coluna aleatoria na coluna atual + 1 (a mais proxima)

			//não pode ser "0"
			if (!l)
				l++;
			if (!c)
				c++;

            if (l == nlin-1 && c == ncol-1)
                terminou = 1;

		} while (tabuleiro[l-1][c-1] == 0 && !terminou); //verifica se a celula está vazia. senão está, então é valida. -1 pk a linha que o jogador coloca é de 1 a nlin e nao de 0 a nlin-1. Para ncol é o mesmo

		*posactl = l;
		*posactc = c;
		return 1;
	}
	else
	{
		do
		{
			valida = 1;

			printf("JOGADOR %d, qual a linha para onde pretende jogar?\n", jogador);
			scanf("%d", &l);


			if (l > nlin || !l)
				valida = 0;

			if (valida && l != -1)
			{
			    fflush(stdin); //para limpar o buffer
				printf("JOGADOR %d, qual a coluna para onde pretende jogar?\n", jogador);
				col = getchar();
				col = toupper(col);
       			c = (int)(col)-64;

				if (c > ncol || !c)
                    valida = 0;
			}

			if (valida && c && l)
			{
				//verificar se o c e o l têm comida. Caso contrário não pode jogar para lá
				if (tabuleiro[l-1][c-1] == 0) //-1 pk a linha que o jogador coloca é de 1 a nlin e nao de 0 a nlin-1. Para ncol é o mesmo
				{
					printf("JOGADA INVALIDA: Deve jogar para uma posição com comida\n");
					valida = 0;
				}
			}
			else if (!valida)
                printf("JOGADA INVALIDA: Deve jogar para uma posição do tabuleiro valida e com comida\n");
		} while (!valida);

		//getchar(); //para limpar o buffer
		fflush(stdin); //para limpar o buffer
		if (!l || !c)
			return 0;
		else
		{
			*posactl = l;
			*posactc = c;
			return 1;
		}
	}
}

int menu()
{
	int op=0;

	do
	{
    // texto em ASCII FEITO ATRAVÉS DE http://patorjk.com/software/taag/#p=display&f=Ogre&t=jogo%0Acomilao

	system("cls");

	printf("  (_) ___   __ _  ___\n");
    printf("  | |/ _ %\\ / _` |/ _ %\\ \n");
    printf("  | | (_) | (_| | (_) | \n");
    printf(" _/ |%\\___/ %\\__, |%\\___/ \n");
    printf("|__/       |___/ \n");

    printf("                     _ _ \n");
    printf("  ___ ___  _ __ ___ (_) | __ _  ___ \n");
    printf(" / __/ _ %\\| '_ ` _ /| | |/ _` |/ _ %\\ \n");
    printf("| (_| (_) | | | | | | | | (_| | (_) | \n");
    printf(" %\\___%\\___/|_| |_| |_|_|_|%\\__,_|%\\___/ \n");

		printf("    \n");
		printf("    =============================================\n");
		printf("    \n");

		printf("    1 - INICIAR NOVO JOGO COM 2 JOGADORES\n");
		printf("    2 - INICIAR NOVO JOGO, C/ JOGADOR AUTOMATICO\n");
		printf("    3 - RECOMECAR UM JOGO INTERROMPIDO\n");
		printf("    0 - SAIR\n\n");
		printf("    =============================================\n");
		printf("OPCAO: ");
		fflush(stdin); //limpa o buffer do teclado, in livro de luis damas
		scanf("%d", &op);
	} while (op < 0 && op > 3);

    fflush(stdin);
	return op;
}

int main(int argc, char* argv[])
{
	/*
	Usei um array em vez de outra estrutura (struct ou listas), pois em cada elemento do tabuleiro apenas temos 2 valores possiveis (que no fundo sao 3):
	1: a celula tem elemento comestivel
	0: a celula foi comida
	a ultima celula tem o chamado veneno, com o valor -1
	*/

	int **tabuleiro;
	int nlin=0, ncol=0; //num linhas e colunas do tabuleiro
	int posactl=0, posactc=0; //linha e coluca da posição atual no tabuleiro
	pjogada lista = NULL;
	int op;
	int jact;//jogador atual
	int jog_atab[2]; //array que guarda se cada um dos dois jogadores ja pediu o aumento do tabuleiro. so pode pedir uma vez
	int automatico; // se o jogador 2 é automatico ou nao
	int terminou;
	int ret; // variavel de retorno do set_jogada
	char c; //carater de continuação para outro jogador ou sair do jogo
	char nomefich[50]; //nome do ficheiro para gravar ou ler as jogadas >ponteiro

	do
	{
		automatico = 1;
		terminou = 0;
		jact = 1;
		jog_atab[0] = 0; //define se o jogador 1 ou 2 ja pediu aumento no tabuleiro =0 nao se =1 sim
		jog_atab[1] = 0;
		op = menu();

		switch (op)
		{
			case 1: {
				automatico = 0;
			} //vai para o 2, pois não tem break. o 2 é <> 1 apenas no jogador automatico
			case 2: {
				inicio(&nlin, &ncol); // qual o n de linhas e colunas, altero o valor por referencia

				/*
				nlin = 4;
				ncol = 6;
				*/

				tabuleiro = (int **)malloc(nlin*sizeof(int *)); //alocar espaço para as linhas
				inicia_tabuleiro(tabuleiro, nlin, ncol);// ir para tabuleiro.cpp
				desenha_tabuleiro(tabuleiro, nlin, ncol, jact, posactl, posactc);
			} break;
			case 3: {
                system("cls");
                printf("\n   ============ lista de jogos guardados ===============\n\n");
                jogos_guardados();
                printf("\n   ============ INICIO DO JOGO DO COMILAO ===============\n\n");
				printf("QUAL O NOME DO FICHEIRO PARA CARREGAR AS JOGADAS: ");
				scanf ("%s", nomefich);
				if (strcmp(nomefich, "0"))
                {
                    if (lista = lista_ler(nomefich, &automatico, &nlin, &ncol))
                        printf("JOGADAS CARREGADAS COM SUCESSO DO FICHEIRO %s\n", nomefich);

                    tabuleiro = (int **)malloc(nlin*sizeof(int *));
                    inicia_tabuleiro(tabuleiro, nlin, ncol);
                    mostrar_jogadas(lista, tabuleiro, nlin, ncol);
                    fflush(stdin); //limpar o buffer
                }
            } break;

            case 0: return 0;

		}

		do
		{
			printf("\n================ menu de jogo ====================\n\n");
			printf("JOGADOR %d\n", jact);

			if (posactl && posactc) //Estamos no inicio do jogo pelo que nao faz sentido as op~~oes de interromper e aumentar o tabuleiro
			{
				printf("1 - Interromper o jogo\n");
				if (!jog_atab[jact-1] && lista_tamanho(lista) >= 2) //so pode uamnetar o tabuleiro se ainda nao o fez. so se pode fazer apos os 2 jogadores terem jogado, ou seja, o numero de jogadas ser pelo menos 2. jact-1 pois em termos de jact temos o 1 e o 2 mas o array de vazes em que aumentamos o tabuleiro é 0 e 1
					printf("2 - Aumentar o tabuleiro\n");
			}


			printf("0 - Sair\n");
			printf("Qualquer outra tecla - Jogar\n");
			c = getchar();

			if (posactl && posactc) //Estamos no inicio do jogo pelo que nao faz sentido as op~~oes de interromper e aumentar o tabuleiro
			{
				if (c == '1')
				{
					printf("Qual o nome do ficheiro para guardar as jogadas ?: ");
                    scanf ("%s", nomefich);
                    if (strcmp(nomefich, "0"))
                    {
                        if (lista_gravar(nomefich, lista, automatico, nlin, ncol))
                            printf("Jogadas gravadas com sucesso no ficheiro %s\n", nomefich);
                    }
                    getchar();
				}
				if (c == '2')
				{
					jog_atab[jact-1] = 1; //se tive-se mais que uma possibilidade de aumentar o tabuleiro entao era ++
					aumenta_tabuleiro(tabuleiro, &nlin, &ncol);
					desenha_tabuleiro(tabuleiro, nlin, ncol, jact, posactl, posactc);
				}
			}

			if (c != '0' && c != '1') //"verificar"
			{
				if (automatico && jact == 2)
					ret = set_jogada(tabuleiro, nlin, ncol, 1, jact, &posactl, &posactc);
				else
					ret = set_jogada(tabuleiro, nlin, ncol, 0, jact, &posactl, &posactc);

				if (ret)
				{
					lista = lista_inserir(lista, jact, posactl, posactc);
					if (posactl == nlin && posactc == ncol)
						terminou = 1;

				}

				desenha_tabuleiro(tabuleiro, nlin, ncol, jact, posactl, posactc);

				if (ret) //se fez -1 mantem o mesmo jogador
				{
					jact++;
					if (jact > 2)
						jact = 1;
				}
			}
		}
		while (!terminou && c != '0' && c != '1');

		if (terminou)
		{
			//de referir que o jact já foi atualizado para "o outro jogador", pelo que esse outro jogador é o que não perdeu (o que venceu)
			printf("------------------- O VENCEDOR FOI O JOGADOR %d -------------------\n", jact);
			printf("----------------------------- PARABENS ----------------------------\n");
			fflush(stdin);
			getchar();
		}

	} while (1); //nao é preciso nenhum controle pois no op = menu se é 0 ja faz o return e sai do jogo

	lista_libertar(lista);
	return 0;

}

