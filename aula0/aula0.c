#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(void)
{
	int i[10];
	int *p = &i[0];
	int b = 7;

	printf("b %d\n", b);
	printf("i %p\n", i);
	printf("p %p\n", p);
	printf("b %p\n", &b);

	// podemos "roubar" e acessar o endereço de b a partir de i
	p = i - (i - &b);
	*p = 6;

	// usar assert é uma boa prática para testar se o esperado ocorreu
	assert(b == 6);
	printf("b %d\n", b);

	return 0;
}