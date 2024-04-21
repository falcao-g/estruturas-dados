#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define MAXCHAR 10
	
typedef struct {
	char key[MAXCHAR];
	char valor[MAXCHAR]; // assume que key = valor
} elemento;

typedef struct {
	elemento* tabela;
	int size;
	int max;
} thash;

void inicializa(thash* hash, int nbuckets) {
	hash->tabela = calloc(sizeof(elemento *), nbuckets + 1);
	hash->max = nbuckets + 1;
	hash->size = 0;

	for (int i = 0; i < nbuckets; i++) {
		hash->tabela[i].key[0] = '\0';
		hash->tabela[i].valor[0] = '\0'; // assumindo que valores não podem ser 0.
	}
}

int h(char* key) {
	int tam = strlen(key);
	int total = 0;

	for (int i = 0; i < tam; i++) {
		total += key[i];
	}

	return total;
}

// os comentários representam o que mudaria para ser um double hash
int insere(thash* hash, char* key) {
	int cod = h(key);
	int pos = cod % hash->max;
	// int i = 0;

	if (hash->max == (hash->size + 1)) {
		return EXIT_FAILURE;
	}
	
	while (hash->tabela[pos].key[0] != '\0' && strcmp(hash->tabela[pos].key, "*") != 0) {
		pos = (pos + 1) % hash->max;
		//pos = (cod + i * cod) % hash->max;
		//i += 1;
	}

	strcpy(hash->tabela[pos].key, key);
	strcpy(hash->tabela[pos].valor, key);
	hash->size += 1;

	return EXIT_SUCCESS;
}

// aqui também, comentários == double hash
int remove_elemento(thash* hash, char* key) {
	int cod = h(key);
	int pos = cod % hash->max;
	// int i = 0;

	while (hash->tabela[pos].key[0] != '\0') {
		if (strcmp(hash->tabela[pos].key, key) == 0) {
			strcpy(hash->tabela[pos].key, "*");
			strcpy(hash->tabela[pos].valor, "*");
			return EXIT_SUCCESS;
		}
		pos = (pos + 1) % hash->max;
		//pos = (cod + i * cod) % hash->max;
		//i += 1;
	}
	return EXIT_FAILURE;
}

// mesma coisa, se você descomentar e tirar o outro cálculo do pos
// vira double hash
int busca(thash* hash, char* key) {
	int cod = h(key);
	int pos = cod % hash->max;
	// int i = 0;

	while(hash->tabela[pos].key[0] != '\0') {
		if(strcmp(hash->tabela[pos].key, key) == 0) {
			return EXIT_SUCCESS;
		}

		pos = (pos + 1) % hash->max;
		//pos = (cod + i * cod) % hash->max;
		//i += 1;
	}
	return EXIT_FAILURE;
}

int main(void) {
	thash hash;
	inicializa(&hash, 4);
	insere(&hash, "abc");
	insere(&hash, "bc");
	insere(&hash, "bbc");
	insere(&hash, "fbc");

	for(int i = 0; i < hash.max; i++) {
		printf("%s %d \n", (char*) hash.tabela[i].key, i);
	}
	printf("\n");

	remove_elemento(&hash, "abc");

	for(int i = 0; i < hash.max; i++) {
		printf("%s %d \n", (char*) hash.tabela[i].key, i);
	}
	printf("\n");

	if (busca(&hash, "fbc") == 0) {
		printf("fbc está na hash \n");
	} else {
		printf("fbc não está na hash \n");
	}

	if (busca(&hash, "bcd") == 0) {
		printf("bcd está na hash \n");
	} else {
		printf("bcd não está na hash \n");
	}
	printf("\n");

	remove_elemento(&hash, "bbc");

	for(int i = 0; i < hash.max; i++) {
		printf("%s %d \n", (char*) hash.tabela[i].key, i);
	}

	return EXIT_SUCCESS;
}
