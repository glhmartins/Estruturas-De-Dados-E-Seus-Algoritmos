#include "TG.h"

TG* TG_inicializa(){
  return NULL;
}


void TG_imprime(TG *g){
  while(g){
    printf("Vizinhos do No %d:\n", g->id_no);
    TVIZ *v = g->prim_viz;
    while(v){
      printf("%d ", v->id_viz);
      v = v->prox_viz;
    }
    printf("\n");
    g = g->prox_no;
  }
}

void TG_imp_rec(TG *g){
  if(g){
    printf("%d:\n", g->id_no);
    TVIZ *v = g->prim_viz;
    while(v){
      printf("%d ", v->id_viz);
      v = v->prox_viz;
    }
    TG_imp_rec(g->prox_no);
  }
}

void TG_libera_viz(TVIZ *v){
  while(v){
    TVIZ *temp = v;
    v = v->prox_viz;
    free(temp);
  }
}

void TG_libera_viz_rec(TVIZ *v){
  if(!v) return;
  TG_libera_viz_rec(v->prox_viz);
  free(v);
}

void TG_libera(TG *g){
  while(g){
    TG_libera_viz(g->prim_viz);
    TG *temp = g;
    g = g->prox_no;
    free(temp);
  }
}

void TG_libera_rec(TG *g){
  if(g){
    TG_libera_viz(g->prim_viz);
    TG_libera_rec(g->prox_no);
    free(g);
  }
}

TG* TG_busca_no(TG* g, int x){
  if((!g) || (g->id_no == x)) return g;
  return(TG_busca_no(g->prox_no, x));
}

TVIZ* TG_busca_aresta(TG *g, int no1, int no2){
  TG *p1 = TG_busca_no(g,no1), *p2 = TG_busca_no(g,no2);
  if((!p1) || (!p2)) return NULL;
  TVIZ *resp = p1->prim_viz;
  while((resp) && (resp->id_viz != no2)) resp = resp->prox_viz;
  return resp;
}

TG* TG_ins_no(TG *g, int x){
  TG *p = TG_busca_no(g, x);
  if(!p){
    p = (TG*) malloc(sizeof(TG));
    p->id_no = x;
    p->prox_no = g;
    p->cor = rand() % 10;
    p->prim_viz = NULL;
    g = p;
  }
  return g;
}

void TG_ins_um_sentido(TG *g, int no1, int no2){
  TG *p = TG_busca_no(g, no1), *q = TG_busca_no(g, no2);
  if((!p) || (!q)) return;
  TVIZ *aresta = TG_busca_aresta(g, no1, no2);
  if(aresta) return;
  aresta = (TVIZ *) malloc(sizeof(TVIZ));
  aresta->id_viz = no2;
  aresta->prox_viz = p->prim_viz;
  p->prim_viz = aresta;
}

void TG_ins_aresta(TG *g, int no1, int no2){
  TG_ins_um_sentido(g, no1, no2);
  TG_ins_um_sentido(g, no2, no1);
}

 void TG_retira_um_sentido(TG *g, int no1, int no2){
  TG *p = TG_busca_no(g, no1);
  if(!p) return;
  TVIZ *ant = NULL, *atual = p->prim_viz;
  while((atual) && (atual->id_viz != no2)){
    ant = atual;
    atual = atual->prox_viz;
  }
  if(!atual) return;
  if(!ant) p->prim_viz = atual->prox_viz;
  else ant->prox_viz = atual->prox_viz;
  free(atual);
}

void TG_retira_aresta(TG *g, int no1, int no2){
  TG_retira_um_sentido(g, no1, no2);
  TG_retira_um_sentido(g, no2, no1);
}

TG* TG_retira_no(TG *g, int no){
  TG *p = g, *ant = NULL;
  while((p)&& (p->id_no != no)){
    ant = p;
    p = p->prox_no;
  }
  if(!p) return g;
  TVIZ *v = p->prim_viz, *t;
  while(v){
    TG_retira_um_sentido(g, v->id_viz, no);
    t = v;
    v = v->prox_viz;
    free(t);
  }
  if(!ant) g = g->prox_no;
  else ant->prox_no = p->prox_no;
  free(p);
  return g;
}

int nn(TG *g){
  if(!g) return 0;
  TG *aux = g;
  int count = 0;
  while(aux){
    count++;
    aux = aux->prox_no;
  }
  return count;
}

