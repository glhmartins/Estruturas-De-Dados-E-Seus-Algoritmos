#include "TABB.h"

struct arvbinbusca{
    int info;
    struct arvbinbusca *esq, *dir;
};

TABB *TABB_inicializa(void){
    return NULL;
}

TABB *TABB_cria(int raiz, TABB *esq, TABB *dir){
    TABB *novo = (TABB*) malloc(sizeof(TABB));
    novo -> info = raiz;
    novo -> esq = esq;
    novo -> dir = dir;
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
    if(a){
        imp_aux(a->dir, andar+1);
        for (int j = 0; j<=andar; j++) printf("\t");
        printf("%d\n", a->info);
        imp_aux(a->esq, andar+1);
    } else {
        for (int j = 0; j<=andar; j++) printf("\t");
        printf("N\n");
    }
}

void TABB_imp_ident(TABB *a){
    imp_aux(a,0);
}

void TABB_libera(TABB *a){
    if(a){
        TABB_libera(a->esq);
        TABB_libera(a->dir);
        free(a);
    }
}

TABB *TABB_busca(TABB *a, int elem){
    if(!a || a->info==elem) return a;
    if(a->info<elem) return TABB_busca(a->dir, elem);
    return TABB_busca(a->esq, elem);
}

TABB *TABB_insere(TABB *a, int elem){
    if(!a) return TABB_cria(elem, NULL, NULL);
    if (a->info > elem) a->esq = TABB_insere(a->esq, elem);
    else if (a->info < elem) a->dir = TABB_insere(a->dir, elem);
    return a;
}

TABB *TABB_retira(TABB *a, int info){
    if (!a) return a;
    if (info < a->info) a->esq = TABB_retira(a->esq, info);
    else if (info > a->info) a->dir = TABB_retira(a->dir, info);
    else {
        if ((!a->dir) && (!a->esq)){
            free(a);
            a = NULL;
        } else if ((!a->dir) || (!a->esq)){
            TABB *aux = a;
            if (a->esq) a = a->esq;
            else a = a->dir;
            free(aux);
        } else {
            TABB *aux = a->esq;
            while (aux->dir) aux = aux -> dir;
            a -> info = aux -> info;
            aux -> info = info;
            a -> esq = TABB_retira(a->esq, info);
        }
    }
    return a;
}

TABB *maior(TABB *a){
    if (!a->dir) return a;
    return maior(a->dir);
}

TABB *menor(TABB *a){
    if (!a->esq) return a;
    return menor(a->esq);
}

void conta_menores(TABB *a, int *count, int N){
    if(a){
        if (a->info < N) (*count)++;
        conta_menores(a->esq, count, N);
        conta_menores(a->dir, count, N);
    }
}

void pv(TABB *a, int *vet, int *pos){
    if (!a) return;
    pv(a->esq, vet, pos);
    vet[(*pos)++] = a->info;
    pv(a->dir, vet, pos);
}

int *mN(TABB *a, int N){
    if(!a) return a;
    int pos = 0, menores;
    conta_menores(a, &menores, N);
    int *vet = (int*) malloc(sizeof(int) * menores);
    pv(a, vet, &pos);
    return vet;
}

TABB *retira_impares(TABB *a){
    if(!a) return a;
    a -> esq = retira_impares(a->esq);
    a -> dir = retira_impares(a->dir);
    if (a->info%2) a = TABB_retira(a, a->info);
    return a;
}

TLSE *ancestrais(TABB *a, int elem){
    TLSE *lista = TLSE_inicializa();
    if((!a) || (a->info == elem)) return lista;
    lista = TLSE_insere(lista, a->info);
    if (a->info>elem) lista -> prox = ancestrais(a->esq, elem);
    else lista -> prox = ancestrais(a->dir, elem);
    return lista;
}

void quant_mn(TABB *a, int m, int n, int *count){
    if(!a) return;
    if((a->info>m) && (a->info<n)) (*count)++;
    quant_mn(a->esq, m, n, count);
    quant_mn(a->dir, m, n, count);
}

void preenche_vet(TABB *a, int m, int n, int *vet, int *pos){
    if(!a) return;
    preenche_vet(a->esq, m, n, vet, pos);
    if ((a->info>m) && (a->info<n)) vet[(*pos)++] = a->info;
    preenche_vet(a->dir, m, n, vet, pos);
}

int *vet_mn(TABB *a, int m, int n){
    if(!a) return NULL;
    int count = 0, pos = 0;
    quant_mn(a, m, n, &count);
    int *vet = (int*) malloc(sizeof(int)*count);
    preenche_vet(a, m, n, vet, &pos);
    return vet;
}