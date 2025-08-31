#include <stdio.h>
#include <stdlib.h>
#include "TLSE.c"
#include "TLSEINT.c"


typedef struct arvbm{
  int nchaves, folha, *chave;
  struct arvbm **filho, *prox;
}TARVBM;


TARVBM *TARVBM_cria(int t);
TARVBM *TARVBM_inicializa(void);
TARVBM *TARVBM_busca(TARVBM *a, int mat);
TARVBM *TARVBM_insere(TARVBM *T, int mat, int t);
TARVBM* TARVBM_retira(TARVBM* arv, int k, int t);
TARVBM* retira_pares(TARVBM* arv);
TARVBM* maior(TARVBM *a);
TARVBM* menor(TARVBM *a);

TLSE* mN(TARVBM *a, int n);
TLSEINT* misc(TARVBM *a, int elem);

int suc (TARVBM *a, int elem);
int igual (TARVBM* a1, TARVBM* a2);
int ni(TARVBM *a);
int nf(TARVBM *a);

void TARVBM_libera(TARVBM *a);
void TARVBM_imprime(TARVBM *a);
void TARVBM_imprime_chaves(TARVBM *a);

