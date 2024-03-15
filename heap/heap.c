#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void imprime_vetor(int v[], int tam) {
    printf("Vetor: ");
    for (int i = 0; i < tam; i++)
        printf("%d ", v[i]);
    printf("\n");
}

void assert_vetor(int v[], int res[], int tam) {
    for (int i = 0; i < tam; i++) {
        assert(v[i] == res[i]);
    }
}

void troca(int *a, int *b) {
    int aux = *a;
    *a = *b;
    *b = aux;
}

int acessa_max(int v[]) {
    return v[0];
}

int pai(int n) {
    return ((n - 1) / 2);
}

void testa_pai(void) {
    assert(pai(0) == 0);
    assert(pai(1) == 0);
    assert(pai(3) == 1);
    assert(pai(7) == 3);
    assert(pai(12) == 5);
}

int filho_esq(int n) {
    return (n * 2 + 1);
}

void testa_filho_esq(void) {
    assert(filho_esq(0) == 1);
    assert(filho_esq(1) == 3);
    assert(filho_esq(2) == 5);
    assert(filho_esq(6) == 13);
    assert(filho_esq(10) == 21);
}

int filho_dir(int n) {
    return (n * 2 + 2);
}

void testa_filho_dir(void) {
    assert(filho_dir(0) == 2);
    assert(filho_dir(1) == 4);
    assert(filho_dir(2) == 6);
    assert(filho_dir(6) == 14);
    assert(filho_dir(10) == 22);
}

void desce(int v[], int tam, int n) {
    int maior = n;
    int esq = filho_esq(n);
    int dir = filho_dir(n);

    if (v[esq] > v[maior] && esq < tam)
        maior = esq;
    if (v[dir] > v[maior] && dir < tam)
        maior = dir;

    if (maior != n) {
        troca(&v[maior], &v[n]);
        desce(v, tam, maior);
    }
}

void testa_desce(void) {
    int vetor[7] = {1, 5, 3, 4, 10, 2, 0};
    desce(vetor, 7, 1);
    int esperado[7] = {1, 10, 3, 4, 5, 2, 0};
    assert_vetor(vetor, esperado, 7);

    int vetor2[7] = {9, 5, 8, 20, 4, 6, 3};
    desce(vetor2, 7, 1);
    desce(vetor2, 7, 0);
    int esperado2[7] = {20, 9, 8, 5, 4, 6, 3};
    assert_vetor(vetor2, esperado2, 5);

    int vetor3[3] = {3, 2, 1};
    desce(vetor3, 3, 0);
    int esperado3[3] = {3, 2, 1};
    assert_vetor(vetor3, esperado3, 3);

    int vetor4[7] = {7, 6, 5, 4, 3, 2, 10};
    desce(vetor4, 7, 2);
    int esperado4[7] = {7, 6, 10, 4, 3, 2, 5};
    assert_vetor(vetor4, esperado4, 7);
}

void sobe(int v[], int n) {
    int p = pai(n);
    if (v[p] < v[n]) {
        troca(&v[p], &v[n]);
        sobe(v, p);
    }
}

void testa_sobe(void) {
    int vetor[3] = {8, 9, 10};
    sobe(vetor, 2);
    int esperado[3] = {10, 9, 8};
    assert_vetor(vetor, esperado, 3);

    int vetor2[7] = {11, 9, 8, 20, 4, 2, 1};
    sobe(vetor2, 3);
    int esperado2[7] = {20, 11, 8, 9, 4, 2, 1};
    assert_vetor(vetor2, esperado2, 7);

    int vetor3[7] = {25, 24, 23, 22, 21, 24, 19};
    sobe(vetor3, 5);
    int esperado3[7] = {25, 24, 24, 22, 21, 23, 19};
    assert_vetor(vetor3, esperado3, 7);

    int vetor4[7] = {7, 6, 5, 4, 3, 2, 1};
    sobe(vetor4, 6);
    int esperado4[7] = {7, 6, 5, 4, 3, 2, 1};
    assert_vetor(vetor4, esperado4, 7);
}

void constroi_heap(int v[], int tam) {
    for (int n = pai(tam); n >= 0; n--)
        desce(v, tam, n);
}

void testa_constroi_heap(void) {
    int vetor[7] = {1, 5, 3, 4, 10, 2, 0};
    constroi_heap(vetor, 7);
    int esperado[7] = {10, 5, 3, 4, 1, 2, 0};
    assert_vetor(vetor, esperado, 7);

    int vetor2[3] = {1, 2, 3};
    constroi_heap(vetor2, 3);
    int esperado2[3] = {3, 2, 1};
    assert_vetor(vetor2, esperado2, 3);

    int vetor3[7] = {7, 6, 5, 4, 3, 2, 1};
    constroi_heap(vetor3, 7);
    int esperado3[7] = {7, 6, 5, 4, 3, 2, 1};
    assert_vetor(vetor3, esperado3, 7);

    int vetor4[7] = {10, 20, 5, 35, 50, 6, 100};
    constroi_heap(vetor4, 7);
    int esperado4[7] = {100, 50, 10, 35, 20, 6, 5};
    assert_vetor(vetor4, esperado4, 7);
}

