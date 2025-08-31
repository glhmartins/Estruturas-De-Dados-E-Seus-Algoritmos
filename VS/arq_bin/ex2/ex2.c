#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct cliente{
    char nome[40], cpf[11];
    int conta, agencia;
    float saldo;
} TC;

void consulta(char *Arq, char *cpf){ //2522
    FILE *fp = fopen(Arq, "rb");
    if(!fp) exit(1);
    TC aux;
    int tam, i;
    fseek(fp, 0, SEEK_END);
    tam = ftell(fp)/sizeof(TC);
    rewind(fp);
    for(i = 0; i<tam; i++){
        fread(&aux, sizeof(TC), 1, fp);
        if(!strcmp(aux.cpf,cpf)){
            printf("Nome: %s\nCpf: %s\nConta: %d\nAgencia: %d\nSaldo: %.2f", aux.nome, aux.cpf, aux.conta, aux.agencia, aux.saldo);
            fclose(fp);
            return;
        }
    }
    fclose(fp);
    printf("Usuario nao esta nos registros\n");
}

int main(){
    consulta("clientes.bin", "1234567890");
    return 1;
}