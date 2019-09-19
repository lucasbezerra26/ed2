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

// Aloca um novo nó, adiciona o valor a ele e inicializa os ponteiros da esquerda 
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

typedef struct node{
    int info;
    int isRed;
    struct node* left;
    struct node* right;
} node;

// typedef struct ocorrencia{
//     int num, casos;
//     struct ocorrencia *prox;
// }ocorrencia;

int cor(node* no){
    return (no == NULL) ? 0 : no->isRed;
}

node* rotacionaEsquerda(node* no){
    node* novo;
    novo = (node*)malloc(sizeof(node));

    novo = no->right;
    no->right = novo->left;
    novo->left = no;
    novo->isRed = no->isRed;
    no->isRed = 1;
    return novo;
}

node* rotacionaDireita(node* no){
    node* novo;
    novo = (node*)malloc(sizeof(node));

    novo = no->left;
    no->left = novo->right;
    novo->right = no;
    novo->isRed = no->isRed;
    no->isRed = 1;
    return novo;
}

node* troca_cor(node* no){
    no->isRed = 1;
    no->left->isRed = 0;
    no->right->isRed = 0;
    return no;
}


node* insertLLRN(node* no, int valor){
    node* novo;

    if(no == NULL){
        novo = (node*)malloc(sizeof(node));
        novo->info = valor;
        novo->left = NULL;
        novo->right = NULL;
        novo->isRed = 1;
        return novo;
    }

    if(valor < no->info)
        no->left = insertLLRN(no->left, valor);
    else
        no->right = insertLLRN(no->right, valor);


    if(cor(no->left) == 0 && cor(no->right) == 1)
        no = rotacionaEsquerda(no);

    if(cor(no->left) == 1 && cor(no->left->left) == 1)
        no = rotacionaDireita(no);

    if(cor(no->left) == 1 && cor(no->right) == 1){
        no = troca_cor(no);
    }

    return no;
}

node* insert(node* no, int valor){
    no = insertLLRN(no, valor);
    no->isRed = 0;
    return no;
}

void mostra_arvore(node **no){
    if(*no){
        printf("(");
        printf("%d->%c ", (*no)->info, ((*no)->isRed == 1) ? 'V' : 'P');
        mostra_arvore(&(*no)->left);
        mostra_arvore(&(*no)->right);
        printf(")");
    }else{
        printf("()");
  }
}


int main(){
    arvAVL *raizAvl, *aux;
    arvAVL *maior;
    
    node *raizRB = malloc(sizeof(node));

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
        
        raizAvl = NULL;
        // maior = NULL;
        clock_t inicio = clock();

        for(int i = 0; i < 1000; i++){
            int num = gerarNumAleatorio();
            inserir(&raizAvl, num);
            raizRB = insert(raizRB, num);
        }
        clock_t fim = clock();
        float segundos = (float)(fim - inicio) / CLOCKS_PER_SEC;
        printf("Inserido 1000 elementos em %.4f segundos.\n", segundos);
        imprimir(&raizAvl);
        mostra_arvore(&raizRB);
        printf("\n");

        profundidade_maior(&raizAvl, &maior, &nivel_maior);
        printf("Maior Nível: %d\n", nivel_maior);

        profundidade_menor(&raizAvl, &aux, &nivel_menor);
        printf("Menor Nível: %d\n", nivel_menor);
        // printf("Num: %d \n", num);

        inicio = clock();
        busca(&raizAvl, 30);
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
