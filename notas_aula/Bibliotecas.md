Para criar uma biblioteca, igual as que importamos com `#include <algo.h>`, primeiro precisamos criar um arquivo .h ou um arquivo header, que guarda as definições das funções da biblioteca, vamos então criar um arquivo `heap.h`:

```c
#ifndef __HEAP__
#define __HEAP__

int pai(int n);
#endif
```

Aqui usamos `ifndef` para executar esse código só quando a variável `__HEAP__` não estiver definida, ou seja, esse código só será executado uma vez, para garantir que as funções não sejam definidas mais de uma vez.

Agora criamos um arquivo `heap.c`, que é onde nós colocamos os códigos das funções que definimos anteriormente:

```c
#include "heap.h"

int pai(int n) {
    int ret;
    if (n == 0) {
    	ret = 0;
    } else {
    	ret = (n - 1) / 2;
    }
    return ret;
}
```

Note que usamos o include com "", isso indica que estamos referenciando uma biblioteca que nós criamos localmente, e não uma das nativas do C.

Agora sim, podemos usar a função `pai` em qualquer arquivo, vamos exemplificar com um arquivo `main.c`:

```C
#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

int main(void) {
	printf("pai de %d é %d", 2, pai(2));
	
	return EXIT_SUCCESS;
}
```

Para testar se está funcionando, compilamos os arquivos main.c e heap.c juntos da seguinte forma: `gcc main.c heap.c -o main`.

Isso é muito legal, mas não é exatamente uma biblioteca, vejamos então como criar uma:

# Biblioteca estática

Uma biblioteca estática é integrada junto do código, isso faz com que o tamanho do arquivo compilado seja maior, já que a biblioteca está junto, e caso um erro seja encontrado no código dela, os arquivos tem que ser todos re-compilados.

Para criar uma, primeiro executamos:

```bash
gcc -fpic -c heap.c
```

Isso cria um arquivo `.o` ou um *object-file*.

Agora precisamos executar o seguinte:

```bash
ar -rcs libfacom.a heap.o
```

Isso cria um arquivo `.a` (archive),  que é o arquivo da biblioteca estática propriamente dita, note que colocamos o nome dele como `libfacom`, você pode escolher qualquer nome, desde que ele **comece com lib**, caso contrário não vai funcionar.

Agora para compilar nosso código fazemos:

```bash
gcc -L. -o main main.c -lfacom
```

Usamos `-L.` para indicar que vamos usar uma biblioteca junto e `-lfacom` para referenciar a biblioteca.

Lembre que essa é uma biblioteca estática, então qualquer mudança na biblioteca, o arquivos arquivos `.o` e depois `.a` precisam ser recriados e o código que a usa também precisa ser recompilado.

# Bibliotecas dinâmicas

No caminho contrário, temos as bibliotecas dinâmicas, que só são referenciadas pelo nosso código, assim se o código da biblioteca mudar, não precisamos recompilar tudo, somente a biblioteca.

Para criar uma começamos da mesma forma, criando um arquivo `.o`:

```bash
gcc -fpic -c heap.c
```

Ao invés de um arquivo `.a`, precisamos criar um arquivo `.so` (shared object):

```bash
gcc -shared -o libfacom.so heap.o
```

Sempre nos lembrando da restrição do nome começar com "lib".

Como estamos trabalhando com uma biblioteca dinâmica, nosso código precisa "enxergar" ela, para isso:

```bash
export LD_LIBRARY_PATH="/caminho/para/a/pasta/onde/ta/a/lib"
```

Por fim, para compilar nosso código que usa a lib:

```bash
gcc -L. -o main main.c -lfacom
```

Como dito anteriormente, se precisarmos mudar o comportamento da biblioteca, basta alterar o código dela e compilar ela novamente, automaticamente todos os arquivos que a referenciam usaram o novo código (por ser uma referência).
