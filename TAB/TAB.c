#include "TAB.h"

TAB *TAB_inicializa(void){
  return NULL;
}

TAB *TAB_cria(int raiz, TAB *esq, TAB *dir){
  TAB *novo = (TAB *) malloc(sizeof(TAB));
  novo->info = raiz;
  novo->cor = NULL;
  novo->esq = esq;
  novo->dir = dir;
  return novo;
}

TAB *TAB_busca(TAB *a, int elem){
  if((!a) || (a->info == elem)) return a;
  TAB *resp = TAB_busca(a->esq, elem);
  if(resp) return resp;
  return TAB_busca(a->dir, elem);
}

void TAB_imp_pre(TAB *a){
  if(a){
    printf("%d ", a->info);
    TAB_imp_pre(a->esq);
    TAB_imp_pre(a->dir);
  }
}

void TAB_imp_pos(TAB *a){
  if(a){
    TAB_imp_pos(a->esq);
    TAB_imp_pos(a->dir);
    printf("%d ", a->info);
  }
}

void TAB_imp_sim(TAB *a){
  if(a){
    TAB_imp_sim(a->esq);
    printf("%d ", a->info);
    TAB_imp_sim(a->dir);
  }
}

void imp_aux(TAB *a, int andar){
  int j;
  if(a){
    imp_aux(a->esq, andar + 1);
    for(j = 0; j <= andar; j++) printf("\t"); //printf("   ");
    printf("%d\n", a->info);
    imp_aux(a->dir, andar + 1);
  }
  else{
   for(j = 0; j <= andar; j++) printf("\t");
   printf("N\n");
  }
}

void TAB_imp_ident(TAB *a){
  imp_aux(a, 0);
}

void imp_aux_cor(TAB *a, int andar){
  int j;
  if(a){
    imp_aux_cor(a->esq, andar + 1);
    for(j = 0; j <= andar; j++) printf("\t"); //printf("   ");
    printf("%d\n", a->cor);
    imp_aux_cor(a->dir, andar + 1);
  }
  else{
   for(j = 0; j <= andar; j++) printf("\t");
   printf("N\n");
  }
}

void TAB_imp_ident_cor(TAB *a){
  imp_aux_cor(a, 0);
}

void TAB_libera(TAB *a){
  if(a){
    TAB_libera(a->esq);
    TAB_libera(a->dir);
    free(a);
  }
}

int max(int x, int y){
    return (x>=y) ? x:y;
}

int min(int x, int y){
    return (x<=y) ? x:y;
}

int TAB_altura(TAB *a){
    if (!a) return -1;
    return max(TAB_altura(a->esq), TAB_altura(a->dir)) + 1;
}

TAB *maior(TAB *a){
    if (!a) return a;
    TAB *esq = maior(a->esq), *dir = maior(a->dir), *resp = a;
    if ((esq) && (esq->info>resp->info)) resp = esq;
    if ((dir) && (dir->info>resp->info)) resp = dir;
    return resp;
}

TAB *menor(TAB *a){
    if (!a) return a;
    TAB *esq = menor(a->esq), *dir = menor(a->dir), *resp = a;
    if ((esq) && (esq->info<resp->info)) resp = esq;
    if ((dir) && (dir->info<resp->info)) resp = dir;
    return resp;
}

TAB *copia(TAB *a){
  TAB *copy = TAB_inicializa();
  if((!a) || ((!a->esq) && (!a->dir))) return a;
  copy = TAB_cria(a->info, copia(a->esq), copia(a->dir));
  return copy;
}

TAB *espelho(TAB *a){
  TAB *esp = TAB_inicializa();
  if ((!a) || ((!a->esq) && (!a->dir))) return a;
  esp = TAB_cria(a->info, espelho(a->dir), espelho(a->esq));
  return esp;
}

int igual(TAB *a1, TAB *a2){
  if (!a1 && !a2) return 1;
  if ((!a1 || !a2) || (a1->info != a2->info)) return 0;
  return 1 * igual(a1 -> esq, a2 -> esq) * igual(a1 -> dir, a2 -> dir);
}


int ni(TAB *a){
  if ((!a) || ((!a->esq) && (!a->dir))) return 0;
  return 1 + ni(a->dir) + ni(a->esq);
}

int nf(TAB *a){
  if (!a) return 0;
  if ((a) && (!a->esq) && (!a->dir)) return 1;
  return nf(a->dir) + nf(a->esq);
}

void colore(TAB *arv){
  if(!arv) return;
  if (arv->cor == NULL){
    arv->cor = 0;
    if (arv->esq) arv->esq->cor = 1;
    if (arv->dir) arv->dir->cor = 1;
  }
  colore(arv->esq);
  colore(arv->dir);
}

TAB *ret_folha_pre(TAB *a, int *x){
  if(!a) return a;
  if((!a -> esq) && (!a -> dir)){
    *x = a->info;
    free(a);
    return NULL;
  }
  if (a->esq) a->esq = ret_folha_pre(a->esq, x);
  else a->dir = ret_folha_pre(a->dir, x);
  return a;
}



TAB* retira_pares(TAB *a){
  if(!a) return a;
  if((!a->esq) && (!a->dir)){
    if(a->info % 2) return a;
    free(a);
    return NULL;
  } if((a->info % 2 ) == 0){
    int x;
    a = ret_folha_pre(a, &x);
    a->info = x;
    a = retira_pares(a);
  } else{
    a->esq = retira_pares(a->esq);
    a->dir = retira_pares(a->dir);
  }
  return a;
}

int min_dist(TAB *a, int x, int y){
  if(!a) return -1;
  else if(x==y) return 0;
  
}