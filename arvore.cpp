#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <math.h> 

using std::string;
using namespace std;

// ############## DATA STRUCTURES ##############

typedef struct no {
	char key;
	struct no *left;
	struct no *right;
} cell;

typedef cell *arvore;


typedef struct fila_no{
	cell *ref_no;
	struct fila_no *prox;
} fila;

typedef fila *queue;

// ############## GLOBAL VARIABLES ##############

int string_input_position = 0;
int last_level_tree = 0;

// ############## QUEUE FUNCTIONS ##############

queue create_queue(){
	queue q;
	q = (queue) malloc(sizeof(fila));
	q->ref_no = NULL;
	q->prox = NULL;
	return q;
}

queue insert_queue(queue final, arvore no){
	queue q;
	q = (queue) malloc(sizeof(fila));
	q->ref_no = no;
	q->prox = NULL;
	final->prox = q;
	return q;
}

queue remove_queue(queue inicio){
	queue novo_inicio = inicio->prox;
	free(inicio);
	return novo_inicio;
}

// ############## TREE FUNCTIONS ##############

arvore create_tree(){
	arvore r;
	r = (arvore) malloc(sizeof(cell));
	r->right = NULL;
	r->left = NULL;
	r->key = ' ';
	return r;
}

arvore create_children(arvore r, char x, int right_left){
	arvore f;
	f = (arvore) malloc(sizeof(cell));
	f->key = x;
	f->left = NULL;
	f->right = NULL;
	if(right_left == 0){
		r->left = f;
	}else{
		r->right = f;
	}
	return f;
}

void create_children_recursive(arvore r, int level){
	if(level > 0){
		if(level == 1){
			if(last_level_tree == 1){
					arvore left = create_children(r, 'a', 0);
					last_level_tree-=1;
				}
			else{
				if(last_level_tree > 1){
					arvore left = create_children(r, 'a', 0);
					arvore right = create_children(r, 'b', 1);
					last_level_tree-=2;
				}	
			}
		}else{
			arvore left = create_children(r, 'a', 0);
			create_children_recursive(left, level-1);
			arvore right = create_children(r, 'b', 1);
			create_children_recursive(right, level-1);
		}
	}
}

int recursive_insert(arvore r, string palavra){	
	if(r->left != NULL) recursive_insert(r->left, palavra);
	r->key = palavra[string_input_position];
	string_input_position +=1;
	if(r->right != NULL) recursive_insert(r->right, palavra);
}


int free_nodes(arvore r){	
	if(r->left != NULL) free_nodes(r->left);
	if(r->right != NULL) free_nodes(r->right);
	free(r);
}

// ############## SEARCH FUNCTION ##############

int breadth_first_search(arvore r){	
	queue inicio = create_queue();
	queue final = create_queue();
	inicio = final;
	
	final = insert_queue(final, r);

	while(inicio->prox->ref_no != NULL){
		printf("%c",inicio->prox->ref_no->key);
		if(inicio->prox->ref_no->left != NULL) final = insert_queue(final, inicio->prox->ref_no->left);
		if(inicio->prox->ref_no->right != NULL) final = insert_queue(final, inicio->prox->ref_no->right);
		inicio = remove_queue(inicio);
		if(inicio->prox == NULL){
			break;
		}
	}
}


int main(){
	int N;
	string str_input;
	scanf("%d",&N);

	while(N > 0){
		string_input_position = 0;
		float tree_levels = log2(float(N));
		last_level_tree = int(N - pow(2, int(tree_levels)) + 1);

		cin.ignore(256, '\n'); 
		std::getline(std::cin,str_input);
		
		arvore root = create_tree();
		create_children_recursive(root, int(tree_levels));
		recursive_insert(root, str_input);

		breadth_first_search(root);
		printf("\n");
		free_nodes(root);
		scanf("%d",&N);
	}
}
