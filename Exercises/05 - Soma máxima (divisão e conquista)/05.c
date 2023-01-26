#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
int recursao(int* v, int ini, int fim){
    int meio, v1=0, v2=0;
    if(fim - ini <= 1){
        if(ini == fim){
            if(v[ini] > 0)
                return v[ini];
        }
        else{
            meio = 0;
            if(v[ini] > 0)
                meio += v[ini];
            if(v[fim]> 0)
                meio += v[fim];
            return meio;
        }
    }
    else{
        meio = (ini + fim)/2;
        v1 += recursao(v, ini, meio);
        v2 += recursao(v, meio+1, fim);
    }
    return v1+v2;
}
int main() {
    int i, num, sum;
    scanf("%d", &num);
    int v[num], ini=0, fim = num-1;
    for(i=0; i<num; i++)
        scanf("%d", &v[i]);
    sum = recursao(v, ini, fim);
    printf("%d", sum);
    return 0;
}
