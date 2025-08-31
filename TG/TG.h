#include <stdlib.h>
#include <stdio.h>
#include "TLSE.c"
#include <string.h>

typedef struct viz {
	int id_viz;
	struct viz *prox_viz;
}TVIZ;

typedef struct grafo{
	int id_no;
	TVIZ *prim_viz;
	struct grafo *prox_no;
}TG;


TG* TG_inicializa();
void TG_imprime(TG *g);
void TG_libera(TG *g);
TG* TG_busca_no(TG* g, int x);
TVIZ* TG_busca_aresta(TG *g, int no1, int no2);
TG* TG_ins_no(TG *g, int x);
void TG_ins_aresta(TG *g, int no1, int no2);
void TG_retira_aresta(TG *g ,int no1, int no2);
TG* TG_retira_no(TG *g, int no);
int nn(TG *g);
int na(TG *g);
int testek(TG *g, int k);
//int nao_tem_mesma_cor(TG *g);
int ig(TG *g1, TG *g2);
int grafo_abb(TG *g);
TLSE *caminho(TG *g, int x, int y);
int numero_seguidos(TG *g, char*nome);
//int seguidores(TG *g, char *nome, int imprime);
int segue_mais_velho(TG *g, int imprime);
TG *mais_popular(TG *g);
int menor_caminho(TG *g, int no1, int no2, int tmax);