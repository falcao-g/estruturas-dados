#include <stdlib.h>
#include <stdio.h>

void troca(int *a, int *b) {
	int aux = *a;
	*a = *b;
	*b = aux;
}

int pai(int n) {
	return (n - 1) / 2;
}


int filho_esq(int n) {
	return (n * 2) + 1;
}

int filho_dir(int n) {
	return (n * 2) + 2;
}


void desce(int v[], int tam, int n) {
	int maior = n;
	int esq = filho_esq(n);
	int dir = filho_dir(n);

	if (esq < tam && v[esq] > v[maior]) 
		maior = esq;
	if (dir < tam && v[dir] > v[maior])
		maior = dir;

	if (maior != n) {
		troca(&v[n], &v[maior]);
		desce(v, tam, maior);
	}
}

// invetermos as comparações entre os valores para o min
void desce_min(int v[], int tam, int n) {
	int menor = n;
	int esq = filho_esq(n);
	int dir = filho_dir(n);

	if (esq < tam && v[esq] < v[menor]) 
		menor = esq;
	if (dir < tam && v[dir] < v[menor])
		menor = dir;

	if (menor != n) {
		troca(&v[n], &v[menor]);
		desce(v, tam, menor);
	}
}



void constroi_heap(int v[], int tam) {
	for (int i = pai(tam); i >= 0; i--) {
		desce(v, tam, i);
	}
}

// só é necessário criar outra pois tenho duas funções desce no mesmo arquivo
void constroi_heap_min(int v[], int tam) {
	for (int i = pai(tam); i >= 0; i--) {
		desce_min(v, tam, i);
	}
}


void sobe(int v[], int n) {
	int p = pai(n);

	if (v[p] < v[n]) {
		troca(&v[n], &v[p]);
		sobe(v, p);
	}
}

// mesma coisa, só invertemos a comparação
void sobe_min(int v[], int n) {
	int p = pai(n);

	if (v[p] > v[n]) {
		troca(&v[n], &v[p]);
		sobe(v, p);
	}
}


// mudei o nome pois pode ser usado para os dois métodos
int extrai_raiz(int v[], int *tam) {
	int max = v[0];
	*tam -= 1;
	troca(&v[0], &v[*tam]);
	desce(v, *tam, 0);
	return max;
}


void altera_prioridade(int v[], int tam, int n, int valor) {
	int anterior = v[n];
	v[n] = valor;

	if (valor > anterior)
		sobe(v, n);
	if (valor < anterior)
		desce(v, tam, n);
}

// inverte as comparações
void altera_prioridade_min(int v[], int tam, int n, int valor) {
	int anterior = v[n];
	v[n] = valor;

	if (valor < anterior)
		sobe_min(v, n);
	if (valor > anterior)
		desce_min(v, tam, n);
}

// heapsort é o mesmo, max-heap deixa o vetor crescente
// min-heap deixa o valor decrescente
// se você tem um dos dois e quer o outro, só imprime o vetor de ré
void heap_sort(int v[], int tam) {
	for (int i = tam - 1; i > 0; i--) {
		troca(&v[0], &v[i]);
		desce(v, i, 0);
	}
}

// tem duas funções pq tem que chamar o desce correspondente
void heap_sort_min(int v[], int tam) {
	for (int i = tam - 1; i > 0; i--) {
		troca(&v[0], &v[i]);
		desce_min(v, i, 0);
	}
}


int insere_elemento(int v[], int *tam, int max, int valor) {
	if (*tam == max)
		return EXIT_FAILURE;

	v[*tam] = valor;
	sobe(v, *tam);
	*tam += 1;

	return EXIT_SUCCESS;
}

// tem que chamar o sobe correto só
int insere_elemento_min(int v[], int *tam, int max, int valor) {
	if (*tam == max)
		return EXIT_FAILURE;

	v[*tam] = valor;
	sobe_min(v, *tam);
	*tam += 1;

	return EXIT_SUCCESS;
}


void remove_elemento(int v[], int *tam, int n) {
	int removido = v[n];
	*tam -= 1;
	v[n] = v[*tam];

	if (v[n] > removido) 
		sobe(v, n);
	if (v[n] < removido)
		desce(v, *tam, n);
}

// comparações e funcões...
void remove_elemento_min(int v[], int *tam, int n) {
	int removido = v[n];
	*tam -= 1;
	v[n] = v[*tam];

	if (v[n] < removido) 
		sobe_min(v, n);
	if (v[n] > removido)
		desce_min(v, *tam, n);
}


int main(void) {
	// max-heap
	int v[20] = {1, 5, 7, 6, 8, 9, 10, 12, 13, 15, 11, 14};
	int tam = 12;
	constroi_heap(v, tam);
	insere_elemento(v, &tam, 20, 20);
	insere_elemento(v, &tam, 20, 3);
	insere_elemento(v, &tam, 20, 18);

	extrai_raiz(v, &tam);
	extrai_raiz(v, &tam);
	extrai_raiz(v, &tam);

	altera_prioridade(v, tam, 1, 2);
	altera_prioridade(v, tam, 4, 100);

	for (int i = 0; i < tam; i++) {
		printf("%d ", v[i]);
	}
	printf("\n");

	heap_sort(v, tam);

	for (int i = 0; i < tam; i++) {
		printf("%d ", v[i]);
	}
	printf("\n");

	// min-heap
	int v2[20] = {1, 5, 7, 6, 8, 9, 10, 12, 13, 15, 11, 14};
	int tam2 = 12;
	constroi_heap_min(v2, tam2);
	insere_elemento_min(v2, &tam2, 20, 20);
	insere_elemento_min(v2, &tam2, 20, 3);
	insere_elemento_min(v2, &tam2, 20, 18);

	extrai_raiz(v2, &tam2);
	extrai_raiz(v2, &tam2);
	extrai_raiz(v2, &tam2);

	altera_prioridade_min(v2, tam2, 1, 2);
	altera_prioridade_min(v2, tam2, 4, 100);

	for (int i = 0; i < tam2; i++) {
		printf("%d ", v2[i]);
	}
	printf("\n");

	heap_sort_min(v2, tam2);

	for (int i = 0; i < tam2; i++) {
		printf("%d ", v2[i]);
	}

	return EXIT_SUCCESS;
}