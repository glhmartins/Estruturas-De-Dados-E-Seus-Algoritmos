#include "TABB.c"

int main(void){
  TABB *a = TABB_inicializa(); 
  int n;

  while(1){
    scanf("%d", &n);
    if(n < 0) break;
    a = TABB_insere(a, n);
  }
  TABB_imp_ident(a);

  while(1){
    scanf("%d", &n);
    if(n < 0) break;
    a = TABB_retira(a, n);
    TABB_imp_ident(a);
  }
  printf("\n\n\n");
  TLSE *l = ancestrais(a, 7);
  while(l){
    printf("%d ", l->info);
    l = l->prox;
  }
  TABB_libera(a);
  return 0;
} 
