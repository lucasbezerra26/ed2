#include<stdio.h> 
#include<stdlib.h>
#include <time.h>


struct arvAVL{ 
	int info; 
	struct arvAVL *esq; 
	struct arvAVL *dir; 
};

typedef struct arvAVL arvAVL;

// Função utilizada para pegar o valor máximo entre os dois inteiros 
int max(int a, int b); 
arvAVL *busca(arvAVL **r, int k);
void imprimir(arvAVL **raiz);


// Pega a altura da árvore
int altura(arvAVL *raiz){ 
    int n = 0;
	if (raiz == NULL) 
		n = -1;
    else
        n = max(altura(raiz->esq), altura(raiz->dir)) + 1;
	
    return n; 
} 

int gerarNumAleatorio(){
    return ((rand() % 1000) + 1);
}

int max(int a, int b) { 
	return (a > b)? a : b; 
} 

// // Aloca um novo nó, adiciona o valor a ele e inicializa os ponteiros da esquerda 
// e direita com null
arvAVL *alocaNo(int valor) { 
	arvAVL *no = (arvAVL*) malloc(sizeof(arvAVL)); 
	no->info = valor; 
	no->esq = NULL; 
	no->dir = NULL; 
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

int fatoRNalanceamento(arvAVL *raiz){ 
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
                if (abs(altura((*raiz)->esq) - altura((*raiz)->dir)) == 2){
                    if(valor < ((*raiz)->esq)->info){
                        rotacaoLL(raiz);
                    }
                    else{
                        rotacaoRR(&((*raiz)->esq));
                        rotacaoLL(raiz);
                    }
                }
            }     
        }else{
            if ( valor > (*raiz)->info ){
                if (inserir(&((*raiz)->dir), valor) == 1){
                    if (abs(altura((*raiz)->esq) - altura((*raiz)->dir)) == 2){
                        if(valor > ((*raiz)->dir)->info){
                            rotacaoRR(raiz);
                        }else{
                            rotacaoLL(&((*raiz)->dir));
                            rotacaoRR(raiz);
                            // rotacaoRl(raiz);
                        }
                    }
                }
            }else
                insere = 0;
        }
    }
    return insere;
}

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

//----------------------Rubro-Negra-----------------------

typedef struct arvRN{
    int info;
    int vermelha;
    struct arvRN* esq;
    struct arvRN* dir;
}arvRN;

int cor(arvRN* no){
    return (no == NULL) ? 0 : no->vermelha;
}

arvRN *rotacionaRN(arvRN* no){
    arvRN* novo;
    novo = (arvRN*)malloc(sizeof(arvRN));
    novo = no->dir;
    no->dir = novo->esq;
    novo->esq = no;
    novo->vermelha = no->vermelha;
    no->vermelha = 1;
    return novo;
}

arvRN *rotacionaRRRN(arvRN* no){
    arvRN* novo;
    novo = (arvRN*)malloc(sizeof(arvRN));
    novo = no->esq;
    no->esq = novo->dir;
    novo->dir = no;
    novo->vermelha = no->vermelha;
    no->vermelha = 1;
    return novo;
}

arvRN *troca_cor(arvRN* no){
    no->vermelha = 1;
    no->esq->vermelha = 0;
    no->dir->vermelha = 0;
    return no;
}

arvRN *alocaNoRN(int valor){
    arvRN *no;
    no = (arvRN *)malloc(sizeof(arvRN));
    no->info = valor;
    no->esq = NULL;
    no->dir = NULL;
    no->vermelha = 1;
    return no;
}
arvRN* inseRN(arvRN* no, int valor){
    if(no == NULL){
        return alocaNoRN(valor);
    }

    if(valor < no->info)
        no->esq = inseRN(no->esq, valor);
    else
        no->dir = inseRN(no->dir, valor);


    if(cor(no->esq) == 0 && cor(no->dir) == 1)
        no = rotacionaRN(no);

    if(cor(no->esq) == 1 && cor(no->esq->esq) == 1)
        no = rotacionaRRRN(no);

    if(cor(no->esq) == 1 && cor(no->dir) == 1){
        no = troca_cor(no);
    }

    return no;
}

arvRN* inserirRN(arvRN** no, int valor){
    *no = inseRN(*no, valor);
    (*no)->vermelha = 0;
}

void imprimirRN(arvRN **no){
    if(*no){
        printf("(");
        printf("%d->", (*no)->info);
        if ((*no)->vermelha == 1){
            printf("v ");
        }else{
            printf("p ");
        }
        imprimirRN(&(*no)->esq);
        imprimirRN(&(*no)->dir);
        printf(")");
    }else{
        printf("()");
  }
}

arvRN *buscaRN (arvRN **r, int k) {
    if (*r == NULL || (*r)->info == k)
       return *r;
    if ((*r)->info > k)
       return buscaRN(&(*r)->esq, k);
    else
       return buscaRN(&(*r)->dir, k);
}

int numeroNosRN(arvRN *raiz){
	if(raiz == NULL ) return 0;
	return numeroNosRN(raiz->esq)+1+numeroNosRN(raiz->dir);
}

void profundidade_maiorRN(arvRN **raiz,arvRN **maior, int *nivel){
    int numeroNoDir = numeroNosRN((*raiz)->dir);
    int numeroNoEsq = numeroNosRN((*raiz)->esq);
    if(!((*raiz)->dir == NULL && (*raiz)->esq == NULL)){
        (*nivel)++;
        if(numeroNoDir > numeroNoEsq){
            (*maior) =  (*raiz)->dir;
            profundidade_maiorRN(&(*raiz)->dir, &(*maior), nivel);
        }else{
            (*maior) =  (*raiz)->esq;
            profundidade_maiorRN(&(*raiz)->esq, &(*maior), nivel);
        }
    }
}

