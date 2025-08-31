#include <stdlib.h>
#include <stdio.h>
#include "TLSE.c"

typedef struct viz {
	int id_viz;
	struct viz *prox_viz;
}TVIZ;

typedef struct grafo{
	int id_no, cor;
	TVIZ *prim_viz;
	struct grafo *prox_no;
}TG;


TG* TG_inicializa();
TG* TG_ins_no(TG *g, int x);
TG* TG_busca_no(TG* g, int x);
TG* TG_retira_no(TG *g, int no);

TVIZ* TG_busca_aresta(TG *g, int no1, int no2);

TLSE *caminho (TG *g, int x, int y);

void TG_imprime(TG *g);
void TG_libera(TG *g);
void TG_ins_aresta(TG *g, int no1, int no2);
void TG_retira_aresta(TG *g ,int no1, int no2);

int nn(TG *g);
int na(TG *g);
int testek(TG *g, int k);
int ig(TG *g1, TG *g2);
int nao_tem_mesma_cor(TG *g);
int teste (TG *g);
