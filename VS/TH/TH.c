#include "TH.h"

int TH_hash(int num, int tam){
  return num % tam;
}

void TH_inicializa(char *tabHash, int tam){
  FILE *fp = fopen(tabHash, "wb");
  if(!fp) exit(1);
  int i, elem = -1;
  for(i = 0; i < tam; i++)fwrite(&elem, sizeof(int), 1, fp);
  fclose(fp);
}

TNUM* TH_aloca(int num){
  TNUM *novo = (TNUM*)malloc(sizeof(TNUM));
  novo->num = num;
  novo->prox = -1;
  novo->qtde = 1;
  return novo;
}

TNUM* TH_busca(char *tabHash, char *dados, int tam, int num){
  FILE *fp = fopen(tabHash, "rb");
  if(!fp)exit(1);
  int pos, h = TH_hash(num, tam);
  fseek(fp, h*sizeof(int), SEEK_SET);
  fread(&pos, sizeof(int), 1, fp);
  fclose(fp);
  if(pos == -1)return NULL;
  fp = fopen(dados,"rb");
  if(!fp) exit(1);
  fseek(fp, pos, SEEK_SET);
  TNUM aux;
  fread(&aux, sizeof(TNUM), 1, fp);
  while(1){
    if((aux.num == num) && (aux.qtde)){
      TNUM *resp = TH_aloca(aux.num);
      resp->prox = aux.prox;
      fclose(fp);
      return resp;
    }
    if(aux.prox == -1){
      fclose(fp);
      return NULL;
    }
    fseek(fp, aux.prox, SEEK_SET);
    fread(&aux, sizeof(TNUM), 1, fp);
  }
}

void TH_retira(char *tabHash, char *dados, int tam, int num){
  FILE *fp = fopen(tabHash,"rb");
  if(!fp) exit(1);
  int pos, h = TH_hash(num, tam);
  fseek(fp, h*sizeof(int), SEEK_SET);
  fread(&pos, sizeof(int), 1, fp);
  fclose(fp);
  if(pos == -1) return;
  fp = fopen(dados,"rb+");
  if(!fp)exit(1);
  TNUM aux;
  while(1){
    fseek(fp, pos, SEEK_SET);
    fread(&aux, sizeof(TNUM), 1, fp);
    if((aux.num == num) && (aux.qtde)){
      aux.qtde--;
      fseek(fp, pos, SEEK_SET);
      fwrite(&aux, sizeof(TNUM), 1, fp);
      fclose(fp);
      return;
    }
    if(aux.prox == -1){
      fclose(fp);
      return;
    }
    pos = aux.prox;
  }
}

void TH_insere(char *tabHash, char *dados, int tam, int num){
  FILE *fph = fopen(tabHash, "rb+");
  if(!fph) exit(1);
  int pos, h = TH_hash(num, tam);
  fseek(fph, h*sizeof(int), SEEK_SET);
  fread(&pos, sizeof(int), 1, fph);
  int ant, prim_pos_livre;
  ant = prim_pos_livre = -1;
  FILE *fp = fopen(dados,"rb+");
  if(!fp){
    fclose(fph);
    exit(1);
  }
  TNUM aux;
  while(pos != -1){
    fseek(fp, pos, SEEK_SET);
    fread(&aux, sizeof(TNUM), 1, fp);
    if(aux.num == num){
      aux.qtde++;
      fseek(fp, pos, SEEK_SET);
      fwrite(&aux, sizeof(TNUM), 1, fp);
      fclose(fp);
      fclose(fph);
      return;
    }
    if((!aux.qtde) && (prim_pos_livre == -1))prim_pos_livre=pos;
    ant = pos;
    pos = aux.prox;
  }
  if(prim_pos_livre == -1){
    aux.num = num;
    aux.prox = -1;
    aux.qtde = 1;
    fseek(fp, 0L, SEEK_END);
    pos = ftell(fp);
    fwrite(&aux, sizeof(TNUM), 1, fp);
    if(ant != -1){
      fseek(fp, ant, SEEK_SET);
      fread(&aux, sizeof(TNUM), 1, fp);
      aux.prox = pos;
      fseek(fp, ant, SEEK_SET);
      fwrite(&aux, sizeof(TNUM), 1, fp);
    }
    else{
      fseek(fph, h*sizeof(int), SEEK_SET);
      fwrite(&pos, sizeof(int), 1, fph);
    }
    fclose(fp);
    fclose(fph);
    return;
  }
  fseek(fp, prim_pos_livre, SEEK_SET);
  fread(&aux, sizeof(TNUM), 1, fp);
  aux.num = num;
  aux.qtde = 1;
  fseek(fp, prim_pos_livre, SEEK_SET);
  fwrite(&aux, sizeof(TNUM), 1, fp);
  fclose(fp);
  fclose(fph);
  return;
}

void TH_imprime (char *tabHash, char *dados, int tam){
  FILE *fp = fopen(tabHash, "rb");
  if(!fp) exit(1);
  int vet[tam];
  fread(&vet, sizeof(int), tam, fp);
  fclose(fp);

  fp = fopen(dados, "rb");
  if(!fp) exit(1);
  int i, pos;
  for(i = 0; i < tam; i++){
    int p = vet[i];
    if(p != -1) printf("%d:\n", i);
    TNUM x;
    while(p != -1){
      fseek(fp, p, SEEK_SET);
      pos = ftell (fp);
      fread(&x, sizeof(TNUM), 1, fp);
      printf("$%d: num: %d\tqtde: %d\tprox_end: $%d\n", pos, x.num, x.qtde, x.prox);
      p = x.prox;
    }
  }
  fclose(fp);
}

