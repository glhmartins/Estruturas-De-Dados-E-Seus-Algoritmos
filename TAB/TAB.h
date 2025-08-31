#include <stdio.h>
#include <stdlib.h>

typedef struct arvbin{
  int info;
  int cor; // 0 = preto, 1 = vermelho
  struct arvbin *esq, *dir;
}TAB;

TAB *TAB_inicializa(void);
TAB *TAB_cria(int raiz, TAB *esq, TAB *dir);

void TAB_imp_pre(TAB *a);
void TAB_imp_pos(TAB *a);
void TAB_imp_sim(TAB *a);
void TAB_imp_ident(TAB *a);

void colore(TAB *arv);

void TAB_libera(TAB *a);

TAB *TAB_busca(TAB *a, int elem);

TAB *maior(TAB *a);
TAB *menor(TAB *a);
TAB *copia(TAB *a);
TAB *espelho(TAB *a);
TAB* retira_pares (TAB* arv);

int igual (TAB* a1, TAB* a2);

int ni(TAB *a);
int nf(TAB *a);

int TAB_altura(TAB *a);
int iguais(int a, int b);
int min_dist(TAB *a, int x, int y);