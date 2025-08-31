#include <stdio.h>

void n_primos(int n){

    int contador = 0, primo = 0, number = 2;

    while (contador!=n){
        for (int i = 1; i<=number; i++){
            if (number%i == 0) primo++;
            if (primo>2) break;
        }
        if (primo == 2){
            contador++;
            printf("%d ", number);
        }
        primo = 0;
        number++;
    }
    printf("\n");

}

int main(){

    int n;

    scanf("%d", &n);

    while (n>0){
        n_primos(n);
        scanf("%d", &n);
    }

    return 0;
}