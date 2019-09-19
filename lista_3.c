#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// Cada unidade eh uma estrutura
// Cada equivalente faz parte de uma lista encadeada simples

// Estrutura para as palavras equivalentes
struct equivalente{
    char nome[100];
    struct equivalente *prox;
};

typedef struct equivalente equivalente;

// Estrutura para as unidades
struct unidade{
    char palavra[100];
    char nome_unidade[100];
    equivalente *equivalentes;
    int qtd_equivalentes;
    struct unidade *dir,*esq;
};

typedef struct unidade unidade;

unidade *alocaNo(){
    unidade *aux;
    aux =(unidade*) malloc(sizeof(unidade));
    aux->equivalentes = (equivalente *) malloc(sizeof(equivalente));
    aux->qtd_equivalentes = 0;
    aux->dir = NULL;
    aux->esq = NULL;
    return aux;
}

unidade *retorna_no(unidade **raiz, char *palavra){
    unidade *aux;
    if(*raiz == NULL){
        aux = NULL;
    }else{
        if(strcmp(palavra, (*raiz)->palavra) == 0){
            aux = *raiz;
        }else if(strcmp(palavra, (*raiz)->palavra) < 0){
            aux = retorna_no(&(*raiz)->esq, palavra);
        }else{
            aux = retorna_no(&(*raiz)->dir, palavra);
        }
    }
    return aux;
}


void inserir(unidade **raiz, char *palavra){
    if(*raiz == NULL){
        *raiz = alocaNo();
        strcpy((*raiz)->palavra, palavra);
    }else{
        // Se a palavra for menor que a atual
        if (strcmp(palavra, (*raiz)->palavra) < 0){
            inserir(&(*raiz)->esq, palavra);
        }else{
            //se a palavra que vou inserir é maior que a que está na árvore
            if (strcmp(palavra, (*raiz)->palavra) > 0){
                inserir(&(*raiz)->dir, palavra);
            }
        }
    }
}

void inserir_equivalente(unidade **raiz, char *palavra, char *p_equivalente){
    unidade *no_encontrado = retorna_no(raiz, palavra);
    if (no_encontrado != NULL){
        if(no_encontrado->qtd_equivalentes == 0){
            equivalente *eq = (equivalente *) malloc(sizeof(equivalente));
            strcpy(eq->nome, p_equivalente);
            eq->prox = NULL;
            no_encontrado->equivalentes = eq;
            no_encontrado->qtd_equivalentes = no_encontrado->qtd_equivalentes + 1;
        }else{
            equivalente *aux = no_encontrado->equivalentes; 
            while(aux->prox != NULL){
                aux = aux->prox;
            }
            equivalente *eq = (equivalente *) malloc(sizeof(equivalente));
            strcpy(eq->nome, p_equivalente);
            eq->prox = NULL;
            aux->prox = eq;
            no_encontrado->qtd_equivalentes = no_encontrado->qtd_equivalentes + 1;
        }
    }
}

void imprimir_equivalentes(equivalente *eq){
    printf("[");
    while (eq != NULL){
        if(eq->prox == NULL){
            printf("%s", eq->nome);
        }else{
            printf("%s, ", eq->nome);
        }
        eq = eq->prox;
    }
    printf("]");
}

void imprimir(unidade **raiz){
    if(*raiz){
        printf("(");
        printf("%s ", (*raiz)->palavra);
        imprimir_equivalentes((*raiz)->equivalentes);
        imprimir(&(*raiz)->esq);
        imprimir(&(*raiz)->dir);
        printf(")");
    }else{
        printf("()");
    }
}

