#include "TG.h"
#include <limits.h>

//int mdk(TG *g, int no1, int no2, int k);

int main(void){
  TG *g = TG_inicializa();
  int n;
  do{
    scanf("%d", &n);
    if(n <= 0) break;
    g = TG_ins_no(g, n);
  }while(1);
  
  int m, custo;
  do{
    scanf("%d%d%d", &n, &m, &custo);
    if((n <= 0) || (m <= 0)) break;
    TG_ins_aresta(g, n, m, custo);
  }while(1);
  TG_imprime(g);
  
  int k;
  scanf("%d%d%d", &n, &m, &k);
  int resp = INT_MAX;
  //resp = mdk(g, n, m, k);
  printf("Menor distancia entre %d e %d com %d arestas e igual a %d\n", n, m, k, resp);
  TG_libera(g);
  return 0;
}

