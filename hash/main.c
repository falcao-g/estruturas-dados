#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

typedef struct {
	char nome[30];
	char rga[12];
} taluno;

void* aloca_aluno(char *nome, char *rga) {
	taluno* aluno = malloc(sizeof(aluno));
	strcpy(aluno->nome, nome);
	strcpy(aluno->rga, rga);
	return aluno;
}

char* pega_rga(void* paluno) {
	return ((taluno *)paluno)->rga;
}

int main(void) {
	taluno* paluno;
	thash hash;

	paluno = aloca_aluno("gabriel", "202319049204");
	printf("meu nome é %s rga %s", paluno->nome, pega_rga(paluno));
	
	hash_constroi(&hash, 10, pega_rga);
	return EXIT_SUCCESS;
}
