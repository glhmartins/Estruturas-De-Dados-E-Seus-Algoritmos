#include <stdio.h>
#include <stdlib.h>

typedef struct arvbin{
  int info;
  int cor;
  struct arvbin *esq, *dir;
}TAB;

TAB *TAB_inicializa(void);
TAB *TAB_cria(int raiz, TAB *esq, TAB *dir);

void TAB_imp_pre(TAB *a);
void TAB_imp_pos(TAB *a);
void TAB_imp_sim(TAB *a);
void TAB_imp_ident(TAB *a);

void TAB_libera(TAB *a);
void colore(TAB *a);

TAB *TAB_busca(TAB *a, int elem);
TAB *copia(TAB *a);
TAB *espelho(TAB *a);
TAB *maior(TAB *a);
TAB *menor(TAB *a);

int TAB_altura(TAB *a);
int ni(TAB *a);
int nf(TAB *a);
int igual(TAB *a1, TAB *a2);
int zz(TAB *a);
int mi(TAB *a1, TAB *a2);
int estbin(TAB *a);
