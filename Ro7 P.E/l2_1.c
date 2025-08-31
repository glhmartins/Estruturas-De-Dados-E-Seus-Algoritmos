#include <stdio.h>
#include <math.h>

int main(){

    int digitos = 0, n, m, a, b, c, d, aux;

    scanf("%d", &n);

    while (n>0){
        m = n;
        while (m>0){
            m/=10;
            digitos++;
        }
        if(digitos<4) printf("Numero invalido\n");
        else{
            aux = pow(10, digitos-2);
            a = n/aux;
            b = n%100;
            c = pow((a+b), 2);
            d = a*100 + b;
            printf("%d = %d (%d e %d)", c, d, a, b);
            if (c == d) printf("1\n");
            else printf("0\n");
        }
        digitos = 0;
        scanf("%d", &n);
    }
    return 0;

}