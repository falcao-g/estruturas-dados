#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

int main(void) {
	printf("pai de %d é %d", 2, pai(2));

	return EXIT_SUCCESS;
}

// gcc main.c heap.c -o main -> compila os arquivos juntos para conseguir usar sem o .so e .o

// Lib dinâmica

// gcc -fpic -c heap.c -> para criar o .o
// gcc -shared -o libfacom.so heap.o -> para criar/recompilar a biblioteca dinâmica (tem que começar com "lib")
// export LD_LIBRARY_PATH="/caminho/para/a/pasta/onde/ta/a/lib" -> para fazer o código enxergar a biblioteca
// gcc -L. -o main main.c -lfacom -> para compilar com a lib
// 
// agora como a lib é dinâmica, se mudarmos a lib, é só recompilar ela que muda nos arquivos que a usam


// Lib estática

// gcc -fpic -c heap.c -> para criar o .o
// ar -rcs libfacom.a heap.o -> para criar o arquivo libfacom.a (.a pq é a lib estática no linux)
// gcc -L. -o main main.c -lfacom -> para compilar com a lib
// 
// como a lib é estática, ela é integrada no arquivo compilado, não precisa atualizar o caminho da lib
// mas se alterar a lib tem que recompilar a lib e o arquivo que usa