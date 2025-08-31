#include "arq_text.h"

void RetRepet(char *ArqEnt, char *ArqSaida){
    FILE *ent = fopen(ArqEnt, "r"), *saida = fopen(ArqSaida, "w");
    if((!ent) || (!saida)) exit(1);
    int r;
    char aux[20], aux1[20];
    r = fscanf(ent, "%s", aux);
    fprintf(saida, "%s ", aux);
    while(r == 1){
        r = fscanf(ent, "%s", aux1);
        if(strcmp(aux, aux1)) fprintf(saida, "%s ", aux1);
        strcpy(aux, aux1);
    }
    fclose(ent);
    fclose(saida);
}

void bubble(TA *alunos, int tam){
    TA aux;
    for(int i = 0; i<tam; i++){
        for(int j = 0; j<tam-1; j++){
            if(alunos[j].media<alunos[j+1].media){
                aux = alunos[j];
                alunos[j] = alunos[j+1];
                alunos[j+1] = aux;
            }
        }
    }
}

void media(char *ArqEnt, char *ArqSaida){
    FILE *fpe = fopen(ArqEnt, "r"), *fps = fopen(ArqSaida, "w");
    if((!fpe) || (!fps)) exit(1);
    int i = 0, r;
    TA alunos[100];
    r = fscanf(fpe, "%s %lf %lf", &alunos[i].nome, &alunos[i].p1, &alunos[i].p2);
    alunos[i].media = (alunos[i].p1*0.5)+(alunos[i].p2*0.5);
    while(r == 3){
        i++;
        r = fscanf(fpe, "%s %lf %lf", &alunos[i].nome, &alunos[i].p1, &alunos[i].p2);
        alunos[i].media = (alunos[i].p1*0.5)+(alunos[i].p2*0.5);
    }
    for(r = 0; r<i; r++) printf("%s %.2lf\n", alunos[r].nome, alunos[r].media);
    bubble(alunos, i);
    for(r = 0; r<i; r++) fprintf(fps, "%s %.2lf\n", alunos[r].nome, alunos[r].media);
    fclose(fpe);
    fclose(fps);
}

int verifica(TNUM *nums, int elem, int tam){
    for(int i = 0; i<tam; i++){
        if(nums[i].num == elem) return 1;
    }
    return 0;
}

void adiciona(TNUM *nums, int elem, int linha, int pos){
    nums[pos].num = elem;
    nums[pos].linhas[0] = linha+1;
    for(int i = 1; i<sizeof(nums[pos].linhas)/sizeof(int); i++) nums[pos].linhas[i] = -1;
}

void add_linha(TNUM *nums, int elem, int linha, int pos){
    int i;
    for(i = 0; i<pos; i++) if(nums[i].num == elem) break;
    for(int j = 0; j<sizeof(nums[i].linhas)/sizeof(int); j++){
        if(nums[i].linhas[j] == -1){
            nums[i].linhas[j] = linha+1;
            break;
        }
    }
}

void resumo(char *Arq){
    FILE *fp = fopen(Arq, "r");
    if(!fp) exit(1);
    TNUM numbers[100];
    int r, elem, pos = 0, linha = 0;
    r = fscanf(fp, "%d", &elem);
    adiciona(numbers, elem, linha, pos);
    pos++;
    while(r == 1){
        linha++;
        r = fscanf(fp, "%d", &elem);
        if(!verifica(numbers, elem, pos)){
            adiciona(numbers, elem, linha, pos);
            pos++;
        }
        else add_linha(numbers, elem, linha, pos);
    }
    for(int i = 0; i<pos; i++){
        printf("Num: %d linhas: ", numbers[i].num);
        for(int j = 0; j<sizeof(numbers[0].linhas)/sizeof(int); j++){
            if(numbers[i].linhas[j]>=0) printf("%d ", numbers[i].linhas[j]);
        }
        printf("\n");
    }
    fclose(fp);
}
