#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
struct NO{
    int val;
    int alt;
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
    novo->alt = 0;
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
                return 1;
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
int Ver_Avl(Arvore* raiz){
    if(raiz == NULL || *raiz == NULL)
        return 0;

    int alt_esq = Ver_Avl(&((*raiz)->esq));
    int alt_dir = Ver_Avl(&((*raiz)->dir));

    if(labs(alt_esq - alt_dir) >= 2)
        return 9999;
    if(alt_esq > alt_dir)
        return (alt_esq +1);
    else
        return(alt_dir + 1);
}
int main() {
    int i, n, val, verifica;
    scanf("%d", &n);
    Arvore* raiz = criar();

    for(i=0; i<n; i++){
        scanf("%d", &val);
        verifica = inserir(raiz, val);
    }
    verifica = Ver_Avl(raiz);
    if(verifica < 9999)
        printf("1");
    else
        printf("0");
    return 0;
}
