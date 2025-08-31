#include <stdio.h>
#include <stdlib.h>
#include "TLSE.c"

typedef struct arvbinbusca TABB;

TABB *TABB_inicializa(void);
TABB *TABB_cria(int raiz, TABB *esq, TABB *dir);

void TABB_imp_pre(TABB *a);
void TABB_imp_pos(TABB *a);
void TABB_imp_sim(TABB *a);
void TABB_imp_ident(TABB *a);

void TABB_libera(TABB *a);

TABB *TABB_busca(TABB *a, int elem);

TABB *TABB_insere(TABB *a, int elem);
TABB *TABB_retira(TABB *a, int info);
TABB *maior(TABB *a);
TABB *menor(TABB *a);
TABB *retira_impares(TABB *a);

TLSE *ancestrais(TABB *a, int elem);

int *mN(TABB *a, int N);
int *vet_mn(TABB *a, int m, int n);