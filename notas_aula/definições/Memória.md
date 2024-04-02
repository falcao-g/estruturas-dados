```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int i[10];
	int *p = &i[0];
	int b = 7;
	
	printf("i %p\n", i);
	printf("p %p\n", p);
	printf("b %p\n", &b);
	
	return EXIT_SUCCESS;
}
```

Se executarmos esse código, perceberemos a seguinte saída:

```bash
i 0x16d2db620
p 0x16d2db610
b 0x16d2db60c
```

Isso nos mostra os endereços de memória das variáveis que declaramos, perceba que eles estão diminuindo, isto é porque declaração de variável se dá na stack memory.

TODO: pesquisar mais sobre stack memory e heap memory