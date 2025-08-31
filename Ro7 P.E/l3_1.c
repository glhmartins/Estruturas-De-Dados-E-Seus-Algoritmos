#include <stdio.h>

int main(){

    int n, primo = 0, numero;

    scanf("%d", &n);

    int vetor[n-1];

    for (int i = 2; i<=n; i++){
        vetor[i-2] = i;
    }

    for (int i = 0; i<n-1; i++){
        for (int k = 1; k<=vetor[i]; k++){
            if (vetor[i]%k == 0) primo++;
        }
        if (primo == 2) numero = vetor[i];
        for (int j = i; j<n-1; j++){
            if (vetor[j] != numero && vetor[j]%numero==0) vetor[j] = 0;
        }
        primo = 0;
    }

    for (int i = 0; i<n-1; i++){
        if (vetor[i] != 0) printf("%d\n", vetor[i]);
    }

    return 0;

}
