#include "TAB.h"

TAB *TAB_inicializa(void){
  return NULL;
}

TAB *TAB_cria(int raiz, TAB *esq, TAB *dir){
  TAB *novo = (TAB *) malloc(sizeof(TAB));
  novo->info = raiz;
  novo->cor = -1;
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

TAB *copia(TAB *a){
  TAB *copy = TAB_inicializa();
  if(!a) return copy;
  copy = TAB_cria(a->info, copia(a->esq), copia(a->dir));
  return copy;
}

TAB *espelho(TAB *a){
  TAB *esp = TAB_inicializa();
  if(!a) return esp;
  esp = TAB_cria(a->info, copia(a->dir), copia(a->esq));
  return esp;
}

TAB *maior(TAB *a){
  if(!a) return a;
  TAB *esq = maior(a->esq), *dir = maior(a->dir), *resp = a;
  if((esq) && (esq->info>resp->info)) resp = esq;
  if((dir) && (dir->info>resp->info)) resp = dir;
  return resp;
}

TAB *menor(TAB *a){
  if(!a) return a;
  TAB *esq = menor(a->esq), *dir = menor(a->dir), *resp = a;
  if((esq) && (esq->info<resp->info)) resp = esq;
  if((dir) && (dir->info<resp->info)) resp = dir;
  return resp;
}

/*TAB *retira_pares(TAB *a){
  if(!a) return a;
  
}*/

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

void imp_aux_colore(TAB *a, int andar){
  int j;
  if(a){
    imp_aux_colore(a->esq, andar + 1);
    for(j = 0; j <= andar; j++) printf("\t"); //printf("   ");
    printf("%d\n", a->cor);
    imp_aux_colore(a->dir, andar + 1);
  }
  else{
   for(j = 0; j <= andar; j++) printf("\t");
   printf("N\n");
  }
}

void TAB_imp_ident(TAB *a){
  imp_aux(a, 0);
}

void TAB_libera(TAB *a){
  if(a){
    TAB_libera(a->esq);
    TAB_libera(a->dir);
    free(a);
  }
}

void colore(TAB *a){ // 0 = preto, 1 = vermelho
  if(a){
    if(a->cor == -1) a->cor = 0;
    if((a->dir)) a->dir->cor = (a->cor+1)%2;
    if(a->esq) a->esq->cor = (a->cor+1)%2;
    colore(a->esq);
    colore(a->dir);
  }
}

int max(int x, int y){
  if(x >= y) return x;
  return y;
}

int TAB_altura(TAB *a){
  if(!a) return -1;
  return max(TAB_altura(a->esq), TAB_altura(a->dir)) + 1;
}

int ni(TAB *a){
  if((!a) || ((!a->esq) && (!a->dir))) return 0;
  return 1+ ni(a->esq)+ ni(a->dir);
}

int nf(TAB *a){
  if((!a)) return 0;
  if((!a->dir) && (!a->esq)) return 1;
  return nf(a->dir) + nf(a->esq);
}

int igual(TAB *a1, TAB *a2){
  if((!a1) && (!a2)) return 1;
  if((!a1) || (!a2)) return 0;
  if((a1->info != a2->info)) return 0;
  return 1 * igual(a1->esq, a2->esq) * igual(a1->dir, a2->dir);
}

void maiores_n(TAB *a, int n, int *tam){
  if(!a) return;
  if(a->info>n) (*tam)++;
  maiores_n(a->esq, n, tam);
  maiores_n(a->dir, n, tam);
}

void pv(TAB *a, int n, int *vet, int *pos){
  if(!a) return;
  if(a->info>n) vet[(*pos)++] = a->info;
  pv(a->esq, n, vet, pos);
  pv(a->dir, n, vet, pos);
}

int *mN(TAB *a, int n, int *tam){
  (*tam) = 0;
  if(!a) return NULL;
  maiores_n(a, n, tam);
  int pos = 0;
  int *vet = (int*) malloc(sizeof(int)*(*tam));
  pv(a, n, vet ,&pos);
  return vet;
}

int aux_zz(TAB *a){
  if((!a) || (!a->esq && !a->dir)) return 1;
  if((a->esq) && (a->dir)) return 0;
  return 1 * aux_zz(a->esq) * aux_zz(a->dir);
}

int zz(TAB *a){
  if((!a) || (!a->esq && !a->dir)) return 1;
  return 1 * aux_zz(a->esq) * aux_zz(a->dir);
}

int estbin(TAB *a){
  if((!a) || (!a->esq && !a->dir)) return 1;
  if((!a->dir && a->esq) || (a->dir && !a->esq)) return 0;
  return 1 * estbin(a->esq) * estbin(a->dir);
}

void conta(TAB *a, int *count){
  if(!a) return;
  (*count)++;
  conta(a->esq, count);
  conta(a->dir, count);
}

void preenche(TAB *a, int *vet, int *pos){
  if(!a) return;
  vet[(*pos)++] = a->info;
  preenche(a->esq, vet, pos);
  preenche(a->dir, vet, pos);
}

int compara(const void *a, const void *b){
  return ((*(int*)a)>(*(int*)b)) ? a:b;
}

int mi(TAB *a1, TAB *a2){
  if(!a1 && !a2) return 1;
  int c1 = 0, c2 = 0;
  conta(a1, &c1);
  conta(a2, &c2);
  if(c1!=c2) return 0;
  int *v1 = (int*) malloc(sizeof(int)*c1), *v2 = (int*) malloc(sizeof(int)*c2);
  int p1 = 0, p2 = 0, i;
  preenche(a1, v1, &p1);
  preenche(a2, v2, &p2);
  qsort(v1, c1, sizeof(int), compara);
  qsort(v2, c2, sizeof(int), compara);
  for(i = 0; i<c1; i++){
    if(v1[i]!=v2[i]){
      free(v1);
      free(v2);
      return 0;
    }
  }
  free(v1);
  free(v2);
  return 1;
}