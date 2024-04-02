```c 
#include <stdio.h>
#include <stdlib.h>

void inc(int v) {
	printf("antes inc %p %d\n", (void *)&v,v);
}

int main(void) {
	// o v da main tem endereço diferente ao v da função, mesmo sendo passado como parâmetro
	int v;
	printf("fora %p %d\n", (void *)&v,v);
	v = 3;
	inc(v);
	printf("fora %p %d\n", (void *)&v, v);
	return EXIT_SUCCESS;
}
```

resultado:

```bash
fora 0x16b90f648 76553168
antes inc 0x16b90f60c 3
fora 0x16b90f648 3
```

note que o valor atribuído fora da função se mantém, isso é porque aqui passamos por valor e não por referência, isso significa que dentro da função é criado outra variável com o mesmo valor, mas uma outra variável.