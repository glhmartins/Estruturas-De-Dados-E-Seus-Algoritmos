/* Sucessor de um elemento na árvore. Se o elemento for o maior da estrutura, sua função deve retornar INT_MAX: */
#include "TARVB.c"

int suc (TARVB *a, int e){
	if(!a) return INT_MAX;
	int i=0;
	while((i<a->nchaves) && (e>=a->chave[i])) i++;
	if (a->folha){
		if (i==a->nchaves) return INT_MAX;
		else return a->chave[i];
	} else {
		int s = suc(a->filho[i], e);
		if ((s==INT_MAX) && (a->chave[i]>e)) return a->chave[i];
		else return s;
	}
}

int main(int argc, char *argv[]){
  TARVB *arvore = TARVB_Inicializa();
  int t;
  printf("Digite o grau minimo. Se o valor digitado for menor que 2, t sera considerado igual a 2...\n");
  scanf("%d", &t);
  if(t < 2) t = 2;
  int num = 0, from, to;
  while(num != -1){
    printf("Digite um numero para adicionar. 0 para imprimir. -9 para remover e -1 para sair\n");
    scanf("%d", &num);
    if(num == -9){
      scanf("%d", &from);
      arvore = TARVB_Retira(arvore, from, t);
      TARVB_Imprime(arvore);
    }
    else if(num == -1){
      printf("\n");
      TARVB_Imprime(arvore);
      break;
    }
    else if(!num){
      printf("\n");
      TARVB_Imprime(arvore);
    }
    else arvore = TARVB_Insere(arvore, num, t);
    printf("\n\n");
  }
  
  int s = suc(arvore, 900);
  printf("\n%d\n", s);
  TARVB_Libera(arvore);
}