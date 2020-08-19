#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <math.h> 


using std::string;
using namespace std;

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
int ultimo_nivel = 0;

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
	q->prox = NULL;
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
		if(level == 1){
			if(ultimo_nivel == 1){
					arvore left = cria_filho(r, 'a', 0);
					ultimo_nivel-=1;
				}
			else{
				if(ultimo_nivel > 1){
					arvore left = cria_filho(r, 'a', 0);
					arvore right = cria_filho(r, 'b', 1);
					ultimo_nivel-=2;
				}	
			}
		}else{
			arvore left = cria_filho(r, 'a', 0);
			cria_filho_recursivo(left, level-1);
			arvore right = cria_filho(r, 'b', 1);
			cria_filho_recursivo(right, level-1);
		}
	}
}

int insere_recursivo(arvore r, string palavra){	
	if(r->esquerda != NULL) insere_recursivo(r->esquerda, palavra);
	r->chave = palavra[posicao];
	posicao +=1;
	if(r->direita != NULL) insere_recursivo(r->direita, palavra);
}


int free_nodes(arvore r){	
	if(r->esquerda != NULL) free_nodes(r->esquerda);
	if(r->direita != NULL) free_nodes(r->direita);
	free(r);
}

// ############## FUNÇÕES PERCURSOS ##############

int percurso_largura(arvore r){	
	queue inicio = cria_fila();
	queue final = cria_fila();
	inicio = final;
	
	final = insere_fila(final, r);

	while(inicio->prox->ref_no != NULL){
		printf("%c",inicio->prox->ref_no->chave);
		if(inicio->prox->ref_no->esquerda != NULL) final = insere_fila(final, inicio->prox->ref_no->esquerda);
		if(inicio->prox->ref_no->direita != NULL) final = insere_fila(final, inicio->prox->ref_no->direita);
		inicio = remove_fila(inicio);
		if(inicio->prox == NULL){
			break;
		}
	}
}


int main(){
	int N;
	string entrada;

	scanf("%d",&N);

	while(N > 0){
		posicao = 0;
		float niveis = log2(float(N));
		ultimo_nivel = int(N - pow(2, int(niveis)) + 1);

		cin.ignore(256, '\n'); 
		std::getline(std::cin,entrada);
		
		arvore r = constroi_arvore('u');
		cria_filho_recursivo(r, int(niveis));
		insere_recursivo(r, entrada);

		percurso_largura(r);
		printf("\n");
		free_nodes(r);
		scanf("%d",&N);
	}

	
}
