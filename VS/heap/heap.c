#include <stdio.h>
#include <stdlib.h>

int esq(int ind){
  return (ind * 2 + 1);
}

int dir(int ind){
  return (ind * 2 + 2);
}

int pai(int ind){
  if(ind > 0) return (ind - 1)/2;
  return -1;
}

void max_heapfy(int *vet, int n, int ind){
  int e = esq(ind), d = dir(ind), maior = ind;
  if(e < n && vet[e] > vet[ind]) maior = e;
  if(d < n && vet[d] > vet[maior]) maior = d;
  if(maior != ind){
    int temp = vet[ind];
    vet[ind] = vet[maior];
    vet[maior] = temp;
    max_heapfy(vet, n, maior);
  }
}

void build_max_heap(int *v, int n){
  int i, ultimo_pai = pai(n - 1);
  for(i = ultimo_pai; i >= 0; i--)
    max_heapfy(v, n, i);
}

void heapsort(int *v, int n){
  int i;
  build_max_heap(v, n);
  for(i = n - 1; i >= 1; i--){
    int temp = v[i];
    v[i] = v[0];
    v[0] = temp;
    max_heapfy(v, i, 0);
  }
}

int main(void){
  int *vet, n, i = 0;
  printf("Digite o tamanho do vetor de elementos a serem ordenados... ");
  scanf("%d",&n);
  if(n <= 0) return 0;
  vet = (int *) malloc(sizeof(int) * n);

  for(i = 0; i < n; i++) vet[i] = rand() % n;
 
  printf("Antes de ordenar com heapsort...\n");
  for(i = 0; i < n; i++) printf("%d ", vet[i]);
  printf("\n");

  heapsort(vet, n);

  printf("Depois de ordenar com heapsort...\n");
  for(i = 0; i < n; i++) printf("%d ", vet[i]);
  printf("\n");

  free(vet);
  return 0;
}
