#include <stdio.h>

int main(){

    int n, m, digitos = 0, binario[16];
    scanf("%d", &n);
    m = n;
    while (m>0){
        
        binario[digitos] = m%2;
        m/=2;
        digitos++;

    }

    for (int j = digitos-1; j>=0; j--){
        printf("%d", binario[j]);
    }
    
    return 0;

}