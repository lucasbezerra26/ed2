#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct arv{
    int info;
    struct arv *dir,*esq;
}; 

typedef struct arv arv;

void inserir(arv **raiz, arv **no){
    if( *raiz == NULL){
        raiz = no;
    }else{
        if( (*raiz)->info < (*no)->info ){
            inserir(&(*raiz)->esq, no);
        }else{
            inserir(&(*raiz)->dir, no);
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

void profundidade(arv **raiz,arv **maior){
    int numeroNoDir = numeroNos(&(*raiz)->dir);
    int numeroNoEsq = numeroNos(&(*raiz)->esq);
    if(numeroNoDir > numeroNoEsq){
        (*maior) =  (*raiz)->dir;
        profundidade(&(*raiz)->dir, &(*maior));
    }else{
        (*maior) =  (*raiz)->esq;
        profundidade(&(*raiz)->esq, &(*maior));
    }
}

arv *busca (arv **r, int k) {
    if (*r == NULL || (*r)->info == k)
       return *r;
    if ((*r)->info > k)
       return busca(&(*r)->esq, k);
    else
       return busca(&(*r)->dir, k);
}

int main(){
    arv *raiz, *aux;
    arv *maior;
    raiz = (arv*) malloc(sizeof(arv));

    clock_t inicio = clock();

    for(int i = 0; i < 1000; i++){
        int num = gerarNumAleatorio();
        aux = alocaNo(num);
        inserir(&raiz, &aux);
    }   
    clock_t fim = clock();
    float segundos = (float)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Inserido 1000 elementos em %.4f segundos.\n", segundos);
    profundidade(&raiz,&maior);
    printf
    return 0;
}
