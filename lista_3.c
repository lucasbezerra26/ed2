#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct arv{
    char palavra[100];
    char equivalentes[200];
    char estrutura[100];
    struct arv *dir,*esq;
};
typedef struct arv arv;


void inserir(arv **raiz, arv **no){
    if( *raiz == NULL){
        *raiz = no;
    }else{
        if (strcmp((*no)->palavra, (*raiz)->palavra) == -1) //se menor
        {
            inserir(&(*raiz)->esq, no);
        }else{
            if (strcmp((*no)->palavra, (*raiz)->palavra) == 1)//se maior, se igual a 0 é pq é igual e não pode ter palavra igual
                inserir(&(*raiz)->dir, no);
        }
    }
}

int main(){
    return 0;
}