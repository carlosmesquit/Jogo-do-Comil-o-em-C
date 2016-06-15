#include "lista.h"



//verifica se a lista est� vazia
int lista_vazia (pjogada lista)
{
	if (lista == NULL)
		return 1;
	else
		return 0;
}


/*
	insere no fim. Percorre a lista ate ao fim (at� que o elemento->proximo seja null
	ou seja, at� que n�o haja proximo. O proximo desse elemento � o novo elemento
	O apontador da lista fica sempre a ser o primeiro elemento da lista
*/

pjogada lista_inserir(pjogada lista, int j, int linha, int col)
{
	pjogada novo, aux;

	novo = (pjogada) malloc(sizeof(jogada));
	if(novo == NULL)
		return lista;
	novo->jogador = j;
	novo->linha  = linha;
	novo->col = col;
	novo->prox = NULL;

	if (lista_vazia(lista))
		lista = novo;
	else
	{
		aux = lista;
		while(aux->prox != NULL)
			aux = aux->prox;
		aux->prox = novo;
	}
	return lista;
}




 // in: http://stackoverflow.com/questions/30216643/how-to-list-all-the-txt-files-in-the-current-directory

int jogos_guardados(){

  DIR *dp;
  struct dirent *ep;

  dp = opendir ("./");
  if (dp != NULL)

      {
    while ((ep = readdir (dp))!=NULL) {
      int length = strlen(ep->d_name);
      if (strncmp(ep->d_name + length - 4, ".txt", 4) == 0) {
          puts (ep->d_name);
      }
    }

    (void) closedir (dp);
  }

  else
    perror ("NAO E POSSIVEL ACEDER A DIRETORIA");

  return 0;
}



/*
	Para alem de gravar as jogadas, h� que gravar, no in�cio do ficheiro, o tabuleiro.
	para isso basta gravar o n� de linhas e colunas do tabuleiro
	nlin e ncol --> n� de linhas e colunas do tabuleiro.
*/


int lista_gravar(char *nomefich, pjogada lista, int automatico, int nlin, int ncol)
{
	FILE *f;
	pjogada aux;
    strcat(nomefich,".txt");

	if ((f = fopen(nomefich,"w")) == NULL)
	{
		printf("Erro ao criar o ficheiro %s\n", nomefich);
		return 0;
	}

    //inicio do ficheiro de texto a gravar
	fprintf(f, "%d\n", automatico); //grava o tipo de jogo
	fprintf(f, "%d\n", nlin);
	fprintf(f, "%d\n", ncol);

	while(lista != NULL)
	{
		aux = lista;
		fprintf(f, "%d %d %d\n", aux->jogador, aux->linha, aux->col);
		lista = lista->prox;
	}

	fclose(f);
	return 1;
}


/*
nlin e ncol s�o variaveis passados por refer�ncia, ou seja, � que � passado por parametro n�o � o seu valor mas o seu endere�o
permitindo que o conteudo dessas variaveis passe para fora da fun��o
*/

pjogada lista_ler(char *nomefich, int *automatico, int *nlin, int *ncol)
{
	FILE *f;
	pjogada aux, lista = NULL;


    if ((f = fopen(nomefich, "r")) == NULL)
    {
        if ((f = fopen(strcat(nomefich, ".txt"), "r")) == NULL) // aqui le o ficheiro sem exten��o porque lhe indico a extens�o
            return NULL;
    }

	//le o formato do tabuleiro
    fscanf(f, "%d\n", automatico); //grava o tipo de jogo
	fscanf(f, "%d\n", nlin);
	fscanf(f, "%d\n", ncol);

	while (!feof(f))
	{
		aux = (pjogada) malloc(sizeof(jogada));
		fscanf(f, "%d %d %d\n", &aux->jogador, &aux->linha, &aux->col);
        lista = lista_inserir(lista, aux->jogador, aux->linha, aux->col);
	}

	fclose(f);
	return lista;
}


// verifica o tamanho da lista

int lista_tamanho(pjogada lista)
{
	int cont = 0;

	while(lista != NULL)
	{
		lista = lista->prox;
		cont++;
	}

	return cont;
}


void lista_libertar(pjogada lista)
{
	pjogada aux;
	while(lista != NULL)
	{
		aux = lista;
		lista = lista->prox;

		free(aux);


	}
}

