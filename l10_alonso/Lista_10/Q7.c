/* quantidade de nós folha: */
#include "TARVB.c"

int nf(TARVB *a){
	if(!a) return 0;
	int c = 0;
	if(!a->folha){
		int i;
		for(i=0; i<=a->nchaves; i++) c+=nf(a->filho[i]);
	}
	if(a->folha) c++;
	return c;
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
  
  int n = nf(arvore);
  printf("\n\n%d\n\n", n);
  TARVB_Libera(arvore);
}