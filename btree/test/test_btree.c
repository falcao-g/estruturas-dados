#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/btree.h"
void imprime_arvore(tnode *x, int prof, int i) {
    int anda = 3;
    int j;
    int k;
    if (x->folha == TRUE) {
        for (j = 0; j < prof; j++)
            printf(" ");
        for (j = 0; j < x->n; j++)
            printf("%d ", x->chaves[j]);
        printf("\n");

    } else {
        imprime_arvore(x->c[0], prof + anda, 0);
        for (k = 0; k < x->n; k++) {
            for (j = 0; j < prof; j++)
                printf(" ");
            printf("%d\n", x->chaves[k]);
            imprime_arvore(x->c[k + 1], prof + anda, k + 1);
        }
        if (prof == 0)
            printf("------\n");
    }
}

void test_btree_split() {
    tarv arv;
    int t = 3;
    tnode *x;
    tnode *y;
    tnode *z;

    btree_constroi(&arv, t);
    x = arv.raiz;
    y = aloca_node(&arv);

    y->folha = TRUE;
    y->n = 5;
    y->chaves[0] = 10;
    y->chaves[1] = 20;
    y->chaves[2] = 30;
    y->chaves[3] = 40;
    y->chaves[4] = 50;

    x->c[0] = y;
    x->n = 0;
    x->folha = FALSE;
    arv.raiz = x;

    btree_split(&arv, x, 0);

    x = arv.raiz;
    y = x->c[0];
    z = x->c[1];
    assert(x->chaves[0] == 30);
    assert(x->folha == FALSE);
    assert(x->n == 1);

    assert(y->chaves[0] == 10);
    assert(y->chaves[1] == 20);
    assert(y->n == 2);
    assert(y->folha == TRUE);

    assert(z->chaves[0] == 40);
    assert(z->chaves[1] == 50);
    assert(z->n == 2);
    assert(z->folha == TRUE);
}

void test_btree_insere_naocheio() {
    tarv arv;
    int t = 3;

    tnode *x;
    tnode *y;

    btree_constroi(&arv, t);
    x = arv.raiz;
    y = aloca_node(&arv);

    y->folha = TRUE;
    y->n = 5;
    y->chaves[0] = 10;
    y->chaves[1] = 20;
    y->chaves[2] = 30;
    y->chaves[3] = 40;
    y->chaves[4] = 50;

    x->c[0] = y;
    x->n = 0;
    x->folha = FALSE;
    arv.raiz = x;

    btree_split(&arv, x, 0);

    btree_insere_naocheio(&arv, x, 23);

    y = x->c[0];

    assert(y->chaves[2] == 23);
    assert(y->n == 3);

    btree_insere_naocheio(&arv, x, 24);

    y = x->c[0];
    assert(y->chaves[3] == 24);
    assert(y->n == 4);

    btree_insere_naocheio(&arv, x, 25);
    btree_insere_naocheio(&arv, x, 26);

    x = arv.raiz;

    assert(x->chaves[0] == 23);
    assert(x->chaves[1] == 30);
    assert(x->n == 2);
    assert(x->folha == FALSE);

    y = x->c[0];

    assert(y->chaves[0] == 10);
    assert(y->chaves[1] == 20);
    assert(y->n == 2);
    assert(y->folha == TRUE);

    y = x->c[1];

    assert(y->chaves[0] == 24);
    assert(y->chaves[1] == 25);
    assert(y->chaves[2] == 26);
    assert(y->n == 3);
    assert(y->folha == TRUE);

    y = x->c[2];

    assert(y->chaves[0] == 40);
    assert(y->chaves[1] == 50);
    assert(y->n == 2);
    assert(y->folha == TRUE);
}

