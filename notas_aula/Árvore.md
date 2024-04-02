```c
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
```

Vejamos o código acima, a função rec é chamada [recursivamente](Recursão.md), e cria uma árvore da seguinte forma:

![[Pasted image 20240304222408.png]]

Se olharmos a saída do terminal, talvez fiquemos confusos no primeiro momento, entretanto, pense que quando a rec(2) é chamada ela adiciona na stack duas chamadas de rec(1), entretanto uma delas vai ser executada primeiro que a outra, a que for executada vai chamar duas vezes rec(0) e assim que rec(0) é chamado ele retorna imediatamente. Assim a árvore se forma como uma espécie de DFS

```bash
stack sendo criada 0x16f77362c 2
stack sendo criada 0x16f7735fc 1
stack sendo criada 0x16f7735cc 0
stack sendo retornada 0x16f7735cc 0
stack sendo criada 0x16f7735cc 0
stack sendo retornada 0x16f7735cc 0
stack sendo retornada 0x16f7735fc 1
stack sendo criada 0x16f7735fc 1
stack sendo criada 0x16f7735cc 0
stack sendo retornada 0x16f7735cc 0
stack sendo criada 0x16f7735cc 0
stack sendo retornada 0x16f7735cc 0
stack sendo retornada 0x16f7735fc 1
stack sendo retornada 0x16f77362c 2
```

Se você esta confuso no porque a árvore ocupa O(N) sempre, pense em um vetor, ele ocupa O(N) independente de quantos valores tem nele, como aqui estamos apenas criando uma árvore, sem cópias, a complexidade de espaço é O(N). Note ademais que se por exemplo se fizermos rec(1), teremos três nós no total, o da raiz e dois rec(0), digamos também que cada chamada ocupe 1 de espaço, quando estamos no rec(1), ocupamos 1, ao chamarmos rec(0) o espaço ocupado vai pra 2, porém, essa função retorna imediatamente, o que faz o espaço ocupado voltar a ser 1, isso acontece novamente para o outro nó e por fim o nó da raiz retorna e ocupamos 0 de espaço.

