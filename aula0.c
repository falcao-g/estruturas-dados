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

	//dúvida
	p = i-(i-&b);
	*p = 6;
	assert(b==6);
	printf("b %d\n", b);

	return 0;
}