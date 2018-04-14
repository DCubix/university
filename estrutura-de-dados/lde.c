#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <time.h>

/**
Funções para medição do tempo de execução de um bloco de código
Uso:
CRON_BEGIN()

... operações ...

CRON_END()
*/
#define CRON_BEGIN() { clock_t __b, __e; double __t; __b = clock()
#define CRON_END()  __e = clock(); __t = (double)(__e - __b) / CLOCKS_PER_SEC; \
printf("Tempo Decorrido: %.6f segundos\n", __t); }

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
	no->prox = lst->inicio;

	if (lst->inicio != NULL) lst->inicio->antr = no;

	lst->inicio = no;
	if (lst->fim == NULL) {
		lst->fim = lst->inicio;
	}
	lst->tamanho++;
}

void insere_listade_fim(LISTADE* lst, int val) {
	if (listade_vazia(lst)) {
		insere_listade_inicio(lst, val);
		return;
	}

	NO* no = cria_no(val);
	no->antr = lst->fim;
	lst->fim->prox = no;
	lst->fim = no;

	lst->tamanho++;
}

void insere_ordenado_listade(LISTADE* lst, int val) {
	if (listade_vazia(lst)) {
		insere_listade_fim(lst, val);
	} else if (val < lst->inicio->val) {
	    NO* no = cria_no(val);
	    no->prox = lst->inicio;
	    lst->inicio->antr = no;
	    lst->inicio = no;
	    lst->tamanho++;
	} else {
		
	}
}

NO* busca_no_listade(LISTADE* lst, int val) {
	NO* inicio = lst->inicio;
	NO* fim = lst->fim;

	while (inicio != NULL && fim != NULL) {
		if (inicio && inicio->val == val)
		    return inicio;
		if (fim && fim->val == val)
		    return fim;

    	inicio = inicio->prox;
		fim = fim->antr;
	}
	return NULL;
}

void remove_listade(LISTADE* lst, int val) {
	if (listade_vazia(lst)) return;
	NO *tmp = NULL;

	// Busca o elemento requisitado (mesmo método de busca)
	tmp = busca_no_listade(lst, val);
	//

	// Não encontrou nenhum valor
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
	return busca_no_listade(lst, val) != NULL;
}

void imprime_listade(LISTADE* lst, bool completa) {
	printf("[");
	NO* tmp = lst->inicio;
	int n = 0;
	while (tmp != NULL) {
		if (tmp->prox == NULL) printf("%d", tmp->val);
		else				   printf("%d, ", tmp->val);
		tmp = tmp->prox;
		if (!completa && n >= 50) {
			printf(" ...");
			break;	
		}
		n++;
	}
	printf("]\n");
}

int main(int argc, char** argv) {
	LISTADE *lst = cria_listade();

	int nitems = -1;

	while (nitems < 0) {
		scanf("%d", &nitems);
	}

	int n = 0;
	if (nitems > 1) {
		n = nitems/2;

		printf("=== Inserção (FIM & INÍCIO):\n");
		for (int i = 0; i < n; i++) {
			insere_listade_inicio(lst, rand() % nitems);
		}

		for (int i = 0; i < n; i++) {
			insere_listade_fim(lst, rand() % nitems);
		}
	}

    imprime_listade(lst, nitems <= 50);

	printf("=== Inserção Ordenada:\n");
	for (int i = 0; i < 25; i++) {
		insere_ordenado_listade(lst, rand() % 20);
	}

	imprime_listade(lst, nitems <= 50);

	printf("=== Busca:\n\t");

	printf("Valor a ser buscado: ");
	int b = 0;
	scanf("%d", &b);

	bool bres = false;
	CRON_BEGIN();
		bres = busca_listade(lst, b);
	CRON_END();
	
	if (bres) {
		printf("Valor %d encontrado!\n", b);
	} else {
		printf("Valor %d não encontrado!\n", b);
	}

	printf("=== Remoção:\n");

	CRON_BEGIN();
		for (int i = 0; i < n; i++) {
			int rem = rand() % nitems;
			remove_listade(lst, rem);
			if (i < 200) printf("\tRemovido: %d\n", rem);
		}
		if (n > 200) printf("\t...\n");
	CRON_END();

	imprime_listade(lst, nitems <= 50);

	return 0;
}
