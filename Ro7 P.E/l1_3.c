#include <stdio.h>

int tempo_de_sono(int h1, int m1, int h2, int m2){
    
    if (h1>h2 || (h1==h2 && m1>m2)) h2+=24;

    int minutos = (h2*60+m2) - (h1*60+m1);

    return minutos;

}

int main(){

    int h1, m1, h2, m2, mins;

    scanf("%d %d %d %d", &h1, &m1, &h2, &m2);

    while (h1!=0 || h2!=0 || m1!=0 || m2!=0){

        mins = tempo_de_sono(h1,m1,h2,m2);
        printf("%d\n", mins);
        scanf("%d %d %d %d", &h1, &m1, &h2, &m2);

    }

    return 0;

}