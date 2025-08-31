#include <stdio.h>
#include <stdlib.h>
#include "TLSE.c"
#include "TG.c"

/* Retornar o tamanho (menor caminho) entre dois nós da arvore requisitados, alem de estar limitado a um numero maximo de arestas que 
voce pode se mover, se nao existir, retornar -infinito. */

//Estou retornado 0 caso não exista

int auxMenorCaminhoTG (TG* grafo, int x, int y, int n, TLSE** anti);

int menorCaminhoTG (TG *g, int x, int y, int n){
	
	int resposta = 0;
	if(!g) return resposta;
	
	TLSE* anti = TLSE_inicializa();
	resposta = auxMenorCaminhoTG(g, x, y, n, &anti);
	
	TLSE_libera(anti);
	return resposta;
	
}

int auxMenorCaminhoTG (TG* grafo, int x, int y, int n, TLSE** anti){
	
	int contador = 0;
	int aux = 0;
	
	TG* no = TG_busca_no(grafo, x);
	TVIZ* vizinho = no->prim_viz;
	
	while(vizinho){ 
		if(vizinho->id_viz == y) return 1;
		vizinho = vizinho->prox_viz;
	}
	
	vizinho = no->prim_viz;
	*anti = TLSE_insere(*anti, x);
	
	while(vizinho){
		
		if(!(TLSE_busca(*anti, vizinho->id_viz))){
			
			aux = auxMenorCaminhoTG(grafo, vizinho->id_viz, y, n, anti);
			if(aux) aux++;
			
			if(((aux<contador) || (!contador)) && ((aux) && (aux<n))) contador = aux;
		}
		
		vizinho = vizinho->prox_viz;
		
	}
	
	*anti = TLSE_retira(*anti, x);
	return contador;
}

int main(void){
  TG *g = TG_inicializa();
  
  int n;
  do{
    scanf("%d", &n);
    if(n <= 0) break;
    g = TG_ins_no(g, n);
  }while(1);
  
  int m;
  do{
    scanf("%d%d", &n, &m);
    if((n <= 0) || (m <= 0)) break;
    TG_ins_aresta(g, n, m);
  }while(1);
  TG_imprime(g);
  
  int resposta = menorCaminhoTG(g, 10, 50, 6);
  printf("\n\n%d\n\n", resposta);
  TG_libera(g);
  return 0;
}