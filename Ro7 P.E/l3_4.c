#include <stdio.h>

void merge(int vet[], int inicio, int meio, int fim){
    int i = inicio, j = meio+1, k = 0, aux[fim-inicio+1];
    while (i<=meio && j<=fim){
        if (vet[i]<=vet[j]) aux[k++] = vet[i++];
        else aux[k++] = vet[j++];
    }
    while (i<=meio) aux[k++] = vet[i++];
    while (j<=fim) aux[k++] = vet[j++];
    for (k = inicio; k<=fim; k++){
        vet[k] = aux[k-inicio];
    }
}

void mergesort(int vet[], int inicio, int fim){
    if (inicio<fim){
        int meio = (inicio+fim)/2;
        mergesort(vet, inicio, meio);
        mergesort(vet, meio+1, fim);
        merge(vet, inicio, meio, fim);
    }
}

int main(){

    int n, m, rep = 0, aux = 0;
    scanf("%d %d", &n, &m);
    while (n!=0 && m!=0){
        int vet[m];
        for (int i = 0; i<m; i++){
            scanf("%d", &vet[i]);
        }
        mergesort(vet, 0, m-1);
        for (int i = 0; i<m-1; i++){
            printf("%d\n", vet[i]);
            if (vet[i] == vet[i+1] && aux != vet[i]){
                rep++;
            }
            aux = vet[i];

        }
        printf("%d\n", rep);
        scanf("%d %d", &n, &m);
        rep = aux = 0;
    }
    return 0;

}
