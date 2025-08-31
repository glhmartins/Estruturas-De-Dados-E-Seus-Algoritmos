#include <stdio.h>

int main(){

    int n, maior = 0, s_maior = 0, ind = 0;
    scanf("%d", &n);

    while (n>0){

        int suspeitos[n];
        for (int i = 0; i<n; i++){
            scanf("%d", &suspeitos[i]);
            if (suspeitos[i]>maior) maior = suspeitos[i];
        }
        for (int i = 0; i<n; i++){
            if (suspeitos[i]>s_maior && suspeitos[i]!=maior) {
                s_maior = suspeitos[i];
                ind = i+1;
                }
        }
        printf("%d\n", ind);
        maior = s_maior = 0;
        scanf("%d", &n);

    }

    return 0;

}