void grava_dados(char linha[], unidade **raiz){
    int x = 0;
    if(linha[0] == '%'){
        x++;
        char *nome_unidade;
        nome_unidade = (char *) malloc(sizeof(char));
        while (linha[x] != '\0'){
            nome_unidade = realloc(nome_unidade, x * sizeof(char));
            nome_unidade[x-1] = linha[x];
            x++;
        }
        nome_unidade = realloc(nome_unidade, x * sizeof(char));
        nome_unidade[x-1] = '\0';

        strcpy((*raiz)->nome_unidade, nome_unidade);
        strcpy((*raiz)->palavra, nome_unidade);

    }else{
        int qtd = 1;
        char *palavra_ingles, *palavra_portugues;
        palavra_ingles = (char *) malloc(sizeof(char));
        palavra_portugues = (char *) malloc(sizeof(char));
        while (linha[x] != ':'){
            palavra_ingles = realloc(palavra_ingles, qtd * sizeof(char));
            palavra_ingles[qtd-1] = linha[x];
            qtd++;
            x++;
        }
        palavra_ingles = realloc(palavra_ingles, qtd * sizeof(char));        
        palavra_ingles[qtd-1] = '\0';

        x++;
        qtd = 1;
        while(linha[x] != '\0'){
            palavra_portugues = realloc(palavra_portugues, qtd * sizeof(char));
            palavra_portugues[qtd-1] = linha[x];
            if (linha[x] == ','){
                palavra_portugues[qtd-1] = '\0';
                inserir(raiz, palavra_portugues);
                inserir_equivalente(raiz, palavra_portugues, palavra_ingles);
                qtd = 0;           
            }   
            qtd++;
            x++;
        }
        palavra_portugues[qtd-1] = '\0';
        inserir(raiz, palavra_portugues);
        inserir_equivalente(raiz, palavra_portugues, palavra_ingles);

    }
}

void imprime_busca(unidade **raiz, char *busca){
    if(*raiz != NULL){
        if((*raiz)->qtd_equivalentes > 0){
            equivalente *aux = (*raiz)->equivalentes;
            while(aux != NULL){
                if(strcmp(aux->nome, busca) == 0){
                    printf("Palavra %s equivalência em português: %s\n", busca, (*raiz)->palavra);
                }
                aux = aux->prox;
            }
        }
        imprime_busca(&(*raiz)->esq, busca);
        imprime_busca(&(*raiz)->dir, busca);
    }
}

void remove_equivalentes(equivalente *eqs){
    if(eqs != NULL){
        if(eqs->prox == NULL){
            free(eqs);
        }else{
            remove_equivalentes(eqs->prox);
            free(eqs);
        }
    }
}

void remover(unidade **raiz, char *palavra, unidade **pai){
    if(*raiz != NULL){
        if (strcmp((*raiz)->palavra, palavra) == 0){
            printf("te achei\n");
            if((*raiz)->esq == NULL && (*raiz)->dir == NULL){
                remove_equivalentes((*raiz)->equivalentes);
                free(*raiz);
                *raiz = NULL;
            }else if((*raiz)->esq == NULL && (*pai) != NULL){
                unidade *aux = (*raiz);
                remove_equivalentes((*raiz)->equivalentes);
                (*raiz) = (*raiz)->dir;
                free(aux);
            }else if((*raiz)->dir == NULL && (*pai) != NULL){
                unidade *aux = (*raiz);
                remove_equivalentes((*raiz)->equivalentes);
                (*raiz) = (*raiz)->esq;
                free(aux);
            }else if((*raiz)->esq == NULL){
                unidade *aux = *raiz;
                (*raiz) = (*raiz)->dir;
                remove_equivalentes(aux->equivalentes);
                free(aux);
            }else{
                unidade *aux = *raiz;
                (*raiz) = (*raiz)->esq;
                remove_equivalentes(aux->equivalentes);
                free(aux);
            }
        }else{
            if(strcmp(palavra, (*raiz)->palavra) > 0){
                remover(&(*raiz)->dir, palavra, raiz);
            }else{
                remover(&(*raiz)->esq, palavra, raiz);
            }
        }
    }
}


int main(){
    FILE *arquivo;
    arquivo = fopen("lista_3.txt", "r");
    unidade *raiz;
    raiz = alocaNo();
    if(arquivo != NULL){
        while (!feof(arquivo)){
            char string[255];
            fscanf(arquivo, "%s", string);
            grava_dados(string, &raiz);
        }
    }
    fclose(arquivo);
    printf("Imprimindo a árvore:\n");
    printf("-------------------------\n");
    imprimir(&raiz);
    printf("\n");
    printf("-------------------------\n");

    char palavra[100];
    // printf("Pesquise por a palavra em inglês: ");
    // scanf(" %s", palavra);
    // imprime_busca(&raiz, palavra);

    // printf("--------------\n");

    printf("Pesquise por a palavra que deseja remover: ");
    scanf(" %s", palavra);
    remover(&raiz, palavra, NULL);


    printf("Imprimindo a árvore:\n");
    printf("-------------------------\n");
    imprimir(&raiz);
    printf("\n");
    printf("-------------------------\n");

    free(raiz);

    return 0;
}