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

// char *pegandoPalavra(char *string){
//     int tamanho = strlen(string), copia,a;
//     char *substring =(char*) malloc(sizeof(char)*100);
//     for(int i=0; i<tamanho; i++ ){
//         if( string[i] == ':' ){
//             for(a=i; string[a] != ' ' ;a-- );
//             // printf("Numero %d\n",a);
//             for(int x=a+1; x<=i ;x++ ){
//                 char strChar[1];
//                 strChar[0] = string[x];
//                 strcat(substring, strChar);
//                 // printf("2- %c\n", string[x]);
//             } 
//             break;
//         }
//     }
//     return substring;
// }

// char *pegandoPalavraFacil(char *string, char caracInicio, char caracFim){
//     int tamanho = strlen(string), copia=0;
//     char *substring = (char *)malloc(sizeof(char) * 100);
//     for(int i=0; i<tamanho; i++ ){
//         if (string[i] == caracInicio){
//             copia = 1;
//             continue;
//         }
//         if(string[i] == caracFim )
//             break;
//         if( copia == 1){
//             char strChar[1];
//             strChar[0] = string[i];
//             // printf("1- %c\n", string[i]);
//             strcat(substring, strChar);
//         }
//     }
//     return substring;
// }

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
        char *palavra, *p_equivalente;
        palavra = (char *) malloc(sizeof(char));
        p_equivalente = (char *) malloc(sizeof(char));
        while (linha[x] != ':'){
            palavra = realloc(palavra, qtd * sizeof(char));
            palavra[qtd-1] = linha[x];
            qtd++;
            x++;
        }
        palavra = realloc(palavra, qtd * sizeof(char));        
        palavra[qtd-1] = '\0';
        inserir(raiz, palavra);

        x++;
        qtd = 1;
        while(linha[x] != '\0'){
            p_equivalente = realloc(p_equivalente, qtd * sizeof(char));
            p_equivalente[qtd-1] = linha[x];
            if (linha[x] == ','){
                p_equivalente[qtd-1] = '\0';
                inserir_equivalente(raiz, palavra, p_equivalente);
                qtd = 0;           
            }   
            qtd++;
            x++;
        }
        p_equivalente[qtd-1] = '\0';
        inserir_equivalente(raiz, palavra, p_equivalente);
        
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
    imprimir(&raiz);
    printf("\n");
    fclose(arquivo);
    return 0;
}