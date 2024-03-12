#include <stdio.h>
#include <stdlib.h>

void rec(int v) {
	printf("stack sendo criada %p %d\n", (void *) &v, v);
	
	// a combinação das condições vai criar uma árvore
	if (v != 0) rec(v-1);
	if (v != 0) rec(v-1);

	printf("stack sendo retornada %p %d\n", (void*) &v, v);
} // temos aqui O(2ˆN) chamadas e O(N) de complexidade de espaço

int main (void) {
	int v = 2;
	rec(v);
}
