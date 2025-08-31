#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ler(char *arq){
    FILE *f = fopen(arq, "rb");
    if (!f) exit(1);
    char *c = (char*) malloc(sizeof(char)*20);
    fread(c, sizeof(char), 20, f);
    while(!feof(f)){
        for(int i = 0; i<20; i++){
            printf("%c", c[i]);
        }
        printf("\n");
        fread(c, sizeof(char), 20, f);
    }
    free(c);
    fclose(f);
}

void cartesiano(char *Arq1, char *Arq2, char *Arq3, int tipo, int max_dig){
    FILE *a = fopen(Arq1, "rb"), *b = fopen(Arq2, "rb"), *c = fopen(Arq3, "wb");
    if ((!a) || (!b) || (!c)) exit(1);
    char *x = (char*) malloc(sizeof(char)*11), *y = (char*) malloc(sizeof(char)*11);
    int t1, t2;
    fseek(a, 0, SEEK_END);
    fseek(b, 0, SEEK_END);
    t1 = ftell(a)-tipo;
    t2 = ftell(b)-tipo;
    rewind(a);
    rewind(b);
    while(ftell(a)<=t1){
        fread(x, tipo, max_dig, a);
        while(ftell(b)<=t2){
            fread(y, tipo, max_dig, b);
            fwrite(x, tipo, max_dig, c);
            fwrite(y, tipo, max_dig, c);
        }
        fseek(b, 0, SEEK_SET);
    }
    fclose(a);
    fclose(b);
    fclose(c);
}

int main(void){
    cartesiano("a.bin", "b.bin", "c.bin", sizeof(char), 10);
    /*FILE *a = fopen("a.bin", "wb");
    if(!a) return 1;
    char palavras[15][15] = {"aaaaaaaaaa", "cccccccccc", "eeeeeeeeee"},
         palavras1[15][15] = {"bbbbbbbbbb", "dddddddddd", "ffffffffff"};
    for (int i = 0; i<3; i++){
        fwrite(palavras[i], sizeof(char)*10, 1, a);
    }
    fclose(a);
    FILE *d = fopen("a1.bin", "rb"), *e = fopen("b.bin", "wb");
    if (!a) return 1;
    for(int i = 0; i<3; i++){
        fwrite(palavras1[i], sizeof(char)*10, 1, e);
    }
    fclose(d);
    fclose(e);*/
    ler("c.bin");
    return 0;
}