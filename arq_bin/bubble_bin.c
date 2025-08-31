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

void BubbleBin(FILE *f, int tipo){
    int j,k,r;
    CLIENTE a,b;
    fseek(f,0,SEEK_END);
    r = ftell(f)/sizeof(tipo);
    rewind(f);
    for(j = 0; j<r; j++){
        rewind(f);
        for(k = 0; k<r-1; k++){
            fread(&a, sizeof(tipo), 1, f);
            fread(&b, sizeof(tipo), 1, f);
            if(a.saldo>b.saldo){
                fseek(f, k*sizeof(tipo), SEEK_SET);
                fwrite(&b, sizeof(tipo), 1, f);
                fwrite(&a, sizeof(tipo), 1, f);
            }
            fseek(f, (k+1)*sizeof(tipo), SEEK_SET);
        }
    }
}

int main(){
    FILE *f = fopen("Arquivo.b", "rb+");
    if (!f) exit(1);
    BubbleBin(f, sizeof(int));
    fclose(f);
    return 0;
}