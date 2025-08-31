#include <stdio.h>
#include <stdlib.h>

void cartesiano(char *ArqA, char *ArqB, char *ArqC){
    FILE *a = fopen(ArqA, "rb"), *b = fopen(ArqB, "rb"), *c = fopen(ArqC, "wb");
    if((!a) || (!b) || (!c)) exit(1);
    char ab[12], bb[12];
    int ra, rb, ta = 0, tb = 0, i = 0, j = 0;
    fseek(a, 0 ,SEEK_END);
    fseek(b, 0, SEEK_END);
    ta = ftell(a)/(sizeof(char)*11);
    tb = ftell(b)/(sizeof(char)*11);
    rewind(a);
    rewind(b);
    while(i<ta && j<tb){
        i++;
        j++;
        fread(ab, sizeof(char), 11, a);
        fread(bb, sizeof(char), 11, b);
        fwrite(ab, sizeof(char), 11, c);
        fwrite(bb, sizeof(char), 11, c);
    }
    while(i<ta){
        i++;
        fread(ab, sizeof(char), 11, a);
        fwrite(ab, sizeof(char), 11, c);
    }
    while(j<tb){
        j++;
        fread(bb, sizeof(char), 11, b);
        fwrite(bb, sizeof(char), 11, c);
    }
    fclose(a);
    fclose(b);
    fclose(c);
}

int main(){
    cartesiano("a.bin", "b.bin", "c.bin");
    return 1;
}