int na(TG *g){
  if(!g) return 0;
  TG *aux = g;
  int arestas = 0;
  while(aux){
    TVIZ *av = aux->prim_viz;
    while (av){
      arestas++;
      av = av->prox_viz;
    }
    aux = aux->prox_no;
  }
  return arestas/2; // dividimos por 2 pois contamos cada aresta duas vezes
}

int testek(TG *g, int k){ // 1 se todos os nós tiverem k arestas, 0 caso ao menos uma não tenha
  if(!g) return 1;
  TG *aux = g;
  int count = 0;
  while(aux){
    TVIZ *av = aux->prim_viz;
    while(av){
      count++;
      av = av->prox_viz;
    }
    if(count!=k) return 0;
    count = 0;
    aux = aux->prox_no;
  }
  return 1;
}

int verifica_nos(TG *g1, TG *g2){
  TG *a1 = g1, *aux;
  while(a1){
    aux = TG_busca_no(g2, a1->id_no);
    if(aux->id_no!=a1->id_no) return 0;
    a1 = a1->prox_no;
  }
  return 1;
}

int verifica_arestas(TG *g1, TG *g2){
  TG *a1 = g2;
  TVIZ *aux;
  while(a1){
    TVIZ *av = a1->prim_viz;
    while(av){
      aux = TG_busca_aresta(g2, a1->id_no, av->id_viz);
      if(aux->id_viz != av->id_viz) return 0;
      av = av->prox_viz;
    }
    a1 = a1->prox_no;
  }
  return 1;
}

int ig(TG *g1, TG *g2){
  if((!g1) && (!g2)) return 1;
  if((!g1) || (!g2)) return 0;
  if(!verifica_nos(g1,g2)) return 0;
  if(!verifica_arestas(g1,g2)) return 0;
  return 1;
}

int nao_tem_mesma_cor(TG *g){
  if(!g) return 1;
  TG *aux = g, *aux2;
  while(aux){
    TVIZ *av = aux->prim_viz;
    while(av){
      aux2 = TG_busca_no(g, av->id_viz);
      printf("%d %d\n", aux->cor, aux2->cor);
      if(aux->cor == aux2->cor) return 0;
      av = av->prox_viz;
    }
    aux = aux->prox_no;
  }
  return 1;
}

/*
int numero_seguidos(TG *g, char *nome){
  if(!g) return -1;
  int segue = 0;
  TG *aux = g;
  while(strcmp(aux->nome,nome)) aux = aux->prox_no;
  TVIZ *v = aux->prim_viz;
  while(v){
    segue++;
    v = v->prox_viz;
  }
  return segue;
}

int seguidores(TG *g, char *nome){
  if(!g) return -1;
  int seguidores = 0;
  TG *aux = g;
  while(aux){
    if(!strcmp(aux->nome, nome)) continue; //strcmp retorna 0 quando as strings são iguais
    TVIZ *v = aux->prim_viz;
    while(v){
      if(!strcmp(v->nome, nome)) seguidores++;
      v = v->prox_viz;
    }
    aux = aux->prox_no;
  }
  return seguidores;
}

TG *mais_popular(TG *g){
  if(!g) return g;
  TG *mp = g, *aux = g->prox_no;
  int ms = seguidores(g, mp->nome), saux;
  while(aux){
    saux = seguidores(g, aux->nome);
    if(saux>ms){
      ms = saux;
      mp = aux;
    }
    aux = aux->prox_no;
  }
  return mp;
}

int segue_mais_velho(TG *g){
  if(!g) return -1;
  int count = 0, mv = 1; // MV = Mais velhos, se a pessoa só segue pessoas mais velhas ira ficar 1
  TG *aux = g;
  while(aux){
    TVIZ *v = aux->prim_viz;
    while(v){
      if(v->idade<aux->idade) mv = 0;
      v = v->prox_viz;
    }
    if(mv == 1){
      printf("%s\n", aux->nome);
      count++;
    }
    mv = 1;
    aux = aux->prox_no;
  }
  return count;
}

*/

TLSE *aux_caminho(TG *g, TLSE *l, TLSE *vistos, int x, int y){
  if(!g) return NULL;
}

TLSE *caminho(TG *g, int x, int y){
  TLSE *l = TLSE_inicializa();
  if(!g) return l;
  TG *a = TG_busca_no(g, x), *b = TG_busca_no(g, y);
  if((a->id_no!=x) || (b->id_no!=y)) return l;
  TLSE *vistos = TLSE_inicializa();

  return l;
}
