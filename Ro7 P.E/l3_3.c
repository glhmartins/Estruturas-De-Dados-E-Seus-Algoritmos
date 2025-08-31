#include <stdio.h>

int digitos(int n){
    int digs = 0;
    while (n>0){
        n/=10;
        digs++;
    }
    return digs;
}

void bubble(int arr[], int size){
    int aux;
    for (int i = 0; i<size-1; i++){
        for (int k = i+1; k<size; k++){
            printf("a");
            if (arr[i] != arr[k]){
                aux = arr[i];
                arr[i] = arr[k];
                arr[k] = aux;
            }
        }
    }
    
}

int main(){
    
    int n,m, dig_n, dig_m, igual = 1;
    scanf("%d %d", &n, &m);
    dig_n = digitos(n);
    dig_m = digitos(m);
    int vetn[dig_n], vetm[dig_m];
    if (dig_m!=dig_n) printf("nao eh permutacao\n");
    else {
        int a = n, b = m;
        for (int i = 0; i<dig_m; i++){
            vetn[i] = a%10;
            n/=10;
            a = n;
            vetm[i] = b%10;
            m/=10;
            b = m;
        }
        int tam = sizeof(dig_n)/sizeof(int);
        bubble(vetn, tam);
        bubble(vetm, tam);
        for (int i = 0; i<dig_m; i++){
            printf("%d %d\n", vetn[i], vetm[i]);
            if (vetm[i] != vetn[i]) igual = 0;
        }
        if (igual == 0) printf("nao eh permutacao\n");
        else printf("eh permutacao\n");
    }   
    
    return 0;

}