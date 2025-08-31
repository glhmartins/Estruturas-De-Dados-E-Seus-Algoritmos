/* função que, dadas duas árvores deste tipo, testa se estas árvores são iguais.
A função retorna um se elas são iguais e zero, caso contrário. 
A função deve obedecer ao seguinte protótipo: */
#include "TARVB.c"

int igual(TARVB* a1, TARVB* a2){
	if(!a1 && !a2) return 1;
	if(!a1 || !a2) return 0;
	if(a1->nchaves != a2->nchaves) return 0;
	if(a1->folha != a2->folha) return 0;
	
	int i;
	for(i=0; i<a1->nchaves; i++){
		if(!igual(a1->filho[i], a2->filho[i])) return 0;
		if(a1->chave[i] != a2->chave[i]) return 0;
	}
	if(!igual(a1->filho[i], a2->filho[i])) return 0;
	return 1;
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
  
  TARVB *arvore2 = TARVB_Inicializa();
  printf("Digite o grau minimo. Se o valor digitado for menor que 2, t sera considerado igual a 2...\n");
  scanf("%d", &t);
  if(t < 2) t = 2;
  num = 0;
  while(num != -1){
    printf("Digite um numero para adicionar. 0 para imprimir. -9 para remover e -1 para sair\n");
    scanf("%d", &num);
    if(num == -9){
      scanf("%d", &from);
      arvore2 = TARVB_Retira(arvore2, from, t);
      TARVB_Imprime(arvore2);
    }
    else if(num == -1){
      printf("\n");
      TARVB_Imprime(arvore2);
      break;
    }
    else if(!num){
      printf("\n");
      TARVB_Imprime(arvore2);
    }
    else arvore2 = TARVB_Insere(arvore2, num, t);
    printf("\n\n");
  }
  
  int s = igual(arvore, arvore2);
  printf("\n\n%d\n\n", s);
  TARVB_Libera(arvore);
  TARVB_Libera(arvore2);
}