void inter(char *arq1, char *arq2, char *saida){
  FILE *a1 = fopen(arq1, "rb"), *a2 = fopen(arq2, "rb"), *fp = fopen(saida, "wb");
  if((!a1) || (!a2) || (!fp)) exit(1);
  char *hash = (char*) malloc(sizeof(char)*8), *dados = (char*) malloc(sizeof(char)*9);
  strcpy(hash, "hash.bin");
  strcpy(dados, "dados.bin");
  FILE *fd = fopen(dados, "wb");
  if(!fd) exit(1);
  int ta1, ta2, tam = 11, tad, i;
  TNUM *aux = NULL, *leitura = NULL;
  fseek(a1, 0, SEEK_END);
  fseek(a2, 0, SEEK_END);
  ta1 = ftell(a1)/sizeof(int);
  ta2 = ftell(a2)/sizeof(int);
  rewind(a1);
  rewind(a2);
  TH_inicializa(hash, tam);
  for(i = 0 ; i<ta1; i++){
    fread(&leitura, sizeof(TNUM), 1, a1);
    aux = TH_busca(hash, dados, tam, leitura->num);
    if(aux->num != leitura->num) TH_insere(hash, dados, tam, leitura->num); // na leitura do arquivo 1 eu só deixo que coloque cada elemento uma vez
  }                                                                           
  for(i = 0; i<ta2; i++){
    fread(&leitura, sizeof(TNUM), 1, a2);
    aux = TH_busca(hash, dados, tam, leitura->num);
    if((aux) && (aux->num == leitura->num) && (aux->qtde<2)) TH_insere(hash, dados, tam, leitura->num); // na leitura do arquivo 2 adiciono os que já existiam
  }
  fclose(fd);                                                                            // mas não deixo que adicionem mais de uma vez para que a qtd fique 2
  fd = fopen(dados, "rb");
  if(!fd) exit(1);
  fseek(fd, 0, SEEK_END);
  tad = ftell(fd)/sizeof(int);
  rewind(fd);
  for(i = 0; i<tad; i++){
    fread(&leitura, sizeof(TNUM), 1, fd);
    if(leitura->qtde == 2) fwrite(&leitura->num, sizeof(int), 1, fp);
  }
  remove(hash);
  remove(dados);
  free(hash);
  free(dados);
  fclose(fd);
  fclose(a1);
  fclose(a2);
  fclose(fp);
}

/*void uniao(char *arq1, char *arq2, char *saida){
  FILE *a1 = fopen(arq1, "rb"), *a2 = fopen(arq2, "rb"), *fp = fopen(saida, "wb");
  if((!a1) || (!a2) || (!fp)) exit(1);
  char hash[] = "hash.bin", dados[] = "dados.bin";
  int ta1, ta2, tam = 11, i, td;
  TH_inicializa(hash, tam);
  fseek(a1, 0 , SEEK_END);
  fseek(a2, 0, SEEK_END);
  TNUM *aux, *leitura;
  ta1 = ftell(a1)/sizeof(int);
  ta2 = ftell(a2)/sizeof(int);
  rewind(a1);
  rewind(a2);
  for(i = 0; i<ta1; i++){
    fread(&leitura, sizeof(TNUM), 1, a1);
    aux = TH_busca(hash, dados, tam, leitura->num);
    if((aux->num != leitura->num)) {
      TH_insere(hash, dados, tam, leitura->num);
      fwrite(leitura->num, sizeof(int), 1, fp);
    }
  }
  for(i = 0; i<ta2; i++){
    fread(&leitura, sizeof(TNUM), 1, a2);
    aux = TH_busca(hash, dados, tam, leitura->num);
    if(aux->num!=leitura->num){
      TH_insere(hash, dados, tam, leitura->num);
      fwrite(leitura->num, sizeof(int), 1, fp);
    }
  }
  remove(hash);
  remove(dados);
  fclose(a1);
  fclose(a2);
  fclose(fp);
}

void dif_sim(char *arq1, char *arq2, char *saida){
  FILE *a1 = fopen(arq1, "rb"), *a2 = fopen(arq2, "rb"), *fp = fopen(saida, "wb");
  if((!a1) || (!a2) || (!fp)) exit(1);
  char u[] = "uniao.bin", i[] = "inter.bin";
  uniao(arq1, arq2, u);
  inter(arq1, arq2, i);
  FILE *uni = fopen(u, "rb"), *intersection = fopen(i, "rb");
  if((!uni) || (!intersection)) exit(1);
  int tu, ti, j, k, lu, li;
  fseek(uni, 0, SEEK_END);
  fseek(intersection, 0, SEEK_END);
  tu = ftell(uni)/sizeof(int);
  ti = ftell(intersection)/sizeof(int);
  rewind(uni);
  rewind(intersection);
  for(j = 0; j<tu; j++){
    rewind(intersection);
    fread(&lu, sizeof(int), 1, uni);
    for(k = 0; k<ti; k++){
      fread(&li, sizeof(int), 1, intersection);
      if(li == lu) break;
    }
    if(li != lu) fwrite(&li, sizeof(int), 1, fp);
  }
  fclose(uni);
  fclose(intersection);
  remove(uni);
  remove(intersection);
  fclose(fp);
}
*/