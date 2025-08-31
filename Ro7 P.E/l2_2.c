#include <stdio.h>

int digitos(int n){
    
    int digitos = 0;

    while (n>0){
        n/=10;
        digitos++;
    }

    return digitos;

}

int main(){

    int n, caracteres, palin = 1;
    scanf("%d", &n);

    while (n>=0){

        caracteres = digitos(n);
        int m = n;
        char string[caracteres];
        for (int i = 0; i<caracteres; i++){
            string[i] = m%10;
            m/=10;
        }
        for (int i = 0, j = caracteres-1; i<caracteres; i++, j--){
            if (string[i] != string[j]) palin = 0;
        }
        if (palin) printf("Verdadeiro\n");
        else printf("Falso\n");
        palin = 1;
        scanf("%d", &n);

    }

    return 0;

}