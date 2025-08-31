#include <stdio.h>

int mdc(int a, int b){

    int mdc = 0;
    if (a>b){
        for (int i = 1; i<=b; i++){
            if (a%i==0 && b%i==0) mdc = i;
        }
    } else {
        for (int i = 1; i<=a; i++){
            if (a%i==0 && b%i==0) mdc = i;
        }
    }

    return mdc;

}

int main(){

    int n, a, b, max_pilhas = 0;
    scanf("%d", &n);
    
    for (int i = 0; i<n; i++){
        scanf("%d %d", &a, &b);
        max_pilhas = mdc(a,b);
        printf("%d\n", max_pilhas);
    }

    return 0;

}