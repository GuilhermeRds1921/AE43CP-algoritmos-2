#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
void guloso(int l, int c, int m[l][c]){
    int i, j, descer, esquerda, direita, bilbo=0;
    for(i=0; i<l; i++)
        for(j=0; j<c; j++){
            if(m[i][j] == 10){
                descer =  m[i+1][j];
                esquerda = m[i][j-1];
                direita = m[i][j+1];
                if(descer == 0 || i == l-1)
                    descer = 20;
                if(esquerda == 0 || j == 0)
                    esquerda = 20;
                if(direita == 0 || j == c-1)
                    direita = 20;
                if(descer < esquerda && descer < direita && (descer != 20 && descer !=10)){
                    bilbo += m[i+1][j];
                    m[i+1][j] = 10;
                    j--;
                    i++;
                }
                if(esquerda < descer && esquerda < direita && (esquerda != 20 && esquerda !=10)){
                    bilbo += m[i][j-1];
                    m[i][j-1] = 10;
                    j-= 2;
                }
                if(direita < descer && direita < esquerda && (direita != 20 && direita !=10)){
                    bilbo += m[i][j+1];
                    m[i][j+1] = 10;
                }
            }
            if(esquerda >= 10 && direita >=10 && descer >=10)
                if(i != l-1 || j != c-1){
                    printf("sem solucao");
                    break;
                    }
            if(i== l-1 && j == c-1)
                printf("%d", bilbo);
        }
}
int main(){
    int linhas, colunas, i, j;
    scanf("%d %d", &linhas, &colunas);
    int m[linhas][colunas];

    for(i=0; i<linhas; i++)
        for(j=0; j<colunas; j++){
            scanf("%d", &m[i][j]);
             if(i==0 && j==0)
                m[i][j] = 10;
        }
    guloso(linhas, colunas, m);

    return 0;
}
