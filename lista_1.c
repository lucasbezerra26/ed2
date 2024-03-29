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

int numeroNos(arv *raiz){
	if(raiz == NULL ) return 0;
	return numeroNos(raiz->esq)+1+numeroNos(raiz->dir);
}

int profundidade_maior(arv **raiz){
    if (!(*raiz)){
        return -1;
    }else{
        int numeroNoDir = profundidade_maior(&(*raiz)->dir);
        int numeroNoEsq = profundidade_maior(&(*raiz)->esq);
        if ( numeroNoEsq < numeroNoDir ){
            return numeroNoDir+1;
        }else{
            return numeroNoEsq+1;
        }
    }
}

int profundidade_menor(arv **raiz){
    if (!(*raiz)){
        return -1;
    }else{
        int numeroNoDir = profundidade_menor(&(*raiz)->dir);
        int numeroNoEsq = profundidade_menor(&(*raiz)->esq);
        if ( numeroNoEsq > numeroNoDir ){
            return numeroNoDir+1;
        }else{
            return numeroNoEsq+1;
        }
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

void imprimir(arv **raiz){
    if(*raiz){
        printf("(");
        printf("%d ", (*raiz)->info);
        imprimir(&(*raiz)->esq);
        imprimir(&(*raiz)->dir);
        printf(")");
    }else{
        printf("()");
    }
    
}

int main(){
    arv *raiz, *aux;
    arv *maior;
    int nivel_menor = 0, nivel_maior;
    srand(time(NULL));
    int *vetor;
    vetor = (int*) calloc(sizeof(int),1000);
    for (int i = 0; i < 30; i++){
        nivel_menor = 0;
        nivel_maior =  0;

        printf("+----------------------------+\n");
        printf("======= %d INTERAÇÃO =========\n", i+1);
        printf("+----------------------------+\n");
        
        raiz = NULL;
        // maior = NULL;
        clock_t inicio = clock();

        for(int i = 0; i < 1000; i++){
            int num = gerarNumAleatorio();
            inserir(&raiz, num);
        }
        clock_t fim = clock();
        float segundos = (float)(fim - inicio) / CLOCKS_PER_SEC;
        printf("Inserido 1000 elementos em %.4f segundos.\n", segundos);
        imprimir(&raiz);
        printf("\n");

        nivel_maior = profundidade_maior(&raiz);
        printf("Maior Nível: %d\n", nivel_maior);

        nivel_menor = profundidade_menor(&raiz);
        printf("Menor Nível: %d\n", nivel_menor);
        // printf("Num: %d \n", num);

        inicio = clock();
        busca(&raiz, 30);
        fim = clock();
        segundos = (float)(fim - inicio) / CLOCKS_PER_SEC;
        printf("Busca do elemento 30. Demorou em %.4f segundos.\n", segundos);
        int difrenca = nivel_maior-nivel_menor;
        vetor[difrenca]++;
    }
    for(int i=0; i<1000; i++){
        if( vetor[i] != 0 ){
            printf("A quantidade de vezes que a diferenca foi %d é %d\n",i,vetor[i]);
        }
    }
    return 0;
}
