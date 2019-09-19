#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node{
    int info;
    int isRed;
    struct node* left;
    struct node* right;
} node;

#define PRETO 0
#define VERMELHO 1


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

node* rotacionaEsquerdaM(node **no){
    node* novo;
    novo = (node*)malloc(sizeof(node));

    novo = (*no)->right;
    (*no)->right = novo->left;
    novo->left = (*no);
    novo->isRed = (*no)->isRed;
    (*no)->isRed = 1;
    *no = novo;
    // return novo;
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

node* rotacionaDireitaM(node **no){
    node* novo;
    novo = (node*)malloc(sizeof(node));

    novo = (*no)->left;
    (*no)->left = novo->right;
    novo->right = (*no);
    novo->isRed = (*no)->isRed;
    (*no)->isRed = 1;
    *no = novo;
    // return novo;
}

node* troca_cor(node* no){
    no->isRed = 1;
    no->left->isRed = 0;
    no->right->isRed = 0;
    return no;
}

node* troca_corM(node **no){
    (*no)->isRed = 1;
    (*no)->left->isRed = 0;
    (*no)->right->isRed = 0;
    // return no;
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

node *minhaInsercao(node *raiz, int valor){

    void insercao(node **no, int valor1){

        if(*no == NULL){
            // printf("Entrou");
            node *novo;
            novo = (node*)malloc(sizeof(node));
            *no = (node*)malloc(sizeof(node));
            novo->info = valor1;
            novo->left = NULL;
            novo->right = NULL;
            novo->isRed = 1;
            (*no)->info = valor1;
            (*no)->left = NULL;
            (*no)->right = NULL;
            (*no)->isRed = 1;
            // *no = novo;
            // return novo;
        }
        // printf("MErda %d", (*no)->info);
        if(valor1 < (*no)->info)
            insercao(&(*no)->left, valor1);
        else
            insercao(&(*no)->right, valor1);


        if(cor((*no)->left) == 0 && cor((*no)->right) == 1)
            rotacionaEsquerdaM(&(*no));

        if(cor((*no)->left) == 1 && cor((*no)->left->left) == 1)
            rotacionaDireitaM(&(*no));

        if(cor((*no)->left) == 1 && cor((*no)->right) == 1){
            troca_corM(&(*no));
        }
        // return no;
    }

    insercao(&raiz, valor);
    raiz->isRed = 0;
    return raiz;

}

    void mostra_arvore(node **no)
{
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
    node *raiz, *aux;
    node *raiz1;
    node *maior;
    int nivel_menor = 0, nivel_maior;
    srand(time(NULL));
    int *vetor;
    vetor = (int*) calloc(sizeof(int),1000);
    for (int i = 0; i < 1; i++){
        nivel_menor = 0;
        nivel_maior =  0;

        printf("+----------------------------+\n");
        printf("======= %d INTERAÇÃO =========\n", i+1);
        printf("+----------------------------+\n");
        
        raiz = NULL;
        raiz1 = NULL;
        // maior = NULL;
        clock_t inicio = clock();

        // int vet[] = {20, 10, 30, 40, 15 /*, 35, 50, 25, 9, 5, 13, 21, 22*/};
        int vet[] = {20, 10, 30, 40, 15, 35, 50, 25, 9, 5, 13, 21, 22};
        for (i = 0; i < 5; i++){
            raiz = insert(raiz, vet[i]);
            raiz1 = minhaInsercao(raiz1, vet[i]);
        }
        mostra_arvore(&raiz);
        printf("\n");
        mostra_arvore(&raiz1);

        // for(int i = 0; i < 1000; i++){
        //     int num = gerarNumAleatorio();
        //     // printf("Ei");
        //     insertLLRN(&raiz, num);
        // }
        // clock_t fim = clock();
        // float segundos = (float)(fim - inicio) / CLOCKS_PER_SEC;
        // printf("Inserido 1000 elementos em %.4f segundos.\n", segundos);
        // // imprimir(&raiz);
        // printf("\n");

        // // profundidade_maior(&raiz, &maior, &nivel_maior);
        // printf("Maior Nível: %d\n", nivel_maior);

        // // profundidade_menor(&raiz, &aux, &nivel_menor);
        // printf("Menor Nível: %d\n", nivel_menor);
        // // printf("Num: %d \n", num);

        // inicio = clock();
        // // busca(&raiz, 30);
        // fim = clock();
        // segundos = (float)(fim - inicio) / CLOCKS_PER_SEC;
        // printf("Busca do elemento 30. Demorou em %.4f segundos.\n", segundos);
        // int difrenca = nivel_maior-nivel_menor;
        // vetor[difrenca]++;
    }
    // for(int i=0; i<1000; i++){
    //     if( vetor[i] != 0 ){
    //         printf("A quantidade de vezes que a diferenca foi %d é %d\n",i,vetor[i]);
    //     }
    // }
    return 0;
}