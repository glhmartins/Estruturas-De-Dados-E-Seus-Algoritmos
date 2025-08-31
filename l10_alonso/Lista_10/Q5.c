/* função em C que, dada uma árvore qualquer, retire todos os elementos pares da
árvore original. A função deve ter o seguinte protótipo: */
#include "TARVB.c"

TARVB* retira_pares(TARVB* arv){
	if(!arv) return arv;
	int i;
	for(i=0; i<arv->nchaves; i++){
		if(!arv->folha) arv->filho[i] = retira_pares(arv->filho[i]);
		if(arv->chave[i]%2==0) arv = TARVB_Retira(arv, arv->chave[i], ((sizeof(arv->filho))/(sizeof(TARVB*)*2)));
	}
	if(!arv->folha) arv->filho[i] = retira_pares(arv->filho[i]);
	return arv;
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
  
  arvore = retira_pares(arvore);
  TARVB_Imprime(arvore);
  TARVB_Libera(arvore);
}