void test_btree_insere() {
    tarv arv;
    tnode *x, *y;
    int t;
    int i;
    t = 3;

    btree_constroi(&arv, t);

    for (i = 10; i <= 60; i += 10)
        btree_insere(&arv, i);

    x = arv.raiz;
    assert(x->chaves[0] == 30);
    assert(x->n == 1);
    assert(x->folha == FALSE);

    y = x->c[0];

    assert(y->chaves[0] == 10);
    assert(y->chaves[1] == 20);
    assert(y->n == 2);
    assert(y->folha == TRUE);

    y = x->c[1];

    assert(y->chaves[0] == 40);
    assert(y->chaves[1] == 50);
    assert(y->chaves[2] == 60);
    assert(y->n == 3);
    assert(y->folha == TRUE);

    for (i = 70; i < 100; i += 10)
        btree_insere(&arv, i);

    x = arv.raiz;
    assert(x->chaves[0] == 30);
    assert(x->chaves[1] == 60);
    assert(x->n == 2);
    assert(x->folha == FALSE);

    y = x->c[0];

    assert(y->chaves[0] == 10);
    assert(y->chaves[1] == 20);
    assert(y->n == 2);
    assert(y->folha == TRUE);

    y = x->c[1];

    assert(y->chaves[0] == 40);
    assert(y->chaves[1] == 50);
    assert(y->n == 2);
    assert(y->folha == TRUE);

    y = x->c[2];

    assert(y->chaves[0] == 70);
    assert(y->chaves[1] == 80);
    assert(y->chaves[2] == 90);
    assert(y->n == 3);
    assert(y->folha == TRUE);

    btree_insere(&arv, 21);
    btree_insere(&arv, 22);
    btree_insere(&arv, 23);
    btree_insere(&arv, 24);

    x = arv.raiz;
    assert(x->chaves[0] == 21);
    assert(x->chaves[1] == 30);
    assert(x->chaves[2] == 60);
    assert(x->n == 3);
    assert(x->folha == FALSE);

    y = x->c[0];

    assert(y->chaves[0] == 10);
    assert(y->chaves[1] == 20);
    assert(y->n == 2);
    assert(y->folha == TRUE);

    y = x->c[1];

    assert(y->chaves[0] == 22);
    assert(y->chaves[1] == 23);
    assert(y->chaves[2] == 24);
    assert(y->n == 3);
    assert(y->folha == TRUE);

    btree_insere(&arv, 51);
    btree_insere(&arv, 52);
    btree_insere(&arv, 53);
    btree_insere(&arv, 54);

    btree_insere(&arv, 91);
    btree_insere(&arv, 92);
    btree_insere(&arv, 93);
    btree_insere(&arv, 94);

    x = arv.raiz;
    assert(x->chaves[0] == 51);
    assert(x->n == 1);
    assert(x->folha == FALSE);

    y = x->c[0];

    assert(y->chaves[0] == 21);
    assert(y->chaves[1] == 30);
    assert(y->n == 2);
    assert(y->folha == FALSE);

    y = x->c[1];

    assert(y->chaves[0] == 60);
    assert(y->chaves[1] == 90);
    assert(y->n == 2);
    assert(y->folha == FALSE);
}

void test_btree_procura_chave() {
    tarv arv;
    tnode *x, *y;
    int t;
    int i;
    t = 3;

    btree_constroi(&arv, t);

    for (i = 10; i <= 50; i += 10)
        btree_insere(&arv, i);

    assert(procura_chave(arv.raiz, 10) == 0);
    assert(procura_chave(arv.raiz, 20) == 1);
    assert(procura_chave(arv.raiz, 30) == 2);
    assert(procura_chave(arv.raiz, 40) == 3);
    assert(procura_chave(arv.raiz, 50) == 4);
}

void test_btree_procura_chave_ic() {
    tarv arv;
    tnode *x, *y;
    int t;
    int i;
    t = 3;

    btree_constroi(&arv, t);

    for (i = 10; i <= 50; i += 10)
        btree_insere(&arv, i);

    assert(procura_ic(arv.raiz, 9) == 0);
    assert(procura_ic(arv.raiz, 18) == 1);
    assert(procura_ic(arv.raiz, 28) == 2);
    assert(procura_ic(arv.raiz, 38) == 3);
    assert(procura_ic(arv.raiz, 48) == 4);
    assert(procura_ic(arv.raiz, 51) == 5);
}
void test_btree_pega_irmao_maior() {
    tarv arv;
    tnode *x, *y;
    int t;
    int i;
    t = 3;

    btree_constroi(&arv, t);

    for (i = 10; i <= 100; i += 10)
        btree_insere(&arv, i);

    imprime_arvore(arv.raiz, 0, 0);
    assert(pega_irmao_maior(arv.raiz, 0) == 1);
    assert(pega_irmao_maior(arv.raiz, 1) == 2);
    assert(pega_irmao_maior(arv.raiz, 2) == 1);
}

