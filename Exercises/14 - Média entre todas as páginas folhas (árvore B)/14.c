#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define N 5
typedef struct NodeB NodeB;
struct NodeB{
     int nro_chaves;
     int chaves[N - 1];
     NodeB *filhos[N];
     int eh_no_folha;
};
NodeB* criar(){
    NodeB *tree= malloc(sizeof(NodeB));
    int i;
    tree->eh_no_folha = 1;
    tree->nro_chaves = 0;

    for (i = 0; i < N; i++)
        tree->filhos[i] = NULL;

    return tree;
}
static int busca_binaria(int key, NodeB *tree){
    int ini, fim, meio;

    if (tree != NULL){
        ini = 0;
        fim = tree->nro_chaves - 1;

        while (ini <= fim){
            meio = (ini + fim) / 2;

            if (tree->chaves[meio] == key)
                return meio;
            else if (tree->chaves[meio] > key)
                fim = meio - 1;
            else
                ini = meio + 1;
        }

        return ini;
    }

    return -1;
}
static NodeB * split_pag(NodeB *pai, int posF_cheio){
    int i;
    NodeB *pag_esq = pai->filhos[posF_cheio];
    NodeB *pag_dir;

    pag_dir = criar();

    pag_dir->eh_no_folha = pag_esq->eh_no_folha;

    pag_dir->nro_chaves = round((N - 1) / 2);

    for (i = 0; i < pag_dir->nro_chaves; i++)
        pag_dir->chaves[i] = pag_esq->chaves[i + pag_dir->nro_chaves];

    if (!pag_esq->eh_no_folha)
        for (i = 0; i < pag_dir->nro_chaves; i++)
            pag_dir->filhos[i] = pag_esq->filhos[i + pag_dir->nro_chaves];

    pag_esq->nro_chaves = (N - 1) / 2;

    for (i = pai->nro_chaves + 1; i > posF_cheio + 1; i--)
        pai->filhos[i + 1] = pai->filhos[i];

    pai->filhos[posF_cheio + 1] = pag_dir;

    pai->filhos[posF_cheio] = pag_esq;

    pai->chaves[posF_cheio] = pag_dir->chaves[0];

    pai->nro_chaves++;

    for (i = 0; i < pag_dir->nro_chaves ; i++)
        pag_dir->chaves[i] = pag_dir->chaves[i + 1];

    pag_dir->nro_chaves--;


    return pai;
}
static NodeB * inserir_pagina_nao_cheia(NodeB *tree, int key){
    int i;
    int pos = busca_binaria(key, tree);
    if (tree->eh_no_folha){
        for (i = tree->nro_chaves; i > pos; i--)
            tree->chaves[i] = tree->chaves[i - 1];
        tree->chaves[i] = key;
        tree->nro_chaves++;
    }else{
        if (tree->filhos[pos]->nro_chaves == N - 1){
            tree = split_pag(tree, pos);
            if (key > tree->chaves[pos])
                pos++;
        }
        tree->filhos[pos] = inserir_pagina_nao_cheia(tree->filhos[pos], key);

    }

    return tree;
}
NodeB * inserir(NodeB *tree, int key){
    NodeB *aux = tree;
    NodeB *nova_pag;
    if (aux->nro_chaves == N - 1){
        nova_pag = criar();
        tree = nova_pag;
        nova_pag->eh_no_folha = 0;
        nova_pag->filhos[0] = aux;
        nova_pag = split_pag(nova_pag, 0);
        nova_pag = inserir_pagina_nao_cheia(nova_pag, key);
        tree = nova_pag;
    }else
        tree = inserir_pagina_nao_cheia(aux, key);
    return tree;
}
int Media_entre_todas_as_paginas_folhas(NodeB* raiz){
    int i=0,j=0, a=0, k, soma=0, med=0;
    NodeB* auxA = raiz;
    NodeB* auxB;
    if(raiz->eh_no_folha == 1)
        for(k=0; k<raiz->nro_chaves; k++){
               soma += raiz->chaves[k];
               med++;
        }
    while(raiz->eh_no_folha != 1){
        auxB = raiz;
        raiz = raiz->filhos[i];
        if(raiz->eh_no_folha == 1)
           for(k=0; k<raiz->nro_chaves; k++){
               soma+=raiz->chaves[k];
               med++;
            }
        if(raiz->eh_no_folha == 1 && i < auxB->nro_chaves){
            raiz = auxB;
            i++;
            if(auxB == auxA)
                j++;
            if(a==1){
                a=0;
                i--;
            }
        }
        else if(raiz->eh_no_folha == 1 && i >= auxB->nro_chaves && j<auxA->nro_chaves){
            raiz = auxA;
            j++;
            i=j;
            a=1;
        }
    }
    return soma/med;
}

int main(){
    int i, n, valor;
    scanf("%d", &n);
    NodeB* raiz = criar();

    for(i=0; i<n; i++){
        scanf("%d", &valor);
        raiz = inserir(raiz, valor);
    }
    printf("%d", Media_entre_todas_as_paginas_folhas(raiz));
    return 0;
}
