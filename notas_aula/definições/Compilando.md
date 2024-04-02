Tem muita flag mas a maioria vai muito além de o que faremos, aqui estão algumas úteis:

Se você alguma vez fez só:

```bash
gcc arquivo.c
```

Você vai perceber que o arquivo é compilado e a saída dele é armazenado em um arquivo a.out, para definir o nome do arquivo de saída usamos a flag `-o`:

```bash
gcc -o arquivo arquivo.c
```

Agora a saída é escrita em um arquivo chamado "arquivo".

A flag `-Wall` serve para mostrar avisos na compilação, por exemplo o seguinte código:

```c
#include<stdio.h>

int main(void)
{
   int i;
   printf("\n maluquisse [%d]\n", i);
   return 0;
}
```

Se usarmos a flag `-Wall` aqui veremos um aviso nos avisando que a variável i foi inicializada, ou seja, estamos usando o valor dela mas o valor dela é um lixo, um valor qualquer. Inclusive se usarmos `-Werror`, os avisos são tratados como erros e é impossível compilar enquanto não forem resolvidos

A flag `-pedantic` faz o compilador irá emitir avisos adicionais para garantir que seu código esteja em conformidade com os padrões ANSI/ISO C ou C++, dependendo do idioma que você está utilizando. Serve para garantir que o código esteja em conformidade com os padrões da linguagem C ou C++ de forma mais estrita, ajudando a evitar problemas potenciais e a escrever um código mais limpo e portável.

Por fim se tivermos um arquivo de texto chamado "Flags" por exemplo, podemos fazer o comando: `gcc arquivo.c @Flags`e o conteúdo dele vai ser tratado como nossas flags, o que é no mínimo interessante