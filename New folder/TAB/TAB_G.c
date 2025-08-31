#include "TAB.H"

TAB *TAB_inicializa(){
    return NULL;
}

TAB *TAB_cria(int raiz, TAB *esq, TAB *dir){
    TAB *novo = (TAB*) malloc(sizeof(TAB));
    novo -> info = raiz;
    novo -> esq = esq;
    novo -> dir = dir;
    novo -> cor = NULL;
    return novo;
}

TAB *TAB_busca(TAB *a, int elem){
    if ((!a) || (a->info == elem)) return a;
    TAB *resp = TAB_busca(a->esq, elem);
    if (resp) return resp;
    return TAB_busca(a->dir, elem);
}

void TAB_imp_pre(TAB *a){
    if (a){
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

void ident_aux(TAB *a, int andar){
    if(a){
        ident_aux(a->esq, andar+1);
        for (int j = 0; j<=andar; j++) printf("\t");
        printf("%d\n", a->info);
        ident_aux(a->dir, andar+1);
    } else {
        for (int j = 0; j<=andar; j++) printf("\t");
        printf("N\n");
    }
}

void TAB_imp_ident(TAB *a){
    ident_aux(a, 0);
}

void TAB_libera(TAB *a){
    if(!a) return a;
    TAB_libera(a->esq);
    TAB_libera(a->dir);
    free(a);
}

int max(int a, int b){
    return (a>=b) ? a:b;
}

int min(int a, int b){
    return (a<=b) ? a:b;
}

int TAB_altura(TAB *a){
    if(!a) return -1;
    return max(TAB_altura(a->esq), TAB_altura(a->dir)) + 1;
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
    esp = TAB_cria(a->info, espelho(a->dir), espelho(a->esq));
    return esp;
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

int ni(TAB *a){
    if ((!a) || (!a->esq && !a->dir)) return 0;
    return 1 + ni(a->esq) + ni(a->dir);
}

int nf(TAB *a){
    if (!a) return 0;
    if ((!a->esq) && (!a->dir)) return 1;
    return nf(a->esq) + nf(a->dir);
}

int igual(TAB *a1, TAB *a2){
    if (!a1 && !a2) return 1;
    if (((a1) || (a2)) && (a1->info!=a2->info)) return 0;
    return igual(a1->esq, a2->esq) * igual(a1->dir, a2->dir);
}

void colore_aux(TAB *a, int andar){
    if(a){
        colore_aux(a->esq, andar+1);
        for (int j = 0; j<=andar; j++) printf("\t");
        printf("%d\n", a->cor);
        colore_aux(a->dir, andar+1);
    } else {
        for (int j = 0; j<=andar; j++) printf("\t");
        printf("N\n");
    }
}

void TAB_imp_colore(TAB *a){
    colore_aux(a, 0);
}

void colore(TAB *arv){
    if(!arv) return;
    if (arv->cor == NULL){
        arv -> cor = 0;
        if (arv->esq) arv->esq->cor = 1;
        if (arv->dir) arv->dir->cor = 1;
    }
    colore(arv->esq);
    colore(arv->dir);
}

TAB *ret_folha_pre(TAB *a, int *x){
    if (!a) return a;
    if ((!a->esq) && (!a->dir)){
        *x = a->info;
        free(a);
        return NULL;
    } 
    if (a->esq) a->esq = ret_folha_pre(a->esq, x);
    else a->dir = ret_folha_pre(a->dir, x);
    return a;
}

TAB *retira_pares(TAB *a){
    if (!a) return a;
    if (!a->esq && !a->dir){
        if (a->info%2) return a;
        free(a);
        return NULL;
    } if ((a->info%2) == 0){
        int x;
        a = ret_folha_pre(a, &x);
        a -> info = x;
        a = retira_pares(a);
    } else {
        a = retira_pares(a->esq);
        a = retira_pares(a->dir);
    }
    return a;
}

int testa_zz(TAB *a){
    if ((!a) || ((!a->dir) && (!a->esq))) return 1;
    if ((a->dir) && (a->esq)) return 0;
    return testa_zz(a->esq) * testa_zz(a->dir);
}

int zz(TAB *a){
    if(!a) return 0;
    return testa_zz(a->esq) * testa_zz(a->dir);
}

int nelem(TAB *a){
    if (!a) return 0;
    return 1 + nelem(a->esq) + nelem(a->dir);
}

void pv(TAB *a, int *vet, int *pos){
    if (!a) return;
    pv(a->esq, vet, pos);
    vet[(*pos)++] = a->info;
    pv(a->dir, vet, pos);
}

int compara(int a, int b){
    return (a<b) ? a:b;
}

int mi(TAB *a1, TAB *a2){ // 0 se não possuem e 1 se possuem
    if(!a1 && !a2) return 0;
    int t1 = nelem(a1), t2 = nelem(a2), p1 = 0, p2 = 0, iguais = 1;
    if(t1!=t2) return 0;
    int *v1 = (int) malloc(sizeof(int)*t1), *v2 = (int) malloc(sizeof(int)*t2);
    pv(a1, v1, &p1);
    pv(a2, v2, &p2);
    qsort(v1, t1, sizeof(int), compara);
    qsort(v2, t2, sizeof(int), compara);
    for (int i = 0; i<t1; i++){
        if (v1[i] != v2[i]) {
            iguais = 0;
            break;
        }
    }
    free(v1);
    free(v2);
    return iguais;
}

int estbin(TAB *a){
    if(!a) return 1;
    if(((!a->dir) && (!a->esq)) || ((a->dir) && (a->esq))) return 1;
    if ((!a->dir) || (!a->esq)) return 0;
    return estbin(a->esq) * estbin(a->dir);
}