void test_btree_merge() {
    tarv arv;
    tnode *x, *y;
    int t;
    int i;
    t = 3;

    btree_constroi(&arv, t);

    for (i = 10; i <= 60; i += 10)
        btree_insere(&arv, i);

    for (i = 70; i < 100; i += 10)
        btree_insere(&arv, i);
    btree_insere(&arv, 21);
    btree_insere(&arv, 22);
    btree_insere(&arv, 23);
    btree_insere(&arv, 24);

    btree_insere(&arv, 51);
    btree_insere(&arv, 52);
    btree_insere(&arv, 53);
    btree_insere(&arv, 54);

    btree_insere(&arv, 91);
    btree_insere(&arv, 92);
    btree_insere(&arv, 93);
    btree_insere(&arv, 94);

    x = arv.raiz;
    merge(&arv, x, 0);

    assert(x->chaves[0] == 21);
    assert(x->chaves[1] == 30);
    assert(x->chaves[2] == 51);
    assert(x->chaves[3] == 60);
    assert(x->chaves[4] == 90);
    assert(x->n == 5);
    assert(x->folha == FALSE);

    y = x->c[0];

    assert(y->chaves[0] == 10);
    assert(y->chaves[1] == 20);
    assert(y->n == 2);
    assert(y->folha == TRUE);

    y = x->c[1];

    assert(y->chaves[0] == 22);
    assert(y->chaves[1] == 23);
    assert(y->chaves[2] == 24);
    assert(y->n == 3);
    assert(y->folha == TRUE);

    y = x->c[2];

    assert(y->chaves[0] == 40);
    assert(y->chaves[1] == 50);
    assert(y->n == 2);
    assert(y->folha == TRUE);

    y = x->c[3];

    assert(y->chaves[0] == 52);
    assert(y->chaves[1] == 53);
    assert(y->chaves[2] == 54);
    assert(y->n == 3);
    assert(y->folha == TRUE);

    y = x->c[4];

    assert(y->chaves[0] == 70);
    assert(y->chaves[1] == 80);
    assert(y->n == 2);
    assert(y->folha == TRUE);

    y = x->c[5];

    assert(y->chaves[0] == 91);
    assert(y->chaves[1] == 92);
    assert(y->chaves[2] == 93);
    assert(y->chaves[3] == 94);
    assert(y->n == 4);
    assert(y->folha == TRUE);
}

void test_btree_merge2() {
    tarv arv;
    tnode *x, *y;
    int t;
    int i;
    t = 3;

    btree_constroi(&arv, t);

    for (i = 10; i <= 60; i += 10)
        btree_insere(&arv, i);

    for (i = 70; i < 100; i += 10)
        btree_insere(&arv, i);
    btree_insere(&arv, 21);
    btree_insere(&arv, 22);
    btree_insere(&arv, 23);
    btree_insere(&arv, 24);

    btree_insere(&arv, 51);
    btree_insere(&arv, 52);
    btree_insere(&arv, 53);
    btree_insere(&arv, 54);

    btree_insere(&arv, 91);
    btree_insere(&arv, 92);
    btree_insere(&arv, 93);
    btree_insere(&arv, 94);

    x = arv.raiz->c[0];
    x->c[1]->n = 2;
    merge(&arv, x, 0);

    assert(x->chaves[0] == 30);
    assert(x->n == 1);
    assert(x->folha == FALSE);

    y = x->c[0];

    assert(y->chaves[0] == 10);
    assert(y->chaves[1] == 20);
    assert(y->chaves[2] == 21);
    assert(y->chaves[3] == 22);
    assert(y->chaves[4] == 23);
    assert(y->n == 5);
    assert(y->folha == TRUE);

    y = x->c[1];

    assert(y->chaves[0] == 40);
    assert(y->chaves[1] == 50);
    assert(y->n == 2);
    assert(y->folha == TRUE);
}
void test_btree_merge3() {
    tarv arv;
    tnode *x, *y;
    int t;
    int i;
    t = 3;

    btree_constroi(&arv, t);

    for (i = 10; i <= 60; i += 10)
        btree_insere(&arv, i);

    for (i = 70; i < 100; i += 10)
        btree_insere(&arv, i);
    btree_insere(&arv, 21);
    btree_insere(&arv, 22);
    btree_insere(&arv, 23);
    btree_insere(&arv, 24);

    btree_insere(&arv, 51);
    btree_insere(&arv, 52);
    btree_insere(&arv, 53);
    btree_insere(&arv, 54);

    btree_insere(&arv, 91);
    btree_insere(&arv, 92);
    btree_insere(&arv, 93);
    btree_insere(&arv, 94);

    x = arv.raiz->c[0];
    x->c[1]->n = 2;
    merge(&arv, x, 1);

    assert(x->chaves[0] == 21);

    y = x->c[0];

    assert(y->chaves[0] == 10);
    assert(y->chaves[1] == 20);
    assert(y->n == 2);
    assert(y->folha == TRUE);

    y = x->c[1];
    assert(y->chaves[0] == 22);
    assert(y->chaves[1] == 23);
    assert(y->chaves[2] == 30);
    assert(y->chaves[3] == 40);
    assert(y->chaves[4] == 50);
    assert(y->n == 5);
    assert(y->folha == TRUE);
}

