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

void insertBin(FILE *f){
    int i,j, tam;
    CLIENTE a,b;
    fseek(f, 0, SEEK_END);
    tam = ftell(f)/sizeof(CLIENTE);
    rewind(f);
    for (i = 1; i<tam; i++){
        j = i-1;
        fseek(f, j*sizeof(CLIENTE), SEEK_SET);
        fread(&a, sizeof(CLIENTE), 1, f);
        fread(&b, sizeof(CLIENTE), 1, f);
        fseek(f, i*sizeof(CLIENTE), SEEK_SET);
        while((j>=0) && (a.saldo>b.saldo)){
            fseek(f, (j+1)*sizeof(CLIENTE), SEEK_SET);
            fwrite(&a, sizeof(CLIENTE), 1, f);
            j -= 1;
            if (j>=0){
                fseek(f, j*sizeof(CLIENTE), SEEK_SET);
                fread(&a, sizeof(CLIENTE), 1, f);
            }
        }
        fseek(f, (j+1)*sizeof(CLIENTE), SEEK_SET);
        fwrite(&b, sizeof(CLIENTE), 1, f);
    }
}

int main(){
    FILE *f = fopen("Arquivo.b", "rb+");
    if (!f) exit(1);
    insertBin(f);
    fclose(f);
    return 0;
}