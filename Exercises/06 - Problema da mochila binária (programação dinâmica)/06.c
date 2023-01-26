#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
int** iniciar(int qnt){
    int i, j;
    int ** m = malloc(qnt * sizeof(int*));
    for(i=0; i<qnt; i++)
        m[i] = malloc(2 * sizeof(int));
    for(i=0; i<qnt; i++)
        for(j=0; j<2; j++)
            scanf("%d", &m[i][j]);
    return m;
}
int Dinamica(int** m, int qnt, int bag){
  int temp[qnt+1][bag+1], i, j, k=0;

    for(i=0; i < qnt+1; i++){
        for(j=0; j<bag+1; j++){
            if(i == 0)
                temp[i][j] = 0;
            else{
                if(j-m[k][0] < 0)
                    temp[i][j] = temp[i-1][j];
                else if( temp[i-1][j] > (m[k][1] + temp[i-1][j-m[k][0]]) )
                    temp[i][j] = temp[i-1][j];
                else
                    temp[i][j] = m[k][1] + temp[i-1][j-m[k][0]];
            }
        }
        if(i!=0)
             k++;
    }
      for(i=0; i<qnt+1; i++)
        for(j=0; j<bag+1; j++)
            if(i==qnt && j == bag)
                printf("%d ", temp[i][j]);
    return 0;
}
void liberar(int** m, int qnt){
    int i;
     for(i=0; i < qnt; i++)
        free(m[i]);
    free(m);
}
int main() {
    int bag, qnt;
    scanf("%d\n%d", &bag, &qnt);
    int ** m = iniciar(qnt);

    Dinamica(m, qnt, bag);
    liberar(m, qnt);

    return 0;
}