int insere_elemento(int v[], int *tam, int max, int valor) {
    if (*tam == max)
        return EXIT_FAILURE;

    v[*tam] = valor;
    sobe(v, *tam);
    *tam += 1;

    return EXIT_SUCCESS;
}

void testa_insere_elemento(void) {
    int vetor[7] = {6, 5, 4, 3, 2, 1};
    int tam = 6;
    int max = 7;
    int valor = 7;
    int esperado[7] = {7, 5, 6, 3, 2, 1, 4};
    insere_elemento(vetor, &tam, max, valor);
    assert_vetor(vetor, esperado, 7);

    int vetor2[3] = {90, 80};
    int tam2 = 2;
    int max2 = 3;
    int valor2 = 100;
    int esperado2[3] = {100, 80, 90};
    insere_elemento(vetor2, &tam2, max2, valor2);
    assert_vetor(vetor2, esperado2, 3);

    int vetor3[7] = {7, 6, 5, 4, 3, 2};
    int tam3 = 6;
    int max3 = 7;
    int valor3 = 1;
    int esperado3[7] = {7, 6, 5, 4, 3, 2, 1};
    insere_elemento(vetor3, &tam3, max3, valor3);
    assert_vetor(vetor3, esperado3, 7);

    int vetor4[3] = {33, 22, 11};
    int tam4 = 3;
    int max4 = 3;
    int valor4 = 44;
    assert(insere_elemento(vetor4, &tam4, max4, valor4) == EXIT_FAILURE);
}

int extrai_max(int v[], int *tam) {
    int max = v[0];
    max = v[0];
    *tam -= 1;
    v[0] = v[*tam];
    desce(v, *tam, 0);
    return max;
}

void testa_extrai_max(void) {
    int vetor[3] = {100, 80, 70};
    int tam = 3;
    int esperado[2] = {80, 70};
    extrai_max(vetor, &tam);
    assert_vetor(vetor, esperado, 2);

    int vetor2[7] = {45, 34, 33, 29, 27, 25, 23};
    int tam2 = 7;
    int esperado2[6] = {34, 29, 33, 23, 27, 25};
    extrai_max(vetor2, &tam2);
    assert_vetor(vetor2, esperado2, 6);
}

void altera_prioridade(int v[], int tam, int n, int valor) {
    int aux = v[n];
    v[n] = valor;

    if (v[n] > aux)
        sobe(v, n);
    if (v[n] < aux)
        desce(v, tam, n);
}

void testa_altera_prioridade(void) {
    int vetor[3] = {100, 90, 70};
    int tam = 3;
    int n = 2;
    int valor = 101;
    altera_prioridade(vetor, tam, n, valor);
    int esperado[3] = {101, 90, 100};
    assert_vetor(vetor, esperado, 3);

    int vetor2[3] = {101, 90, 100};
    int tam2 = 3;
    int n2 = 0;
    int valor2 = 70;
    altera_prioridade(vetor2, tam2, n2, valor2);
    int esperado2[3] = {100, 90, 70};
    assert_vetor(vetor2, esperado2, 3);

    int vetor3[7] = {100, 90, 80, 70, 60, 50, 40};
    int tam3 = 7;
    int n3 = 4;
    int valor3 = 110;
    altera_prioridade(vetor3, tam3, n3, valor3);
    int esperado3[7] = {110, 100, 80, 70, 90, 50, 40};
    assert_vetor(vetor3, esperado3, 7);

    int vetor4[7] = {100, 90, 80, 70, 60, 50, 40};
    int tam4 = 7;
    int n4 = 2;
    int valor4 = 30;
    altera_prioridade(vetor4, tam4, n4, valor4);
    int esperado4[7] = {100, 90, 50, 70, 60, 30, 40};
    assert_vetor(vetor4, esperado4, 7);
}

void heap_sort(int v[], int tam) {
    for (int i = tam - 1; i > 0; i--) {
        troca(&v[0], &v[i]);
        desce(v, i, 0);
    }
}

void testa_heapsort(void) {
    int vetor[3] = {10, 9, 8};
    int esperado[3] = {8, 9, 10};
    heap_sort(vetor, 3);
    assert_vetor(vetor, esperado, 3);

    int vetor2[7] = {100, 87, 69, 43, 35, 34, 23};
    int esperado2[7] = {23, 34, 35, 43, 69, 87, 100};
    heap_sort(vetor2, 7);
    assert_vetor(vetor2, esperado2, 7);

    int vetor3[15] = {15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int esperado3[15] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    heap_sort(vetor3, 15);
    assert_vetor(vetor3, esperado3, 15);

    int vetor4[2] = {2, 1};
    int esperado4[2] = {1, 2};
    heap_sort(vetor4, 2);
    assert_vetor(vetor4, esperado4, 2);

    int vetor5[1] = {3};
    heap_sort(vetor5, 1);
}

int main(void) {
    // Roda os testes para garantir que as funções estão corretas
    testa_pai();
    testa_filho_esq();
    testa_filho_dir();
    testa_desce();
    testa_sobe();
    testa_constroi_heap();
    testa_insere_elemento();
    testa_extrai_max();
    testa_altera_prioridade();
    testa_heapsort();

    return EXIT_SUCCESS;
}
