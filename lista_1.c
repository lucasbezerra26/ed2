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

arv *buscar(arv **raiz, int ch, arv **pai){
    arv atual = *raiz;
	pai = NULL;
	while(raiz){
		if(r->chave == ch )
			return r;
		*pai = r;
		if( ch < r->chave)
			r = r->esq;
		else
			r = r->dir;
	}
	return NULL;
}

int numeroNos(arv **raiz){
	if(*raiz == NULL) return 0;
	return numeroNos(&(*raiz)->esq)+1+numeroNos(&(*raiz)->dir);
}

int profundidade(arv **raiz,arv **maior, int distancia){
    int numeroNoDir = numeroNos(&(*raiz)->dir);
    int numeroNoEsq = numeroNos(&(*raiz)->esq);
    if(numeroNoDir > numeroNoEsq){
        (*maior) =  (*raiz)->dir;
        profundidade((*raiz)->dir, &(*maior), distancia);
    }else{
        (*maior) =  (*raiz)->esq;
        profundidade((*raiz)->esq, &(*maior), distancia);
    }
}

int main(){
    arv *raiz, *aux;
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

    return 0;
}
