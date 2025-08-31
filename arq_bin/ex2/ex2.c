#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[40];
    char cpf[11];
    int conta_corrente;
    int agencia;
    float saldo;
} CLIENTE;

CLIENTE procura_cpf(FILE *f, char *cpf){
    CLIENTE c;
    fseek(f, 0, SEEK_END);
    int t = ftell(f) - sizeof(CLIENTE);
    printf("%d\n", t);
    rewind(f);
    while(ftell(f)<=t){
        fread(&c, sizeof(CLIENTE), 1, f);
        if (strcmp(cpf, c.cpf) == 0) break;
    }   
    return c;
}

int main(){
    FILE *f = fopen("clientes.bin", "rb");
    if(!f) exit(1);
    CLIENTE c = procura_cpf(f, "66666666666");
    printf("%s %s %d %d %.2f\n", c.nome, c.cpf, c.conta_corrente, c.agencia, c.saldo);
    fclose(f);
    return 0;
}