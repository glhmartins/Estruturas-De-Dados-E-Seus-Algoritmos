#include "arqtext.h"

typedef struct{
    int n;
    char linha[3];
} Numero;

typedef struct registro{
    char nome[100];
    float media;
} REG;

REG lista[100];

void cria_arq_ord(char *narq){
    FILE *fp = fopen(narq, "w");
    if (!fp) exit(1);
    int n, ant;
    scanf("%d", &ant);
    fprintf(fp, "%d\n", ant);
    do {
        scanf("%d\n", &n);
        if (n<=ant) break;
        fprintf(fp, "%d\n", n);
        ant = n;
    } while(1);
    fclose(fp);
}

void merge(char *a1, char *a2, char *s){
    FILE *fp1 = fopen(a1, "r"),
    *fp2 = fopen(a2, "r"),
    *fpo = fopen(s, "w");
    if((!fp1)||(!fp2)||(!fpo)) exit(1);
    int r1, n1, r2, n2;
    r1 = fscanf(fp1, "%d", &n1);
    r2 = fscanf(fp2, "%d", &n2);
    while((r1 == 1) || (r2 == 1)){
        if((r2 != 1) || (n1 <= n2)){
            fprintf(fpo, "%d\n", n1);
            r1 = fscanf(fp1, "%d", &n1);
            if(r1 != 1) n1 = __INT_MAX__;
        }
        else if((r1 != 1) || (n2 < n1)){
            fprintf(fpo, "%d\n", n2);
            r2 = fscanf(fp2, "%d", &n2);
            if(r2 != 1) n2 = __INT_MAX__;
        }
    }
    fclose(fp1);
    fclose(fp2);
    fclose(fpo);
}

void RetRepet(char *ArqEnt, char *ArqSaida){
    FILE *fpe = fopen(ArqEnt, "r"), *fps = fopen(ArqSaida, "w");
    if(!fpe || !fps) exit(1);
    int r;
    char ant[100], atual[100];
    r = fscanf(fpe, "%s", &ant);
    fprintf(fps, "%s ", ant);
    r = fscanf(fpe, "%s", &atual);
    while (r==1){
        if (strcmp(ant, atual)){
            fprintf(fps, "%s ", atual);
            strcpy(ant, atual);
        }
        r = fscanf(fpe, "%s", &atual);
    }
    fclose(fpe);
    fclose(fps);
}

void bubble(REG lista[], int tamanho){
    REG aux;
    for (int i = 0; i<tamanho; i++){
        for (int j = 0; j<tamanho-1; j++){
            if (lista[j].media>(lista[j+1]).media){
                aux = lista[j];
                lista[j] = lista[j+1];
                lista[j+1] = aux;
            }
        }
    }
}

REG inicializa(char nome[], float n1, float n2){
    REG r;
    strcpy(r.nome, nome);
    r.media = (n1+n2)/2.0;
    return r;
}

Numero start(int n, int linha){
    Numero number;
    number.n = n;
    sprintf(number.linha, "%d", linha);
    return number;
}

void media(char *ArqEnt, char *ArqSaida){
    FILE *fpe = fopen(ArqEnt, "r"),*fps = fopen(ArqSaida, "w");
    if (!fpe || !fps) exit(1);
    int r1, r2, pos = 0;
    float n1, n2;
    char nome[100], c;
    fgets(nome, 100, fpe);
    r1 = fscanf(fpe, "%f", &n1);
    r2 = fscanf(fpe, "%f", &n2);
    while ((r1==1) && (r2==1)){
        fscanf(fpe, "%c", &c); // limpar buffer
        REG aux = inicializa(nome, n1, n2);
        lista[pos++] = aux;
        fgets(nome, 100, fpe);
        r1 = fscanf(fpe, "%f", &n1);
        r2 = fscanf(fpe, "%f", &n2);
    }
    bubble(lista, pos);
    for (int i = 0; i<pos; i++) fprintf(fps, "%s %.2f\n", lista[i].nome, lista[i].media);
    fclose(fpe);
    fclose(fps);
}

void bubble2(Numero lista[], int tamanho){
    Numero aux;
    for (int i = 0; i<tamanho; i++){
        for (int j = 0; j<tamanho-1; j++){
            if (lista[j].n>(lista[j+1]).n){
                aux = lista[j];
                lista[j] = lista[j+1];
                lista[j+1] = aux;
            }
        }
    }
}

int conta(Numero lista[], int tamanho, int n){
    int count = 0;
    for (int i = 0; i<tamanho; i++) 
        if(lista[i].n == n) 
            count++;
    return count;
}

void imp(Numero lista[], int tamanho){
    int count = conta(lista,tamanho, lista[0].n), ant = lista[0].n;
    printf("O numero %d apareceu %d vezes, ele apareceu na(s) linha(s): %s ", ant, count ,lista[0].linha);
    for (int i = 1; i<tamanho; i++){
        if(lista[i].n!=ant){
            count = conta(lista, tamanho, lista[i].n);
            printf("\nO numero %d apareceu %d vezes, ele apareceu na(s) linha(s): ", lista[i].n, count);
        }
        printf("%s ", lista[i].linha);
        ant = lista[i].n;
        count++;
    }
}

void resumo(char *Arq){
    FILE *fe = fopen(Arq, "r");
    if (!fe) exit(1);
    int r, n, pos = 0, linha = 1;
    Numero lista[100];
    r = fscanf(fe, "%d", &n);
    while (r==1){
        Numero x = start(n, linha);
        linha++;
        lista[pos++] = x;
        r = fscanf(fe, "%d", &n); 
    }
    bubble2(lista, pos);
    imp(lista, pos);
    fclose(fe);
}
