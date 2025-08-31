#include "TH.c"

void misc(char *arq1, char *arq2, char *saida, int k){
  FILE *a = fopen(arq1, "rb"), *b = fopen(arq2, "rb"), *fp = fopen(saida, "w");
  if((!a) || (!b) || (!fp)) exit(1);
  char hash[] = "hash.bin", dados[] = "dados.bin";
  FILE *fd = fopen(dados, "wb");
  if(!fd) exit(1);
  int ta, tb, aux, i, resto, buscar, j;
  TNUM nb;
  TH_inicializa(dados, hash, k);
  fseek(a, 0 ,SEEK_END);
  fseek(b, 0, SEEK_END);
  ta = ftell(a)/sizeof(int);
  tb = ftell(b)/sizeof(int);
  rewind(a);
  rewind(b);
  for(i = 0; i<tb; i++){
    fread(&aux, sizeof(int), 1, b);
    resto = aux%k;
    TH_insere(hash, dados, k, resto, aux);
  }
  fclose(fd);
  fd = fopen(dados, "rb");
  if(!fd) exit(1);
  for(i = 0; i<ta; i++){
    fread(&aux, sizeof(int), 1, a);
    resto = k - (aux%k);
    buscar = TH_busca(hash, dados, k, resto);
    if(buscar!=-1){
        rewind(fd);
        fread(&nb, sizeof(TNUM), 1, fd);
        while(nb.valor != buscar) fread(&nb, sizeof(TNUM), 1, fd);
        while(nb.prox != -1){
          fprintf(fp, "%d %d\n", aux, nb.ch);
          fseek(fd, nb.prox*sizeof(TNUM), SEEK_SET);
          fread(&nb, sizeof(TNUM), 1, fd);
        }
        fprintf(fp, "%d %d\n", aux, nb.ch);
    }
  }
  fclose(a);
  fclose(b);
  fclose(fd);
  fclose(fp);
}

int main(void){
  int num;
  char nome_dados1[31];
  printf("Digite nome do primeiro arquivo... ");
  scanf("%s", nome_dados1);
  FILE *fp = fopen(nome_dados1, "wb");
  if(!fp) exit(1);  
  printf("Digite um numero... NAO digite numeros repetidos... Para interromper insira um numero negativo...\n");
  do{
    scanf("%d", &num);
    if(num < 0) break;
    fwrite(&num, sizeof(int), 1, fp);
  }while(1);
  fclose(fp);
  
  char nome_dados2[31];
  printf("Digite nome do segundo arquivo... ");
  scanf("%s", nome_dados2);
  fp = fopen(nome_dados2, "wb");
  if(!fp) exit(1);
  printf("Digite um numero... NAO digite numeros repetidos... Para interromper insira um numero negativo...\n");
  do{
    scanf("%d", &num);
    if(num < 0) break;
    fwrite(&num, sizeof(int), 1, fp);
  }while(1);
  fclose(fp);

  char nome_saida[31];
  printf("Digite nome do arquivo de saida... ");
  scanf("%s", nome_saida);
  int k;
  printf("Digite k... ");
  scanf("%d", &k);
  misc(nome_dados1, nome_dados2, nome_saida, k);
  
  fp = fopen(nome_saida, "r");
  if(!fp) exit(1);
  int r, x, y;
  do{
    r = fscanf(fp, "%d", &x);
    if(r != 1) break;
    r = fscanf(fp, "%d", &y);
    if(r != 1) break;
    printf("(%d,%d)\n", x, y);
  }while(1);
  fclose(fp);

  return 0;
}
