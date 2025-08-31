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
    int i,j,k,tam;
    CLIENTE a,b, c;
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
        rewind(f);
        for(int i = 0; i<tam;i++){
            fread(&c, sizeof(CLIENTE), 1, f);
            printf("%s\n", c.nome);
        }
        printf("\n");
    }
}

void BubbleBin(FILE *f){
    int j,k,r;
    CLIENTE a,b;
    fseek(f,0,SEEK_END);
    r = ftell(f)/sizeof(CLIENTE);
    rewind(f);
    for(j = 0; j<r; j++){
        rewind(f);
        for(k = 0; k<r-1; k++){
            fread(&a, sizeof(CLIENTE), 1, f);
            fread(&b, sizeof(CLIENTE), 1, f);
            if(a.saldo>b.saldo){
                fseek(f, k*sizeof(CLIENTE), SEEK_SET);
                fwrite(&b, sizeof(CLIENTE), 1, f);
                fwrite(&a, sizeof(CLIENTE), 1, f);
            }
            fseek(f, (k+1)*sizeof(CLIENTE), SEEK_SET);
        }
    }
}

void escreve(FILE *l, FILE *e){
    rewind(e);
    CLIENTE c;
    fseek(l, 0, SEEK_END);
    int x = ftell(l);
    rewind(l);
    for(int i = 0; i<x/sizeof(CLIENTE);i++){
        fread(&c, sizeof(CLIENTE), 1, l);
        fwrite(&c, sizeof(CLIENTE),1, e);
    }
}

int main(){
    FILE *f = fopen("clientes.bin", "rb+"), *s = fopen("indices.bin", "rb+");
    if(!f || !s) exit(1);
    CLIENTE c;
    insertBin(f);
    //BubbleBin(f);
    escreve(f,s);
    rewind(s);
    rewind(f);
    for(int i = 0; i<5; i++){
        fread(&c, sizeof(CLIENTE), 1, s);
        printf("%s %s %d %d %.2f\n", c.nome, c.cpf, c.conta_corrente, c.agencia, c.saldo);
    }
    fclose(f);
    fclose(s);
    return 0;
}