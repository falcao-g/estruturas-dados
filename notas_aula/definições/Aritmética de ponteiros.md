```c
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

int main(void) {
	int i[10];
	int *p = &i[0];
	int b = 7;

	printf("b %d\n", b);
	printf("i %p\n", i);
	printf("p %p\n", p);
	printf("b %p\n", &b);

	p = i-(i-&b); // aqui calculamos a diferença, porque o compilador sacaneia a gente se tentar colocar numero estatico 
	*p = 6;
	assert(b==6);
	printf("b %d\n", b);

	return 0;
}
```

Observe o código acima, utilizamos [Ponteiros](Ponteiros.md) e Aritmética de ponteiros para "invadir" o endereço de memória da variável b e alterar ela para 6.