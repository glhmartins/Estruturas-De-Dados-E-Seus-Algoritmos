#include <stdio.h>
#include <stdlib.h>
#include "TLSE.c"
#include "TLSEINT.c"

typedef struct ArvB{
  int nchaves, folha, *chave;
  struct ArvB **filho;
}TARVB;

TARVB *TARVB_Inicializa();
TARVB *TARVB_Cria(int t);
TARVB *TARVB_Libera(TARVB *a);
TARVB *TARVB_Busca(TARVB* x, int ch);
TARVB *TARVB_Insere(TARVB *T, int k, int t);
TARVB* TARVB_Retira(TARVB* arv, int k, int t);
TARVB* maior(TARVB *a);
TARVB* menor(TARVB *a);
TARVB* retira_pares(TARVB* a);

TLSE* mN(TARVB*a, int N);
TLSEINT* misc(TARVB *a, int elem);

int suc (TARVB *a, int elem);
int igual (TARVB* a1, TARVB* a2);
int ni(TARVB *a);
int nf(TARVB *a);

void TARVB_Imprime(TARVB *a);
