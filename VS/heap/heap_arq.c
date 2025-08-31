#include <stdio.h>
#include <stdlib.h>

int esq (int ind){ 
  return 2 * ind + sizeof(int);
}


int dir (int ind){ 
  return 2 * (ind + sizeof(int));
}


int pai(int ind){
  if(ind) return ((ind/sizeof(int))/2) * sizeof(int);
  return -1;
}


void max_heapfy(char *narq, int tamarq, int ind){
  int e = esq(ind), d = dir(ind), maior = ind, aux, maior_elem;

  FILE *fp = fopen(narq, "rb+");
  if(!fp) exit(1);
  fseek(fp, maior, SEEK_SET);
  fread(&maior_elem, sizeof(int), 1, fp);

  if(e < tamarq){
    fseek(fp, e, SEEK_SET);
    fread(&aux, sizeof(int), 1, fp);
    if(aux > maior_elem){
      maior = e;
      maior_elem = aux;
    }    
  } 

  if(d < tamarq){
    fseek(fp, d, SEEK_SET);
    fread(&aux, sizeof(int), 1, fp);
    if(aux > maior_elem){
      maior = d;
      maior_elem = aux;
    }    
  } 

  if(maior != ind){
    int intermediario;
    fseek(fp, ind, SEEK_SET);
    fread(&intermediario, sizeof(int), 1, fp);
    fseek(fp, maior, SEEK_SET);
    printf("($%d) %d x ($%d) %d\n", ind, intermediario, maior, maior_elem);    
    fwrite(&intermediario, sizeof(int), 1, fp);
    fseek(fp, ind, SEEK_SET);
    fwrite(&maior_elem, sizeof(int), 1, fp);
    fclose(fp);
    if((tamarq - maior) > 4) max_heapfy(narq, tamarq, maior);
  }
  else 
    fclose(fp);
}


void build_maxheap(char *narq){
  int tam;
  FILE *fp = fopen(narq, "rb");
  if(!fp) exit(1);
  fseek(fp, 0L, SEEK_END);
  tam = ftell(fp);
  fclose(fp);
  int i, ultimo_pai = pai(tam - sizeof(int));
  for(i = ultimo_pai; i >= 0; i = i - sizeof(int)){
    printf("$%d:\n", i); 
    max_heapfy(narq, tam, i);
    printf("\n");
  }
}


void heapsort(char *narq){
  build_maxheap(narq);

  int tam;
  FILE *fp = fopen(narq, "rb");
  if(!fp) exit(1);
  fseek(fp, 0L, SEEK_END);
  tam = ftell(fp);
  int i, j = tam, aux;
  fclose(fp);

  printf("Depois de build_maxheap, trocando sempre o ultimo elemento pelo primeiro\n");
  for(i = tam - sizeof(int); i >= 0; i = i - sizeof(int)){
    int ult, prim;
    fp = fopen(narq, "rb+");
    if(!fp) exit(1);
    fseek(fp, i, SEEK_SET);
    fread(&ult, sizeof(int), 1, fp);
    fseek(fp, 0L, SEEK_SET);
    fread(&prim, sizeof(int), 1, fp);

    fseek(fp, 0L, SEEK_SET);
    fwrite(&ult, sizeof(int), 1, fp);
    fseek(fp, i, SEEK_SET);
    fwrite(&prim, sizeof(int), 1, fp);

    fclose(fp);
    j -= sizeof(int);
    max_heapfy(narq, j, 0);
  }
}

int main(void){
  char nome_arq[31];
  printf("Digite o nome do arquivo: ");
  scanf("%s", nome_arq);
  int nvet, i = 0, aux;
  printf("Digite o numero de elementos distintos do arquivo: ");
  scanf("%d", &nvet);
  int vet[nvet];
  while (i < nvet){
    scanf("%d", &aux);
    if(aux >= 0){
      int j;
      for(j = 0; j < i; j++) if (vet[j] == aux) break;
      if (j == i) vet[i++] = aux;
    }
  }

  FILE *fp = fopen(nome_arq, "wb");
  if(!fp) exit(1);
  fwrite(&vet, sizeof(int), nvet, fp);
  fclose(fp);

  heapsort(nome_arq);
  int resp[nvet];
  fp = fopen(nome_arq, "rb");
  if(!fp) exit(1);
  fread(&resp, sizeof(int), nvet, fp);
  fclose(fp);

  printf("\nVerificacao da ordenacao...\n");
  for(i = 0; i < nvet; i++) printf("(%d):\t%d\t%d\n", i + 1, vet[i], resp[i]);

  return 0;
}