void test_btree_empresta_irmao() {
    tarv arv;
    tnode *x, *y, *z;
    int t;
    int i;
    t = 3;

    btree_constroi(&arv, t);

    for (i = 10; i <= 60; i += 10)
        btree_insere(&arv, i);

    for (i = 70; i < 100; i += 10)
        btree_insere(&arv, i);
    btree_insere(&arv, 21);
    btree_insere(&arv, 22);
    btree_insere(&arv, 23);
    btree_insere(&arv, 24);

    btree_insere(&arv, 51);
    btree_insere(&arv, 52);
    btree_insere(&arv, 53);
    btree_insere(&arv, 54);

    btree_insere(&arv, 91);
    btree_insere(&arv, 92);
    btree_insere(&arv, 93);
    btree_insere(&arv, 94);

    x = arv.raiz->c[0];
    pega_emprestado_irmao(x, 0, 1);

    y = x->c[0];
    z = x->c[1];

    assert(x->chaves[0] == 22);
    assert(x->chaves[1] == 30);
    assert(x->n == 2);
    assert(x->folha == FALSE);

    assert(y->chaves[0] == 10);
    assert(y->chaves[1] == 20);
    assert(y->chaves[2] == 21);
    assert(y->n == 3);
    assert(y->folha == TRUE);

    assert(z->chaves[0] == 23);
    assert(z->chaves[1] == 24);
    assert(z->n == 2);
    assert(z->folha == TRUE);
}

void test_btree_empresta_irmao2() {
    tarv arv;
    tnode *x, *y, *z;
    int t;
    int i;
    t = 3;

    btree_constroi(&arv, t);

    for (i = 10; i <= 60; i += 10)
        btree_insere(&arv, i);

    for (i = 70; i < 100; i += 10)
        btree_insere(&arv, i);
    btree_insere(&arv, 21);
    btree_insere(&arv, 22);
    btree_insere(&arv, 23);
    btree_insere(&arv, 24);

    btree_insere(&arv, 51);
    btree_insere(&arv, 52);
    btree_insere(&arv, 53);
    btree_insere(&arv, 54);

    btree_insere(&arv, 91);
    btree_insere(&arv, 92);
    btree_insere(&arv, 93);
    btree_insere(&arv, 94);

    x = arv.raiz->c[0];
    pega_emprestado_irmao(x, 0, 1);

    y = x->c[0];
    z = x->c[1];

    assert(x->chaves[0] == 22);
    assert(x->chaves[1] == 30);
    assert(x->n == 2);
    assert(x->folha == FALSE);

    assert(y->chaves[0] == 10);
    assert(y->chaves[1] == 20);
    assert(y->chaves[2] == 21);
    assert(y->n == 3);
    assert(y->folha == TRUE);

    assert(z->chaves[0] == 23);
    assert(z->chaves[1] == 24);
    assert(z->n == 2);
    assert(z->folha == TRUE);
}

void test_btree_remove() {
    tarv arv;
    int t;
    tnode *x;
    t = 3;

    btree_constroi(&arv, t);
    btree_insere(&arv, 10);
    btree_insere(&arv, 20);
    btree_insere(&arv, 30);
    btree_insere(&arv, 40);
    btree_insere(&arv, 50);
    btree_insere(&arv, 60);

    x = arv.raiz;

    assert(x->chaves[0] == 30);

    btree_remove(&arv, 10);
    btree_remove(&arv, 20);
    btree_remove(&arv, 30);
    btree_remove(&arv, 40);
    btree_remove(&arv, 50);

    assert(x->chaves[0] == 60);
    assert(x->n == 1);
    assert(x->folha == TRUE);

    btree_insere(&arv, 10);
    btree_insere(&arv, 20);
    btree_insere(&arv, 30);
    btree_insere(&arv, 40);
    btree_insere(&arv, 50);

    x = arv.raiz;

    imprime_arvore(arv.raiz, 0, 0);
    assert(x->chaves[0] == 30);
    btree_remove(&arv, 10);
    imprime_arvore(arv.raiz, 0, 0);
    assert(x->chaves[0] == 40);
    btree_remove(&arv, 40);
    imprime_arvore(arv.raiz, 0, 0);
    assert(x->chaves[0] == 20);
}

