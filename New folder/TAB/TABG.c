#include "TAB.H"

TAB *TAB_inicializa(){
    return NULL;
}

TAB *TAB_cria(int raiz, TAB *esq, TAB *dir){
    TAB *novo = (TAB*) malloc(sizeof(TAB));
    novo -> info = raiz;
    novo -> esq = esq;
    novo -> dir = dir;
    return novo;
}

TAB *TAB_busca(TAB *a, int elem){
    if((!a) || (a->info == elem)) return a;
    TAB *resp = TAB_busca(a->esq, elem);
    if (resp == elem) return resp;
    return TAB_busca(a->dir, elem);
}

void TAB_imp_pre(TAB *a){
    if(!a) return a;
    printf("%d ", a->info);
    TAB_imp_pre(a->esq);
    TAB_imp_pre(a->dir);
}

void TAB_imp_pos(TAB *a){
    if (!a) return a;
    TAB_imp_pos(a->esq);
    TAB_imp_pos(a->dir);
    printf("%d ", a->info);
}

void TAB_imp_sim(TAB *a){
    if (!a) return a;
    TAB_imp_sim(a->esq);
    printf("%d ", a->info);
    TAB_imp_sim(a->dir);
}

void imp_aux(TAB *a, int andar){
    if (a){
        imp_aux(a->esq, andar+1);
        for (int j = 0; j<= andar; j++) printf("\t");
        printf("%d ", a->info);
        imp_aux(a->dir, andar+1);
    } else {
        for (int j = 0; j<=andar; j++) printf("\t");
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
    if ((!a) || ((!a->esq) && (!a->dir))) return a;
    copy = TAB_cria(a->info, copia(a->esq), copia(a->dir));
    return copy;
}

TAB *espelho(TAB *a){
    TAB *esp = TAB_inicializa();
    if ((!a) || ((!a->esq) && (!a->dir))) return a;
    esp = TAB_cria(a->info, espelho(a->dir), espelho(a->esq));
    return esp;
}

TAB *maior(TAB *a){
    if(!a) return a;
    TAB *esq = maior(a->esq), *dir = maior(a->dir), *resp = a;
    if ((esq) && (esq->info>resp->info)) resp = esq;
    if ((dir) && (dir->info>resp->info)) resp = dir;
    return resp;
}

TAB *menor(TAB *a){
    if(!a) return a;
    TAB *esq = maior(a->esq), *dir = maior(a->dir), *resp = a;
    if ((esq) && (esq->info<resp->info)) resp = esq;
    if ((esq) && (esq->info<resp->info)) resp = dir;
    return resp;
}

int ni(TAB *a){
    if ((!a) && ((!a->esq) && (!a->dir))) return 0;
    return 1 + ni(a->esq) + n1(a->dir);
}

int nf(TAB *a){
    if(!a) return 0;
    if ((a) && (!a->esq) && (!a->dir)) return 1;
    return nf(a->esq) + nf(a->dir);
}

int igual(TAB *a1, TAB *a2){
    if ((!a1 && !a2)) return 1;
    if (((a1) || (a2)) && (a1->info!=a2->info)) return 0;
    return 1 * igual(a1->esq, a2->esq) * igual(a1->dir, a2->dir);
}

void colore(TAB *a){
    
}