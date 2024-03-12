#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void inc(int v)
{
	printf("antes inc %p %d\n", (void *)&v, v);
	// cada chamada cria uma nova variável em outro endereço da memória
	// com endereços decrescentes
	if (v != 0)
	{
		inc(v - 1);
	}

	// isso cria uma árvore
	if (v != 0)
	{
		inc(v - 1);
	}
	// aqui os endereços são crescentes pois são quando a função volta, quem diria que é uma stack...
	printf("depois inc %p %d\n", (void *)&v, v);
}

int main(void)
{
	// o v da main tem endereço diferente ao v da função, mesmo sendo passado como parâmetro
	// isso porque o c passa por valor, e não por referência
	int v;
	printf("fora %p %d\n", (void *)&v, v);
	v = 3;
	inc(v);
	printf("fora %p %d\n", (void *)&v, v);
	return EXIT_SUCCESS;
}