#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct num{
  int num, prox, qtde;
}TNUM;

int TH_hash(int mat, int tam);

void TH_inicializa(char *tabHash, int tam);
void TH_retira(char *tabHash, char *dados, int tam, int num);
void TH_insere(char *tabHash, char *dados, int tam, int num);
void TH_imprime (char *tabHash, char *dados, int tam);
void inter(char* arq1, char* arq2, char* saida);
void dif_sim(char* arq1, char* arq2, char* saida);
void uniao(char* arq1, char* arq2, char* saida);

TNUM* TH_busca(char *tabHash, char *dados, int tam, int num);
