#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct arv{
    int info;
    struct arv *dir,*esq;
}; 

typedef struct arv arv;

arv *busca (arv **r, int k);

void inserir(arv **raiz, int valor){
    if( *raiz == NULL){
        *raiz = (arv*)malloc(sizeof(arv));
        (*raiz)->info = valor;
        (*raiz)->esq = (*raiz)->dir = NULL;
        clock_t inicio = clock();
        busca(&raiz, 30);
        clock_t fim = clock();
        float segundos = (float)(fim - inicio) / CLOCKS_PER_SEC;
        printf("Busca do elemento 30. Demorou em %.4f segundos.\n", segundos);
    }else{
        if( valor < (*raiz)->info ){
            inserir(&(*raiz)->esq, valor);
        }else{
            inserir(&(*raiz)->dir, valor);
        }
    }
}

arv *alocaNo(int info){
    arv *aux;
    aux =(arv*) malloc(sizeof(arv));
    aux->info = info;
    aux->dir = NULL;
    aux->esq = NULL;
    return aux;
}

int gerarNumAleatorio(){
    return ((rand() % 1000) + 1);
}

int numeroNos(arv **raiz){
	if(*raiz == NULL) return 0;
	return numeroNos(&(*raiz)->esq)+1+numeroNos(&(*raiz)->dir);
}

int profundidade_maior(arv **raiz,arv **maior){
    int numeroNoDir = numeroNos(&(*raiz)->dir);
    int numeroNoEsq = numeroNos(&(*raiz)->esq);
    if(!((*raiz)->dir == NULL && (*raiz)->esq == NULL)){
        if(numeroNoDir > numeroNoEsq){
            (*maior) =  (*raiz)->dir;
            profundidade_maior(&(*raiz)->dir, &(*maior));
        }else{
            (*maior) =  (*raiz)->esq;
            profundidade_maior(&(*raiz)->esq, &(*maior));
        }
    }
    return (*raiz)->info;
}

int profundidade_menor(arv **raiz,arv **maior){
    int numeroNoDir = numeroNos(&(*raiz)->dir);
    int numeroNoEsq = numeroNos(&(*raiz)->esq);
    if(!((*raiz)->dir == NULL && (*raiz)->esq == NULL)){
        if(numeroNoDir < numeroNoEsq){
            (*maior) =  (*raiz)->dir;
            profundidade_menor(&(*raiz)->dir, &(*maior));
        }else{
            (*maior) =  (*raiz)->esq;
            profundidade_menor(&(*raiz)->esq, &(*maior));
        }
    }
    return (*raiz)->info;
}

arv *busca (arv **r, int k) {
    if (*r == NULL || (*r)->info == k)
       return *r;
    if ((*r)->info > k)
       return busca(&(*r)->esq, k);
    else
       return busca(&(*r)->dir, k);
}

void imprimir(arv **raiz){
    if(*raiz){
        printf("(");
        printf("%d ", (*raiz)->info);
        imprimir(&(*raiz)->esq);
        imprimir(&(*raiz)->dir);
        printf(")");
    }
}

int main(){
    arv *raiz, *aux;
    raiz = NULL;

    clock_t inicio = clock();

    for(int i = 0; i < 5; i++){
        int num = gerarNumAleatorio();
        inserir(&raiz, num);
    }
    clock_t fim = clock();
    float segundos = (float)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Inserido 1000 elementos em %.4f segundos.\n", segundos);

    imprimir(&raiz);
    printf("\n");

    return 0;
}
