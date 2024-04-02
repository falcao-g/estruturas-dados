Recursão é uma ferramenta muito poderosa, veja por exemplo, esse código:

```c
#include <stdio.h>
#include <stdlib.h>

void inc(int v) {
	printf("criando a stack %p %d\n", (void *)&v,v);
	
	// cada chamada cria uma nova variável em outro endereço da memória
	// com endereços decrescentes
	if (v!=0) {
		inc(v-1);
	}

	// aqui os endereços são crescentes pois são quando a função volta, quem diria que é uma stack...
	printf("retornando a stack %p %d\n", (void *)&v, v);
}

int main(void) {
	int v = 3;
	inc(v);

	return EXIT_SUCCESS;
}
```

Se executarmos, veremos um resultado assim no terminal:

```bash
criando a stack 0x16d20f62c 3
criando a stack 0x16d20f5fc 2
criando a stack 0x16d20f5cc 1
criando a stack 0x16d20f59c 0
retornando a stack 0x16d20f59c 0
retornando a stack 0x16d20f5cc 1
retornando a stack 0x16d20f5fc 2
retornando a stack 0x16d20f62c 3
```

Perceba que a recursão aqui cria uma stack de chamadas, que vão chamado as funções depois dela e quando chegam no final, voltam retornando todas, perceba também que os endereços se mantém os mesmos, isto fica trivial se lembrarmos que ainda estamos dentro da função.