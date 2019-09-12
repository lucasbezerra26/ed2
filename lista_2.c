#include<stdio.h> 
#include<stdlib.h>
#include <time.h>


struct arvAVL{ 
	int info; 
	struct arvAVL *esq; 
	struct arvAVL *dir; 
	int altura; 
};

typedef struct arvAVL arvAVL;

// Função utilizada para pegar o valor máximo entre os dois inteiros 
int max(int a, int b); 
arvAVL *busca(arvAVL **r, int k);
void imprimir(arvAVL **raiz);


// Pega a altura da árvore
int altura(arvAVL *raiz){ 
	if (raiz == NULL) 
		return 0; 
	return raiz->altura; 
} 

int gerarNumAleatorio(){
    return ((rand() % 1000) + 1);
}

int max(int a, int b) { 
	return (a > b)? a : b; 
} 

// Aloca um novo nó, adiciona o valor a ele e inicializa os ponteiros da esquerda 
// e direita com null
arvAVL *alocaNo(int valor) { 
	arvAVL *no = (arvAVL*) malloc(sizeof(arvAVL)); 
	no->info = valor; 
	no->esq = NULL; 
	no->dir = NULL; 
	no->altura = 0; 
	return no; 
} 

// rotação RR  
void rotacaoRR(arvAVL **no) { 
  arvAVL *aux;
  aux = (*no)->dir;
  (*no)->dir = aux->esq;
  aux->esq = *no;
  *no = aux;
}

// rotação LL  
void rotacaoLL(arvAVL **no) { 
  arvAVL *aux;
  aux = (*no)->esq;
  (*no)->esq = aux->dir;
  aux->dir = *no;
  *no = aux;
}

int numeroNos(arvAVL *raiz){
	if(raiz == NULL ) return 0;
	return numeroNos(raiz->esq)+1+numeroNos(raiz->dir);
}

void profundidade_maior(arvAVL **raiz,arvAVL **maior, int *nivel){
    int numeroNoDir = numeroNos((*raiz)->dir);
    int numeroNoEsq = numeroNos((*raiz)->esq);
    if(!((*raiz)->dir == NULL && (*raiz)->esq == NULL)){
        (*nivel)++;
        if(numeroNoDir > numeroNoEsq){
            (*maior) =  (*raiz)->dir;
            profundidade_maior(&(*raiz)->dir, &(*maior), nivel);
        }else{
            (*maior) =  (*raiz)->esq;
            profundidade_maior(&(*raiz)->esq, &(*maior), nivel);
        }
    }
}

void profundidade_menor(arvAVL **raiz,arvAVL **menor, int *nivel){
    int numeroNoDir = numeroNos((*raiz)->dir);
    int numeroNoEsq = numeroNos((*raiz)->esq);
    if( ((*raiz)->dir != NULL) && ((*raiz)->esq != NULL) ){
        (*nivel)++;
        if(numeroNoDir < numeroNoEsq){
            (*menor) =  (*raiz)->dir;
            profundidade_menor(&(*raiz)->dir, &(*menor), nivel);
        }else{
            (*menor) =  (*raiz)->esq;
            profundidade_menor(&(*raiz)->esq, &(*menor), nivel);
        }
    }else{
        if ((*raiz)->dir == NULL && (*raiz)->esq != NULL){
            profundidade_menor(&(*raiz)->esq, &(*menor), nivel);
        }else{
            if( (*raiz)->dir != NULL && (*raiz)->esq == NULL ){
                profundidade_menor(&(*raiz)->dir, &(*menor), nivel);
            }else{
                (*menor) = (*raiz);
            }
        }
    }
}

arvAVL *busca (arvAVL **r, int k) {
    if (*r == NULL || (*r)->info == k)
       return *r;
    if ((*r)->info > k)
       return busca(&(*r)->esq, k);
    else
       return busca(&(*r)->dir, k);
}

int fatorBalanceamento(arvAVL *raiz){ 
	if (raiz == NULL) 
		return 0; 
	return altura(raiz->esq) - altura(raiz->dir); 
}


