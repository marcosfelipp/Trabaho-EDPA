#include <stdio.h>
#include <stdlib.h>
#include <string>

using std::string;

typedef struct no {
	char chave;
	struct no *esquerda;
	struct no *direita;
} celula;

typedef celula *arvore;


typedef struct fila_no{
	celula *ref_no;
	struct fila_no *prox;
} fila;

typedef fila *queue;

int posicao = 0;
int ultimo_nivel = 1;

// ############## FUNÇÕES FILA ##############

queue cria_fila(){
	queue q;
	q = (queue) malloc(sizeof(fila));
	q->ref_no = NULL;
	q->prox = NULL;
	return q;
}

queue insere_fila(queue final, arvore no){
	queue q;
	q = (queue) malloc(sizeof(fila));
	q->ref_no = no;
	final->prox = q;
	return q;
}

queue remove_fila(queue inicio){
	queue novo_inicio = inicio->prox;
	free(inicio);
	return novo_inicio;
}

// ############## FUNÇÕES ARVORE ##############

arvore constroi_arvore(char chave){
	arvore r;
	r = (arvore) malloc(sizeof(celula));
	r->direita = NULL;
	r->esquerda = NULL;
	r->chave = chave;
	return r;
}

arvore cria_filho(arvore r, char x, int direita_esquerda){
	arvore f;
	f = (arvore) malloc(sizeof(celula));
	f->chave = x;
	f->esquerda = NULL;
	f->direita = NULL;
	if(direita_esquerda == 0){
		r->esquerda = f;
	}else{
		r->direita = f;
	}
	return f;
}

void cria_filho_recursivo(arvore r, int level){
	if(level > 0){
		arvore left = cria_filho(r, 'a', 0);
		cria_filho_recursivo(left, level-1);
		arvore right = cria_filho(r, 'b', 1);
		cria_filho_recursivo(right, level-1);
	}
}

int insere_recursivo(arvore r, string palavra){	
	if(r->esquerda != NULL) insere_recursivo(r->esquerda, palavra);
	r->chave = palavra[posicao];
	posicao +=1;
	if(r->direita != NULL) insere_recursivo(r->direita, palavra);
}


arvore busca_no_recursivo(arvore r, char x){
	arvore prof = NULL; 	
	if(r->chave == x) return r;
	else{
		if(r->esquerda != NULL) prof = busca_no_recursivo(r->esquerda, x); 	
		if(r->direita != NULL) prof = busca_no_recursivo(r->direita , x);
		return prof;
	}
}


// ############## FUNÇÕES PERCURSOS ##############

int percurso_largura(arvore r){	
	queue inicio = cria_fila();
	queue final = cria_fila();
	inicio = final;
	
	final = insere_fila(final, r);

	while(inicio->prox != NULL){
		printf("%c",inicio->prox->ref_no->chave);
		
		if(inicio->prox->ref_no->esquerda != NULL) final = insere_fila(final, inicio->prox->ref_no->esquerda);
		if(inicio->prox->ref_no->direita != NULL) final = insere_fila(final, inicio->prox->ref_no->direita);
		inicio = remove_fila(inicio);
	}
}


int percurso_profundidade(arvore r){	
	if(r->esquerda != NULL) percurso_profundidade(r->esquerda);
	printf("%c",r->chave);
	if(r->direita != NULL) percurso_profundidade(r->direita);
}


int main(){
	arvore r = constroi_arvore('u');
	string entrada = ("ot mseiUmxp lte");

	cria_filho_recursivo(r, 4);
	insere_recursivo(r, entrada);
	// percurso_profundidade(r);
	percurso_largura(r);
	printf("\n");

}
