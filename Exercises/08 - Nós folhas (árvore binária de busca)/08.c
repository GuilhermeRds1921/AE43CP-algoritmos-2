#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
struct NO{
    int val;
    struct NO *esq;
    struct NO *dir;
};
typedef struct NO* Arvore;
Arvore* criar(){
    Arvore* raiz = (Arvore*) malloc(sizeof (Arvore));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}
int inserir(Arvore* raiz,int valor){
    if(raiz == NULL)
        return 0;

    struct NO* novo;
    novo = (struct NO*) malloc(sizeof(struct NO));
    if(novo == NULL)
        return 0;

    novo->val = valor;
    novo->dir = NULL;
    novo->esq = NULL;

    if(*raiz == NULL)
        *raiz = novo;
    else{
        struct NO* atual = *raiz;
        struct NO* ant = NULL;
        while(atual != NULL){
            ant = atual;
            if(valor == atual->val){
                free(novo);
                return 0;
            }
            if(valor > atual->val)
                atual = atual->dir;
            else
                atual = atual->esq;
        }
            if(valor > ant->val)
                ant->dir = novo;
            else
                ant->esq = novo;
    }
    return 1;
}
void percorrer(Arvore* raiz){
    if(raiz == NULL)
        return;

    if(*raiz != NULL){
        percorrer(&((*raiz)->esq));
        percorrer(&((*raiz)->dir));
        if((*raiz)->esq == NULL && (*raiz)->dir == NULL)
            printf(" %d", (*raiz)->val);
    }
}
int main() {
    int i, n, val, conf;
    scanf("%d", &n);
    Arvore* raiz = criar();
    for(i=0; i<n; i++){
        scanf("%d", &val);
        conf = inserir(raiz, val);
        if(conf == 0)
            printf("erro");
    }
    percorrer(raiz);
    return 0;
}