int inserir(arvAVL **raiz, int valor){
    int insere = 1;
    if( *raiz == NULL){
        *raiz = alocaNo(valor);
    }else{
        if(valor < (*raiz)->info){
            if (inserir(&((*raiz)->esq), valor) == 1){
                if (abs(fatorBalanceamento(*raiz)) == 2){
                    printf("OLA");
                    if(valor < ((*raiz)->esq)->info){
                        printf("Rotacao LL\n");
                        rotacaoLL(raiz);
                    }
                    else{
                        printf("Rotacao LR\n");
                        rotacaoRR(&((*raiz)->esq));
                        rotacaoLL(raiz);
                        
                        // rotacaoLR(raiz);
                    }
                }
            }     
        }else{
            if ( valor > (*raiz)->info ){
                if (inserir(&((*raiz)->dir), valor) == 1){
                    if (abs(fatorBalanceamento(*raiz)) == 2){
                        if(valor > ((*raiz)->dir)->info){
                            printf("Rotacao RR\n");
                            rotacaoRR(raiz);
                        }else{
                            imprimir(raiz);
                            printf("Rotacao RL\n");
                            printf("Raiz %d\n",(*raiz)->info);
                            rotacaoLL(&((*raiz)->dir));
                            rotacaoRR(raiz);
                            // rotacaoRl(raiz);
                        }
                    }
                }
            }else
                insere = 0;
        }
        (*raiz)->altura = max( altura((*raiz)->esq), altura((*raiz)->dir))+1;
    }
    // printf("ALTURA (%d): %d\n",valor, (*raiz)->altura);
    return insere;
}

// Insere na árvore e já faz o balaceamento, caso necessario;
// void inserir(arvAVL **raiz, int valor){ 
// 	if (*raiz == NULL) {
//         imprimir(raiz);
// 		*raiz = alocaNo(valor); 
//     }

// 	if (valor < (*raiz)->info) 
// 		inserir(&(*raiz)->esq, valor);

// 	else if (valor > (*raiz)->info) 
// 		inserir(&(*raiz)->dir, valor); 

// 	int fb = abs(fatorBalanceamento(*raiz));
//     printf("=========== %d\n", fatorBalanceamento((*raiz)->esq));
//     printf("=========== %d\n", fatorBalanceamento((*raiz)->dir));
// 	printf("comparando o fb de %d = %d\n", (*raiz)->info, fb);

// 	if (fb > 1){	
// 		printf("============ entrou aqui\n");
// 		printf("============ antes\n");
// 	    imprimir(raiz);
// 		printf(" \nveio aqui\n");		
// 		if ((*raiz)->esq && valor <= (*raiz)->info){
// 			if((*raiz)->esq->esq)
// 				rotacaoLL(&(*raiz)); 
// 			else{
// 				rotacaoRR(&(*raiz)->esq); 
// 				rotacaoLL(&(*raiz));
// 			}
// 		}
// 		else{
// 			if((*raiz)->dir->dir)
// 				rotacaoRR(&(*raiz)); 
// 			else{
// 				rotacaoLL(&(*raiz)->dir); 
// 				rotacaoRR(&(*raiz));
// 			}
// 		}
//         printf("============ depois\n");
// 	    imprimir(raiz);
// 		printf("\n");		
// 	}
	
//     (*raiz)->altura = 1 + max(altura((*raiz)->esq), altura((*raiz)->dir)); 

// } 

void imprimir(arvAVL **raiz){
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

int main1(){
    arvAVL *raiz, *aux;
    arvAVL *maior;
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

        for(int i = 0; i < 13; i++){
            int num = gerarNumAleatorio();
            inserir(&raiz, num);
        }
        clock_t fim = clock();
        float segundos = (float)(fim - inicio) / CLOCKS_PER_SEC;
        printf("Inserido 1000 elementos em %.4f segundos.\n", segundos);
        imprimir(&raiz);
        printf("\n");

        profundidade_maior(&raiz, &maior, &nivel_maior);
        printf("Maior Nível: %d\n", nivel_maior);

        profundidade_menor(&raiz, &aux, &nivel_menor);
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


int main(){ 
  arvAVL *root = NULL; 

//   inserir(&root, 647); 
//   inserir(&root, 663); 
//   inserir(&root, 930); 
//   inserir(&root, 874); 
//   inserir(&root, 665); 
//   inserir(&root, 651); 
//   inserir(&root, 770); 
//   inserir(&root, 673); 
//   inserir(&root, 988); 
    
    inserir(&root, 663); 
    inserir(&root, 647); 
    inserir(&root, 930); 
    inserir(&root, 874); 
    inserir(&root, 665); 
    // inserir(&root, 664); 
    // inserir(&root, 662); 
    
    // inserir(&root, 667); 
    // inserir(&root, 668); 
    // inserir(&root, 669); 
    // inserir(&root, 670); 
    // inserir(&root, 671); 
    // inserir(&root, 600); 
    // inserir(&root, 601); 
    // inserir(&root, 602); 
    // inserir(&root, 100); 
    // inserir(&root, 1100); 


//   inserir(&root, 40); 
//   inserir(&root, 50); 
//   inserir(&root, 25); 

  imprimir(&root);
  printf("\n");

  return 0; 
} 
