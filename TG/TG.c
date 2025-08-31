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
  /*if(g){
    TG_libera(g->prox_no);
    TG_libera_viz(g->prim_viz);
    free(g);
  }*/;
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
  return 1 + nn(g->prox_no);
}

int na(TG *g){
  TG *p = g;
  int count = 0;
  while ((p)){
    TVIZ *aux = p->prim_viz, *ant = NULL;
    while(aux){
      count++;
      ant = aux;
      aux = aux -> prox_viz;
      TG_retira_aresta(p, p->id_no, ant->id_viz);
    }
    p = p->prox_no;
  }
  return count;
}

int conta_aresta(TG *g, int k){
  if (!g) return 1;
  TVIZ *v = g->prim_viz;
  int count = 0;
  while (v){
    count++;
    v = v->prox_viz;
  }
  return (count==k) ? 1:0;
}

int testek(TG *g, int k){ // -1 se não tem grafo, 1 se passou no teste e 0 se não passou no teste
  if (!g) return -1;
  TG *p = g;
  int resp = 1;
  while(p){
    resp *= conta_aresta(p, k);
    p = p -> prox_no;
  }
  return resp;
}

/*int nao_tem_mesma_cor(TG *g){
  if (!g) return 1;
  TVIZ *aux = g->prim_viz;
  int cor_ant = aux->cor;
  while (aux->prox_viz){
    if (cor_ant == aux->prox_viz->cor) return 0;
    aux = aux->prox_viz;
    cor_ant = aux->cor;
  }
  return 1;
}*/

int qnos(TG *g){
  if(!g) return 0;
  return 1 + qnos(g->prox_no);
}

int arestas_iguais(TG *g1, TG *g2){
  if(g1 && g2){
    TVIZ *v1 = g1 -> prim_viz, *v2 = g2 -> prim_viz;
    if (!v1 || !v2) return 0;
    while (v1 && v2){
      if (v1->id_viz != v2->id_viz) return 0;
      v1 = v1->prox_viz;
      v2 = v2->prox_viz;
    }
    return 1;
  }
}

int ig(TG *g1, TG *g2){
  if (!g1 && !g2) return -1;
  if (qnos(g1) != qnos(g2)) return 0;
  TG *p = g1, *q = g2;
  while (p && q){
    if ((arestas_iguais(p,q)) == 0) return 0;
    p = p->prox_no;
    q = q->prox_no;
  }
  return 1;
}

/*int numero_seguidos(TG *g, char *nome){
  if(!g) return 0;
  TG *p = TG_busca_no(g, nome);
  if (!p) return 0;
  int count = 0;
  TVIZ *resp = p->prim_viz;
  while (resp){
    count++;
    resp = resp->prox_viz;
  }
  return count;
}*/

/*int seguidores(TG *g, char *nome, int imprime){
  if(!g) return 0;
  if (!(TG_busca_no(g, nome))) return 0;
  TG *p = g;
  int count = 0;
  while(p){
    TVIZ *aux = p->prim_viz;
    while (aux){
      if(aux->nome == nome){
        if (imprime) printf("%s\n", p->nome);
        count++;
        break;
      }
      aux = aux->prox_viz;
    }
    p = p->prox_no;
  }
  return count;
}*/

int verifica_idade(TVIZ *v, int idade){
  if(!v) return 0;
  while(v){
    if(idade>v->id_viz) return 0;
    v = v->prox_viz;
  }
  return 1;
}

/*int segue_mais_velhos(TG *g, int imprime){
  if(!g) return 0;
  TG *p = g;
  int count = 0, verifica;
  while(p){
    verifica = verifica_idade(p->prim_viz, p->id_no);
    if ((verifica) && (imprime)) printf("%s\n", p->nome);
    count += verifica;
  }
  return count;
}*/

/*TG *compara_seg(TG *g,TG *g1, TG *g2){
  int sg1 = seguidores(g, g1->nome, 0),
      sg2 = seguidores(g, g2->nome, 0);
  return (sg1>sg2) ? g1:g2;
}

TG *mais_popular(TG *g){
  if(!g) return g;
  TG *p = g->prox_no, *mp = g, *atual;
  while(p){
    mp = compara_seg(g, mp, p);
    p = p->prox_no;
  }
  return mp;
}*/

int auxMenorCaminho(TG *g, int x, int y, int n, TLSE *l){
  int count = 0, aux = 0;
  TG *no = TG_busca_no(g, x);
  TVIZ *v = no->prim_viz;
  while(v){
    if(v->id_viz==y) return 1;
    v = v->prox_viz;
  }
  v = no->prim_viz;
  l = TLSE_insere(l, x);
  while(v){
    if(!(TLSE_busca(l, v->id_viz))){
      aux = auxMenorCaminho(g, v->id_viz, y, n, l);
      if (aux) aux++;
      if ((aux<count || !count) && (aux && aux<n)) count = aux;
    }
    v = v->prox_viz;
  }
  l = TLSE_retira(l,x);
  return count;
}

int menor_caminho(TG *g, int no1, int no2, int tmax){
  int resp = 0;
  if (!g) return resp;
  TLSE *l = TLSE_inicializa();
  resp = auxMenorCaminho(g, no1, no2, tmax, l);
  TLSE_lib_rec(l);
  return resp;
}

int verificaCaminho(TLSE *l, int y){
  TLSE *aux = l;
  while(aux){
    if(aux->info==y) return 1;
    aux = aux->prox;
  }
  return 0;
}

TLSE *auxCaminho(TG *g, int x, int y, TLSE *l){
  TG *no = TG_busca_no(g, x);
  if(!no) return l;
  TVIZ *v = no->prim_viz;
  l = TLSE_insere(l, x);
  while(v){
    if(v->id_viz==y) return TLSE_insere(l, v->id_viz);
    v = v->prox_viz;
  }
  v = no->prim_viz;
  while(v){
    if(!(TLSE_busca(l, v->id_viz))){
      l = auxCaminho(g, v->id_viz, y, l);
      if(verificaCaminho(l,y)) return l;
    }
    v = v->prox_viz;
  }
  return l;
}

TLSE *caminho(TG *g, int x, int y){
  TLSE *l = TLSE_inicializa();
  if(!g) return l;
  l = auxCaminho(g, x, y, l);
  return l;
}