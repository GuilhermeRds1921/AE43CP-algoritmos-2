#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
typedef struct NodeVP NodeVP;
struct NodeVP{
    int key;
    int color;
    NodeVP *father;
    NodeVP *left;
    NodeVP *right;
};


NodeVP* criar_AVP(int key){
    NodeVP* tree = (NodeVP*) malloc(sizeof(NodeVP));
    tree->key = key;
    tree->color = 0;
    tree->left = NULL;
    tree->right = NULL;
    tree->father = NULL;

    return tree;
}


int liberar(NodeVP *tree){
    if (tree != NULL){
        free(tree);

        return 1;
    }

    return 0;
}

NodeVP* obter_avo(NodeVP *no){
    if ((no != NULL) && (no->father != NULL)){
        return no->father->father;
    }

    return NULL;
}


NodeVP* obter_tio(NodeVP *no){
    NodeVP* avo = obter_avo(no);
    NodeVP* aux = NULL;


    if (avo != NULL){
        if (avo->left == no->father){
            aux = avo->right;
        }else
            aux = avo->left;
    }

    return aux;
}


NodeVP* rotacionar_dir(NodeVP *x){
    NodeVP *p = x->father;
    NodeVP *a = p->father;

    p->father = a->father;

    if (a->father != NULL){

        if (a->father->left == a)
            a->father->left = p;
        else
            a->father->right = p;
    }

    a->father = p;
    a->left = p->right;
    p->right = a;

    x = p;

    return x;
}


NodeVP* rotacionar_esq(NodeVP *x){
    NodeVP *p = x->father;
    NodeVP * a = p->father;

    p->father = a->father;

    if (a->father != NULL){

        if (a->father->right == a)
            a->father->right = p;
        else
            a->father->left = p;
    }

    a->father = p;
    a->right = p->left;
    p->left = a;

    x = p;

    return x;
}


NodeVP* rotacionar_dir_esq(NodeVP *x){
    NodeVP *p = x->father;
    NodeVP *a = p->father;

    x->father = a;
    a->left = x;
    p->left = x->right;
    x->right = p;
    p->father = x;


    return x = rotacionar_esq(p);
}


NodeVP* rotacionar_esq_dir(NodeVP *x){
    NodeVP *p = x->father;
    NodeVP * a = p->father;

    x->father = a;
    a->left = x;
    p->father = x;
    p->right = x->left;
    x->left = p;


    return x = rotacionar_dir(p);
}


NodeVP* balancear(NodeVP *x){
    NodeVP *pai, *tio;

    if (x->father == NULL){
        x->color = 1;
    }else{
        pai = x->father;

        if (pai->color == 0){
            tio = obter_tio(x);

            if ((tio != NULL) && (tio->color == 0)){
                pai->color = tio->color = 1;
                x = obter_avo(x);

            if (x->father != NULL)
                x->color = 0;
            }else{

                if (pai->left == x){
                    if (pai->father->right == pai)
                        x = rotacionar_dir_esq(x);
                    else
                        x = rotacionar_dir(x);
                }else{
                    if (pai->father->left == pai)
                        x = rotacionar_esq_dir(x);
                    else
                        x = rotacionar_esq(x);
                }

                x->color = 1;

                if(x->left != NULL)
                    x->left->color = 0;

                if(x->right != NULL)
                    x->right->color = 0;
            }
        }
    }

    return x;
}


NodeVP* inserir(NodeVP *tree, int key){
    NodeVP *auxP, *auxF;

    if(tree == NULL){
        tree = criar_AVP(key);
        tree->color = 1;
    }
    else{
        auxP = auxF = tree;

        while(auxF != NULL){
            auxP = auxF;

            if(key < auxF->key)
                auxF = auxF->left;
            else
                auxF = auxF->right;
        }

        auxF = criar_AVP(key);
        auxF->father = auxP;

        if(auxF->key < auxP->key)
            auxP->left = auxF;
        else
            auxP->right = auxF;

        while((auxF->father != NULL)  && (auxF->color == 0) && (auxF->father->color == 0))
            auxF = balancear(auxF);

        while(auxF->father != NULL)
            auxF = auxF->father;

        tree = auxF;
    }
    return tree;
}

int altura(NodeVP* raiz){
    int i =0;
    NodeVP* NO;
    while(raiz != NULL){
        if(raiz->color == 1)
            i++;
        raiz = raiz->left;

    }
    return i;
}
int main() {
    int i, n, valor;
    scanf("%d", &n);
    NodeVP* raiz = NULL;

    for(i=0; i<n; i++){
        scanf("%d", &valor);
        raiz = inserir(raiz, valor);
    }

    n = altura(raiz);
    liberar(raiz);
    printf("%d", n);
    return 0;
}
