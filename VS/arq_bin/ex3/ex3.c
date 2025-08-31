#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct cliente{
    char nome[40], cpf[11];
    int conta, agencia;
    float saldo;
} TC;

void bubblebin(char *Arq){
    FILE *fp = fopen(Arq, "rb+");
    if(!fp) exit(1);
    TC atual, prox;
    fseek(fp, 0, SEEK_END);
    int tam = ftell(fp)/sizeof(TC), i, j;
    rewind(fp);
    for(i = 0; i<tam; i++){
        for(j = 0; j<tam-1; j++){
            fseek(fp, sizeof(TC)*j, SEEK_SET);
            fread(&atual, sizeof(TC), 1, fp);
            fread(&prox, sizeof(TC), 1, fp);
            if(atual.saldo>prox.saldo){
                fseek(fp, sizeof(TC)*j, SEEK_SET);
                fwrite(&prox, sizeof(TC), 1, fp);
                fwrite(&atual, sizeof(TC), 1, fp);
            }
        }
    }
    rewind(fp);
    for(i = 0; i<tam; i++){
        fread(&atual, sizeof(TC), 1, fp);
        printf("%s %.2f\n", atual.nome, atual.saldo);
    }
    fclose(fp);
}

int main(){
    bubblebin("clientes.bin");
    return 1;
}