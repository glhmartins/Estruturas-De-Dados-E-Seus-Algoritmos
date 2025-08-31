#include "TH.c"

int main(){
    FILE *c1 = fopen("c1.bin", "wb");
    for(int i = 0; i<5; i++) fwrite(&i, sizeof(int), i, c1);
    fclose(c1);
    FILE *c2 = fopen("c2.bin", "wb");
    for(int i = 0; i<5; i++) fwrite(&i, sizeof(int), i, c2);
    fclose(c2);
    inter("c1.bin", "c2.bin", "inter.bin");
    FILE *inters = fopen("inter.bin", "rb");
    int tam, aux;
    fseek(inters, 0, SEEK_END);
    tam = ftell(inters)/sizeof(int);
    rewind(inters);
    for(int i = 0; i<tam; i++){
        fread(&aux, sizeof(int), 1, inters);
        printf("%d\n", aux);
    }
    return 1;
}