void test_btree_remove2() {
    tarv arv;
    int t;
    int i;
    t = 3;

    btree_constroi(&arv, t);

    for (i = 10; i <= 60; i += 10)
        btree_insere(&arv, i);

    for (i = 70; i < 100; i += 10)
        btree_insere(&arv, i);

    btree_insere(&arv, 21);
    btree_insere(&arv, 22);
    btree_insere(&arv, 23);
    btree_insere(&arv, 24);

    btree_insere(&arv, 51);
    btree_insere(&arv, 52);
    btree_insere(&arv, 53);
    btree_insere(&arv, 54);

    btree_insere(&arv, 91);
    btree_insere(&arv, 92);
    btree_insere(&arv, 93);
    btree_insere(&arv, 94);

    imprime_arvore(arv.raiz, 0, 0);

    btree_remove(&arv, 24);

    imprime_arvore(arv.raiz, 0, 0);

    btree_remove(&arv, 50);
    imprime_arvore(arv.raiz, 0, 0);

    btree_remove(&arv, 51);
    imprime_arvore(arv.raiz, 0, 0);

    btree_remove(&arv, 54);
    imprime_arvore(arv.raiz, 0, 0);

    btree_remove(&arv, 60);
    imprime_arvore(arv.raiz, 0, 0);

    btree_remove(&arv, 30);
    imprime_arvore(arv.raiz, 0, 0);

    btree_remove(&arv, 21);
    imprime_arvore(arv.raiz, 0, 0);

    btree_remove(&arv, 22);
    imprime_arvore(arv.raiz, 0, 0);

    btree_remove(&arv, 23);
    imprime_arvore(arv.raiz, 0, 0);

    btree_remove(&arv, 80);
    imprime_arvore(arv.raiz, 0, 0);

    btree_remove(&arv, 90);
    imprime_arvore(arv.raiz, 0, 0);

    btree_remove(&arv, 91);
    imprime_arvore(arv.raiz, 0, 0);

    btree_remove(&arv, 92);
    imprime_arvore(arv.raiz, 0, 0);

    btree_remove(&arv, 52);
    imprime_arvore(arv.raiz, 0, 0);

    btree_remove(&arv, 40);
    imprime_arvore(arv.raiz, 0, 0);

    btree_remove(&arv, 20);
    imprime_arvore(arv.raiz, 0, 0);

    btree_remove(&arv, 53);
    imprime_arvore(arv.raiz, 0, 0);

    btree_remove(&arv, 10);
    imprime_arvore(arv.raiz, 0, 0);

    btree_remove(&arv, 70);
    imprime_arvore(arv.raiz, 0, 0);

    btree_remove(&arv, 93);
    imprime_arvore(arv.raiz, 0, 0);

    btree_remove(&arv, 94);
    imprime_arvore(arv.raiz, 0, 0);

    btree_remove(&arv, 94);
    imprime_arvore(arv.raiz, 0, 0);
}

int main(void) {
    tarv arv;
    int t;
    t = 2;

    btree_constroi(&arv, t);
    btree_insere(&arv, 10);
    btree_insere(&arv, 20);
    btree_insere(&arv, 30);
    btree_insere(&arv, 40);
    btree_insere(&arv, 50);
    btree_insere(&arv, 60);
    btree_insere(&arv, 70);
    btree_insere(&arv, 80);
    btree_insere(&arv, 90);
    btree_insere(&arv, 100);
    btree_insere(&arv, 15);
    btree_insere(&arv, 25);
    btree_insere(&arv, 13);
    btree_insere(&arv, 12);

    imprime_arvore(arv.raiz, 0, 0);

    btree_remove(&arv, arv.raiz->chaves[0]);

    imprime_arvore(arv.raiz, 0, 0);
}