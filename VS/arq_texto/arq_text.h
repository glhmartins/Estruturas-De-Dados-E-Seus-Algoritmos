#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct aluno{
    char nome[20];
    double p1, p2, media;
} TA;

typedef struct num{
    int num, linhas[10];
} TNUM;

void RetRepet(char *ArqEnt, char *ArqSaida);
void media(char *ArqEnt, char *ArqSaida);
void resumo(char *arq);