void profundidade_menorRN(arvRN **raiz,arvRN **menor, int *nivel){
    int numeroNoDir = numeroNosRN((*raiz)->dir);
    int numeroNoEsq = numeroNosRN((*raiz)->esq);
    if( ((*raiz)->dir != NULL) && ((*raiz)->esq != NULL) ){
        (*nivel)++;
        if(numeroNoDir < numeroNoEsq){
            (*menor) =  (*raiz)->dir;
            profundidade_menorRN(&(*raiz)->dir, &(*menor), nivel);
        }else{
            (*menor) =  (*raiz)->esq;
            profundidade_menorRN(&(*raiz)->esq, &(*menor), nivel);
        }
    }else{
        if ((*raiz)->dir == NULL && (*raiz)->esq != NULL){
            profundidade_menorRN(&(*raiz)->esq, &(*menor), nivel);
        }else{
            if( (*raiz)->dir != NULL && (*raiz)->esq == NULL ){
                profundidade_menorRN(&(*raiz)->dir, &(*menor), nivel);
            }else{
                (*menor) = (*raiz);
            }
        }
    }
}

int main(){

    
    arvAVL *raizAvl, *aux;
    arvAVL *maior;
    
    arvRN *raizRN = malloc(sizeof(arvRN));
    arvRN *maiorRN,*auxRN;
    int nivel_menor = 0, nivel_maior;
    int nivel_menorRN = 0, nivel_maiorRN;
    srand(time(NULL));
    int *vetor;
    int *vetorRN;
    vetor = (int*) calloc(sizeof(int),1000);
    vetorRN = (int*) calloc(sizeof(int),1000);
    for (int i = 0; i < 30; i++){
        nivel_menor = 0;
        nivel_maior =  0;

        printf("+----------------------------+\n");
        printf("======= %d INTERAÇÃO =========\n", i+1);
        printf("+----------------------------+\n");
        
        maior = NULL;
        maiorRN = NULL;
        raizAvl = NULL;
        raizRN = NULL;
        int num[1000];
        for( int x=0;x<1000;x++)
            num[x] = gerarNumAleatorio();

        clock_t inicio = clock();
        for(int i = 0; i < 1000; i++){
            inserir(&raizAvl, num[i]); //inserindo na arvore avl
        }
        clock_t fim = clock();
        float segundos = (float)(fim - inicio) / CLOCKS_PER_SEC;
        printf("Inserido 1000 elementos na arvore AVL em %.4f segundos.\n", segundos);

        inicio = clock();
        for(int i = 0; i < 1000; i++){
            inserirRN(&raizRN, num[i]); //inserindo na arvore Rubro Negra
        }
        fim = clock();
        float segundosRN = (float)(fim - inicio) / CLOCKS_PER_SEC;
        printf("Inserido 1000 elementos na arvore Rubro-Negra em %.4f segundos.\n", segundosRN);

        if (segundos > segundosRN){
            printf("O tempo na AVL foi maior\n");
        }else{
            if (segundos < segundosRN)
                printf("O tempo na Rubro Negra foi maior\n");
            else
                printf("O tempo nas duas ávores foram iguais\n");
        }
        
        printf("\nArvore AVL\n");
        imprimir(&raizAvl);
        printf("\n");
        printf("\nArvore Rubro Negra\n");
        imprimirRN(&raizRN);
        printf("\n");

        profundidade_maior(&raizAvl, &maior, &nivel_maior);
        profundidade_menor(&raizAvl, &aux, &nivel_menor);
        printf("Maior Nível da AVL: %d\n", nivel_maior);
        printf("Menor Nível da AVl: %d\n", nivel_menor);

        profundidade_maiorRN(&raizRN, &maiorRN, &nivel_maiorRN);
        profundidade_menorRN(&raizRN, &auxRN, &nivel_menorRN);
        printf("Maior Nível da RN: %d\n", nivel_maiorRN);
        printf("Menor Nível da RN: %d\n", nivel_menorRN);

        inicio = clock();
        busca(&raizAvl, 30);
        fim = clock();
        segundos = (float)(fim - inicio) / CLOCKS_PER_SEC;
        printf("Busca do elemento 30 na AVL. Demorou em %f segundos.\n", segundos);
        int diferenca = nivel_maior-nivel_menor;
        vetor[diferenca]++;
        
        inicio = clock();
        buscaRN(&raizRN, 30);
        fim = clock();
        segundosRN = (float)(fim - inicio) / CLOCKS_PER_SEC;
        printf("Busca do elemento 30 na Rubro Negra. Demorou em %f segundos.\n", segundosRN);
        int diferencaRN = nivel_maiorRN-nivel_menorRN;
        vetorRN[diferencaRN]++;

    }
    for(int i=0; i<1000; i++){
        if( vetor[i] != 0 ){
            printf("A quantidade de vezes que a diferenca na AVL foi %d é %d\n",i,vetor[i]);
        }
    }

    for(int i=0; i<1000; i++){
        if( vetorRN[i] != 0 ){
            printf("A quantidade de vezes que a diferenca na Rubro Negra foi %d é %d\n",i,vetorRN[i]);
        }
    }
    return 0;
}
