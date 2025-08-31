#include <limits.h>
#include "TARVBM.c"

int digitos(int k){
  int d = 0;
  while(k>0){
    d++;
    k/=10;
  }
  return d;
}

int altura(TARVBM *a, int k){
  int h = 0, i = 0;
  TARVBM *aux = a;
  while(aux){
    while(aux->chave[i]<k && i<aux->nchaves) i++;
    h++;
    aux = aux->filho[i];
    i = 0;
  }
  return h;
}

void preenche_char(char *n, int k, int d){
  char aux;
  int pos = d;
  n[pos--] = '\0';
  while(k>0){
    aux = (k%10) + 48;
    k/=10;
    n[pos--] = aux;
  }
}

char* codif (TARVBM* a, int k){
  TARVBM *aux = TARVBM_busca(a, k);
  if(!aux || !a){
    free(aux);
    int nd = digitos(k);
    char *n = (char*) malloc(sizeof(char)*(nd+1));
    preenche_char(n, k, nd);
    return n;
  }
  int i = 0, alt = altura(a, k), pos = 0;
  char *c = (char*) malloc(sizeof(char)*(alt+1));
  char conv;
  while(!a->folha){
    while(i<a->nchaves && a->chave[i]<=k) i++;
    a = a->filho[i];
    conv = i+48;
    c[pos++] = conv;
    i = 0;
  }
  if(a->nchaves == 1){
    conv = 0+48;
    c[pos++] = conv;
    c[pos] = '\0';
  } else{
    for(i = 0; i<a->nchaves; i++){
      if(a->chave[i] == k){
        conv = i+48;
        c[pos++] = conv;
        c[pos] = '\0';
        break;
      }
    }
  }
  return c;
}

int main(int argc, char *argv[]){
  TARVBM *arvore = TARVBM_inicializa();
  int t;
  do{
    printf("t = ");
    scanf("%d", &t);
  }while((t < 2) || (t > 5));

  int num;
  do{
    scanf("%d", &num);
    if(num <= 0) break;
    arvore = TARVBM_insere(arvore, num, t);
  }while(1);
  TARVBM_imprime(arvore);
  
  if(arvore){
    char repete;
    do{
      scanf("%d", &num);
      char *resp = codif (arvore, num);
      printf("%s\n", resp);
      free(resp);
      printf("Quer continuar? ");
      scanf(" %c", &repete);
    }while((repete != 'N') && (repete != 'n'));
  }
  TARVBM_libera(arvore);
  return 0;
}
