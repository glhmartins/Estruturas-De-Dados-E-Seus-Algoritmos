#include <string.h>
#include "TAB.c"

int min(int x, int y){
  return (x<y) ? x:y;
}

int max(int x, int y){
  return (x>y) ? x:y;
}

int altura(TAB *a){
  if(!a) return -1;
  return max(altura(a->esq), altura(a->dir))+1;
}

int balanceamento(TAB *a){
  int esq = 0, dir = 0;
  return altura(a->esq) - altura(a->dir);
}

int mse(TAB *a, int raiz){ // Maior sub-arvore esquerda
  if(!a) return raiz;
  return max(mse(a->esq, a->info), mse(a->dir, a->info));
}

int msd(TAB *a, int raiz){ // Menor sub-arvore direita
  if(!a) return raiz;
  return min(msd(a->esq, a->info), msd(a->dir, a->info));
}

int abeAVL(TAB* a){
  if(!a) return 1;
  if(a->dir){
    if(a->info > a->dir->info) return 0;
  } if(a->esq){
    if(a->info < a->esq->info) return 0;
  }
  int h = balanceamento(a), esq = mse(a->esq, a->info), dir = msd(a->dir, a->info);
  if(esq>a->info) return 0;
  if(dir<a->info) return 0;
  if(h>2 || h<-2) return 0;
  return 1 * abeAVL(a->esq) * abeAVL(a->dir);
}

int main(void){
  int no, pai;
  printf("Digite a raiz da arvore... ");
  scanf("%d", &no);
  TAB *a = TAB_cria(no, NULL, NULL), *resp;
  char repete;
  do{
    char lado[2];
    printf("Quer continuar inserindo nos na árvore (digite N ou n para parar)? ");
    scanf(" %c", &repete);
    if((repete == 'N') || (repete == 'n')) break;
    printf("Digite o pai (que deve existir), o filho a ser inserido na arvore e a posição E(ESQ) ou D(DIR)... ");
    scanf("%d%d%s", &pai, &no, lado);
    resp = TAB_busca(a, pai);
    if(!resp){
      TAB_libera(a);
      return 0;
    }
    if(strcmp(lado, "E") == 0) resp->esq = TAB_cria(no, NULL, NULL);
    else resp->dir = TAB_cria(no, NULL, NULL);
  }while(1);
  TAB_imp_ident(a);
  printf("\n");
  printf("Arvore a e AVL? %d\n", abeAVL(a)); 
  TAB_libera(a);
  return 0;
}
