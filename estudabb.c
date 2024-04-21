#include <stdio.h>
#include <stdlib.h>

typedef struct _elemento{
    int reg;
    struct _elemento *esq;
    struct _elemento *dir;
} elemento;

typedef struct {
    elemento * raiz;
} tarv;

void abb_constroi(tarv *parv){
    parv->raiz = NULL;
}

void abb_insere_node(tarv * parv, elemento ** ppnode, int reg) {
    if (*ppnode == NULL){
         *ppnode = malloc(sizeof(elemento));
         (*ppnode)->reg = reg;
         (*ppnode)->esq = NULL;
         (*ppnode)->dir = NULL;
    } else if ((*ppnode)->reg > reg) { // esquerda
        abb_insere_node(parv, &((*ppnode)->esq), reg);
    } else { // direita
        abb_insere_node(parv, &((*ppnode)->dir), reg);
    }
}

void abb_insere(tarv * parv, int reg){
    abb_insere_node(parv, &parv->raiz, reg);
}

elemento* abb_busca_node(tarv * parv, elemento * pnode, int reg) {
    elemento * ret;

    if (pnode == NULL){
        ret = NULL;
    } else if (pnode->reg > reg) { // esquerda
        ret = abb_busca_node(parv, pnode->esq, reg);
    } else if (pnode->reg < reg) { // direita
        ret = abb_busca_node(parv, pnode->dir, reg);
    } else {
        ret = pnode->reg;
    }
    return ret;
}

elemento* abb_busca(tarv * parv, int reg) {
    return abb_busca_node(parv, parv->raiz, reg);
}

int main(void) {
	tarv abb;
	abb_constroi(&abb);
	abb_insere(&abb, 10);
	printf("%d \n", abb.raiz->reg);

	abb_insere(&abb, 7);
	printf("%d \n", abb.raiz->esq->reg);

	abb_insere(&abb, 5);
	printf("%d \n", abb.raiz->esq->esq->reg);

	abb_insere(&abb, 9);
	printf("%d \n", abb.raiz->esq->dir->reg);

	abb_insere(&abb, 15);
	printf("%d \n", abb.raiz->dir->reg);

	abb_insere(&abb, 20);
	printf("%d \n", abb.raiz->dir->dir->reg);

	abb_insere(&abb, 18);
	printf("%d \n", abb.raiz->dir->dir->esq->reg);

	abb_insere(&abb, 16);
	printf("%d \n", abb.raiz->dir->dir->esq->esq->reg);

	abb_insere(&abb, 19);
	printf("%d \n", abb.raiz->dir->dir->esq->dir->reg);

	elemento * no;
	no = abb_busca(&abb, 55);

	if (no == NULL)
		printf("55 não está na ABB \n");
	else
		printf("55 está na ABB \n");

	no = abb_busca(&abb, 19);

	if (no == NULL)
		printf("19 não está na ABB \n");
	else
		printf("19 está na ABB \n");
		printf("%d \n", no);

	no = abb_busca(&abb, 10);

	if (no == NULL)
		printf("10 não está na ABB \n");
	else
		printf("10 está na ABB \n");
}