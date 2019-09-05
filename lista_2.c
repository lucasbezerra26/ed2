#include<stdio.h> 
#include<stdlib.h> 

struct arvAVL{ 
	int info; 
	struct arvAVL *esq; 
	struct arvAVL *dir; 
	int altura; 
}; 

typedef struct arvAVL arvAVL;

// Função utilizada para pegar o valor máximo entre os dois inteiros 
int max(int a, int b); 


void imprimir(arvAVL **raiz);


// Pega a altura da árvore
int altura(arvAVL *raiz){ 
	if (raiz == NULL) 
		return 0; 
	return raiz->altura; 
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

// rotação LR 
void rotacaoLR(arvAVL **no) { 
	rotacaoRR(&(*no));
	rotacaoLL(&(*no));
}

// rotação LR 
void rotacaoRL(arvAVL **no) { 
	rotacaoLL(&(*no));
	rotacaoRR(&(*no));
}

// fator de balanceamento 
int fatorBalanceamento(arvAVL *raiz){ 
	if (raiz == NULL) 
		return 0; 
	return altura(raiz->esq) - altura(raiz->dir); 
}

// Insere na árvore e já faz o balaceamento, caso necessario;
void inserir(arvAVL **raiz, int valor){ 
	if (*raiz == NULL) 
		*raiz = alocaNo(valor); 

	if (valor < (*raiz)->info) 
		inserir(&(*raiz)->esq, valor);

	else if (valor > (*raiz)->info) 
		inserir(&(*raiz)->dir, valor); 

	(*raiz)->altura = 1 + max(altura((*raiz)->esq), altura((*raiz)->dir)); 

	int fb = abs(fatorBalanceamento((*raiz)->esq) - fatorBalanceamento((*raiz)->dir));

	if (fb == 2){	
		if ((*raiz)->esq && valor <= (*raiz)->esq->info){
			if((*raiz)->esq->esq)
				rotacaoLL(&(*raiz)); 
			else{
				rotacaoRR(&(*raiz)->esq); 
				rotacaoLL(&(*raiz));
			}
		}
		else{
			if((*raiz)->dir->dir)
				rotacaoRR(&(*raiz)); 
			else{
				rotacaoLL(&(*raiz)->dir); 
				rotacaoRR(&(*raiz));
			}
		}

		// if ((*raiz)->esq->info) { 
		// 	rotacaoLL(&((*raiz)->esq)); 
		// 	rotacaoRR(&(*raiz)); 
		// } 

		// if (valor < (*raiz)->dir->info) { 
		// 	rotacaoRR(&((*raiz)->dir)); 
		// 	rotacaoLL(&(*raiz)); 
		// }
	}

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

int main(){ 
  arvAVL *root = NULL; 

  inserir(&root, 10); 
  inserir(&root, 20); 
  inserir(&root, 30); 
  inserir(&root, 40); 
  inserir(&root, 50); 
  inserir(&root, 25); 

  imprimir(&root);
  printf("\n");

  return 0; 
} 
