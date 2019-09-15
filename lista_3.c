#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct arv{
    char estrutura[100];
    char palavra[100];
    char equivalentes[200];
    struct arv *dir,*esq;
};
typedef struct arv arv;

char *pegandoPalavra(char *string){
    int tamanho = strlen(string), copia,a;
    char *substring =(char*) malloc(sizeof(char)*100);
    for(int i=0; i<tamanho; i++ ){
        if( string[i] == ':' ){
            for(a=i; string[a] != ' ' ;a-- );
            // printf("Numero %d\n",a);
            for(int x=a+1; x<=i ;x++ ){
                char strChar[1];
                strChar[0] = string[x];
                strcat(substring, strChar);
                // printf("2- %c\n", string[x]);
            } 
            break;
        }
    }
    return substring;
}

char *pegandoPalavraFacil(char *string, char caracInicio, char caracFim){
    int tamanho = strlen(string), copia=0;
    char *substring = (char *)malloc(sizeof(char) * 100);
    for(int i=0; i<tamanho; i++ ){
        if (string[i] == caracInicio){
            copia = 1;
            continue;
        }
        if(string[i] == caracFim )
            break;
        if( copia == 1){
            char strChar[1];
            strChar[0] = string[i];
            // printf("1- %c\n", string[i]);
            strcat(substring, strChar);
        }
    }
    return substring;
}

arv *alocaNo(char *string){
    // printf("%s",string);
    arv *aux;
    aux =(arv*) malloc(sizeof(arv));
    strcpy(aux->estrutura, pegandoPalavraFacil(string,'%',' '));
    strcpy(aux->palavra, pegandoPalavra(string));
    strcpy(aux->equivalentes, pegandoPalavraFacil(string, ':', '\n'));
    aux->dir = NULL;
    aux->esq = NULL;
    return aux;
}


void inserir(arv **raiz, arv **no){
    if( *raiz == NULL){
        *raiz = *no;
    }else{
        if (strcmp((*no)->palavra, (*raiz)->palavra) == -1) //se menor
        {
            inserir(&(*raiz)->esq, no);
        }else{
            if (strcmp((*no)->palavra, (*raiz)->palavra) == 1)//se maior, se igual a 0 é pq é igual e não pode ter palavra igual
                inserir(&(*raiz)->dir, no);
        }
    }
}

void imprimir(arv **raiz){
    if(*raiz){
        printf("(");
        printf("%s ", (*raiz)->estrutura);
        printf("%s ", (*raiz)->palavra);
        printf("%s ", (*raiz)->equivalentes);
        imprimir(&(*raiz)->esq);
        imprimir(&(*raiz)->dir);
        printf(")");
    }else{
        printf("()");
    }
}

int main(){
    char gerandoUmaEntrada[] = {"%basico indice:index"} ;
    // printf("%s",gerandoUmaEntrada);
    // char gerandoUmaEntrada[] = {"%Basico:encontrar:find"} 
    // alocaNo(gerandoUmaEntrada);
    arv *no = alocaNo(gerandoUmaEntrada);
    arv *raiz = NULL;
    inserir(&raiz,&no);
    imprimir(&raiz);
    return 0;
}