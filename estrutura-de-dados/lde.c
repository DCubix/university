#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct no_t {
	int val;
	struct no_t *antr;
	struct no_t *prox;
} NO;

NO* cria_no(int val) {
	NO* no = (NO*) malloc(sizeof(NO));
	no->val = val;
	no->antr = NULL;
	no->prox = NULL;
	return no;
}

typedef struct listade_t {
	NO *inicio;
	NO *fim;
	int tamanho;
} LISTADE;

LISTADE* cria_listade() {
	LISTADE* lst = (LISTADE*) malloc(sizeof(LISTADE));
	lst->inicio = lst->fim = NULL;
	lst->tamanho = 0;
	return lst;
}

bool listade_vazia(LISTADE* lst) {
	return lst->tamanho == 0;
}

void insere_listade_inicio(LISTADE* lst, int val) {
	NO* no = cria_no(val);
	if (listade_vazia(lst)) {
		lst->fim = no;
	} else {
		lst->inicio->antr = no;
	}
	no->prox = lst->inicio;
	lst->inicio = no;
	lst->tamanho++;
}

void insere_listade_fim(LISTADE* lst, int val) {
	NO* no = cria_no(val);
	if (listade_vazia(lst)) {
		lst->inicio = lst->fim = no;
	} else {
		lst->fim->prox = no;
		no->antr = lst->fim;
	}
	lst->fim = no;
	lst->tamanho++;
}

void remove_listade(LISTADE* lst, int val) {
	if (listade_vazia(lst)) return;
	NO *tmp = lst->inicio;
	while (tmp != NULL && tmp->val != val) {
		tmp = tmp->prox;
	}

	// Atingiu o fim da lista sem encontrar nenhum valor
	if (tmp == NULL) return;
	if (tmp->val != val) return;

	if (tmp->antr == NULL) { // Inicio
		NO* temp = lst->inicio;
		lst->inicio = lst->inicio->prox;
		free(temp);
		lst->tamanho--;
		return;
	} else if (tmp->prox == NULL) { // Fim
		NO* temp = lst->fim;
		lst->fim = lst->fim->antr;
		free(temp);
		lst->tamanho--;
		return;
	} else {
		NO* ant = tmp->antr;
		NO* prx = tmp->prox;
		ant->prox = prx;
		prx->antr = ant;
		free(tmp);
		lst->tamanho--;
	}
}

bool busca_listade(LISTADE* lst, int val) {
	if (listade_vazia(lst)) return false;
	NO* inicio = lst->inicio;
	NO* fim = lst->fim;

	int i = 0;
	while (inicio != NULL || fim != NULL) {
		if (inicio && inicio->val == val) return true;
		if (fim && fim->val == val) return true;

		inicio = inicio->prox;
		fim = fim->antr;
		if ((i+=2) >= lst->tamanho) break;
	}
	return false;
}

void imprime_listade(LISTADE* lst) {
	printf("[");
	NO* tmp = lst->inicio;
	while (tmp != NULL) {
		if (tmp->prox == NULL) printf("%d", tmp->val);
		else				   printf("%d, ", tmp->val);
		tmp = tmp->prox;
	}
	printf("]\n");
}

int main(int argc, char** argv) {
	LISTADE *lst = cria_listade();
	printf("=== Inserção:\n");
	for (int i = 0; i < 100; i++) {
		insere_listade_fim(lst, rand() % 100);
	}

	imprime_listade(lst);

	printf("=== Busca:\n\t");

	printf("Valor a ser buscado: ");
	int b = 0;
	scanf("%d", &b);

	if (busca_listade(lst, b)) {
		printf("Valor %d encontrado!\n", b);
	} else {
		printf("Valor %d não encontrado!\n", b);
	}

	printf("=== Remoção:\n");

	for (int i = 0; i < 20; i++) {
		remove_listade(lst, rand() % 100);
	}

	imprime_listade(lst);

	return 0;
}