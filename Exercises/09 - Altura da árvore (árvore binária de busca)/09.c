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
int altura(Arvore* raiz){
    if(raiz == NULL || *raiz == NULL)
        return 0;

    int alt_esq = altura(&((*raiz)->esq));
    int alt_dir = altura(&((*raiz)->dir));
    if(alt_esq > alt_dir)
        return (alt_esq +1);
    else
        return(alt_dir + 1);
}
int main() {
    int i, n, val, conf;
    Arvore* raiz = criar();
    scanf("%d", &n);
    for(i=0; i<n; i++){
        scanf("%d", &val);
        conf = inserir(raiz, val);
        if(conf == 0)
            printf("erro");
    }
    printf("%d", altura(raiz)-1); //para retirar a altura do noh raiz.
    return 0;
}
