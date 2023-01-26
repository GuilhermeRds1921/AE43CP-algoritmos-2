#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
int* binario(int n, int bit){
    int i;
    int* V = malloc(bit * sizeof(int));
    for(i=bit-1; i>=0; i--){
        V[i] = n%2;
        n /= 2;
    }
    return V;
}
int** backtracking(int n, int bag){
    int i, j, peso = 0, all = pow(2, n);
    int** todas = malloc(all * sizeof(int*));
    for(i=0; i<all; i++)
        todas[i] = binario(i, n);
    return todas;
}
int maior(int* peso, int* valor, int** todas, int n, int bag){
    int i, j, max=0, mp, mv;
    for(i=0; i<pow(2,n); i++){
        mp = 0;
        mv = 0;
        for(j=0; j<n; j++){
            mp += todas[i][j] * peso[j];
            mv += todas[i][j] * valor[j];
        }
        if((mp <= bag)&&(mv >max))
            max = mv;
    }
    return max;
}
int main() {

    int bag, n, i;
    scanf("%d\n%d", &bag, &n);
    int valor[n], peso[n];
    for(i=0; i<n; i++){
        scanf("%d %d", &peso[i], &valor[i]);
    }
    int** todas = backtracking(n, bag);
    printf("%d", maior(peso, valor, todas, n, bag));
    return 0;
}
