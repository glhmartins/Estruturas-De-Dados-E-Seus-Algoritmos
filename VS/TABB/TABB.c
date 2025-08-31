#include "TABB.h"

struct arvbinbusca{
  int info;
  struct arvbinbusca *esq, *dir;
};

TABB *TABB_inicializa(void){
  return NULL;
}

TABB *TABB_cria(int raiz, TABB *esq, TABB *dir){
  TABB *novo = (TABB *) malloc(sizeof(TABB));
  novo->info = raiz;
  novo->esq = esq;
  novo->dir = dir;
  return novo;
}

void TABB_imp_pre(TABB *a){
  if(a){
    printf("%d ", a->info);
    TABB_imp_pre(a->esq);
    TABB_imp_pre(a->dir);
  }
}

void TABB_imp_pos(TABB *a){
  if(a){
    TABB_imp_pos(a->esq);
    TABB_imp_pos(a->dir);
    printf("%d ", a->info);
  }
}

void TABB_imp_sim(TABB *a){
  if(a){
    TABB_imp_sim(a->esq);
    printf("%d ", a->info);
    TABB_imp_sim(a->dir);
  }
}

void imp_aux(TABB *a, int andar){
  int j;
  if(a){
    imp_aux(a->dir, andar + 1);
    for(j = 0; j <= andar; j++) printf("\t"); //printf("   ");
    printf("%d\n", a->info);
    imp_aux(a->esq, andar + 1);
  }
  else{
   for(j = 0; j <= andar; j++) printf("\t");
   printf("N\n");
  }
}

void TABB_imp_ident(TABB *a){
  imp_aux(a, 0);
}

void TABB_libera(TABB *a){
  if(a){
    TABB_libera(a->esq);
    TABB_libera(a->dir);
    free(a);
  }
}

TABB *TABB_busca(TABB *a, int elem){
  if((!a) || (a->info == elem)) return a;
  if(a->info > elem) return TABB_busca(a->esq, elem);
  return TABB_busca(a->dir, elem);
}

TABB *TABB_insere(TABB *a, int elem){
  if(!a) return TABB_cria(elem, NULL, NULL);
  if(a->info > elem) a->esq = TABB_insere(a->esq, elem);
  else if (a->info < elem) a->dir = TABB_insere(a->dir, elem);
  return a;
}

TABB *TABB_retira(TABB *a, int info){
  if(!a) return a;
  if(info < a->info) 
    a->esq = TABB_retira(a->esq, info);
  else if(info > a->info) 
    a->dir = TABB_retira(a->dir, info);
  else{ //info encontrada
    if((!a->esq) && (!a->dir)){ //CASO (1)
      free(a);
      a = NULL;
    }
    else if((!a->esq) || (!a->dir)){ //CASO (2)
      TABB *temp = a;
      if(!a->esq) a = a->dir;
      else a = a->esq;
      free(temp); 
    }
    else{ //CASO (3)
      TABB *filho = a->esq;
      while(filho->dir) filho = filho->dir;
      a->info = filho->info;
      filho->info = info;
      a->esq = TABB_retira(a->esq, info);
    }
  }
  return a; 
}

TABB *maior(TABB *a){
  if(!a) return a;
  while(a->dir) a = a->dir;
  return a;
}

TABB *maior_rec(TABB *a){
  if((!a) || (!a->dir)) return a;
  return maior_rec(a->dir);
}

TABB *menor(TABB *a){
  if(!a) return a;
  while(a->esq) a = a->esq;
  return a;
}

TABB *menor_rec(TABB *a){
  if((!a) || (!a->esq)) return a;
  return menor_rec(a->esq);
}

void menores_N(TABB *a, int n, int *count){
  if(!a) return;
  if(a->info<n) (*count)++;
  menores_N(a->esq, n, count);
  menores_N(a->dir, n, count);
}

void preenche_vet(TABB *a, int n, int *vet, int *pos){
  if(!a) return;
  preenche_vet(a->esq, n, vet, pos);
  if (a->info<n){
    vet[(*pos)] = a->info;
    (*pos)++;
  }
  preenche_vet(a->dir, n, vet, pos);
}

int *mN(TABB *a, int n){
  if(!a) return NULL;
  int count = 0, pos = 0;
  menores_N(a, n, &count);
  printf("%d\n", count);
  int *vet = (int*) malloc(sizeof(int)*count);
  preenche_vet(a, n, vet, &pos);
  return vet;
}

TABB *retira_impares(TABB *a){
  if(!a) return a;
  a -> esq = retira_impares(a->esq);
  a -> dir = retira_impares(a->dir);
  if(a->info%2) a = TABB_retira(a, a->info);
  return a;
}

TLSE *aux_ancestrais(TABB *a, int elem, TLSE *l){
  if(!a) return l;
  else if(a->info == elem) {
    l = TLSE_insere(l, a->info);
    return l;
  } else if(a->info<elem){
    l = TLSE_insere(l, a->info);
    aux_ancestrais(a->dir, elem, l);
  } else {
    l = TLSE_insere(l, a->info);
    aux_ancestrais(a->esq, elem, l);
  }
}

TLSE *ancestrais(TABB *a, int elem){
  if(!a) return NULL;
  TABB *verifica = TABB_busca(a, elem);
  if(verifica->info!=elem) return NULL;
  TLSE *l = TLSE_inicializa();
  l = aux_ancestrais(a, elem, l);
  return l;
}