Heap ou Lista de Prioridade, é uma estrutura baseada em [árvore](Árvore.md), onde essa árvore é uma [árvore binária completa](Árvore%20Binária%20Completa), o objetivo dessa estrutura é acessar o maior (ou menor) valor em O(1).

Temos dois tipos de Heap, Min-Heap e Max-Heap:

# Max-Heap:

Nesse heap, cada nó pai é maior que seus filhos, isso é válido para todos os nós da árvore:

> O número total de comparações necessárias no max-heap é baseado na altura da árvore. A altura da árvore binária completa é sempre log n, então a complexidade também será O(log n).

# Min-Heap:

Nesse heap, cada nó pai é menor que seus filhos, isso é válido para todos os nós da árvore:

> O número total de comparações necessárias no min-heap é baseado na altura da árvore. A altura da árvore binária completa é sempre log n, então a complexidade também será O(log n).

![[Pasted image 20240317210649.png]]

# Operações

A Heap é construída a partir de um vetor, para isso precisamos criar a função `desce`, porém, precisamos primeiro de uma maneira de encontrar o pai, filho esquerdo e filho direito de um dado nó, segue a implementação dessas funções na linguagem C:

```C
int pai(int n) {
    return ((n - 1) / 2);
}

int filho_esq(int n) {
    return (n * 2 + 1);
}

int filho_dir(int n) {
    return (n * 2 + 2);
}
```

Agora sim podemos implementar a `desce`, ela será responsável por analisar se um nó n é menor que um de seus filhos, se ele for, eles trocam de lugar e chamamos a função recursivamente na posição trocada: 

```C
void desce(int v[], int tam, int n) {
    int maior = n;
    int esq = filho_esq(n);
    int dir = filho_dir(n);

    if (v[esq] > v[maior] && esq < tam)
        maior = esq;
    if (v[dir] > v[maior] && dir < tam)
        maior = dir;

    if (maior != n) {
        troca(&v[maior], &v[n]);
        desce(v, tam, maior);
    }
}
```

Note que aqui estamos seguindo a `max-heap`, caso queira uma min-heap, basta analisar se os filhos são menores que o pai, perceba também que adicionamos uma condição que `esq` e `dir` devem ser menores que o tamanho do vetor, caso contrário a função começaria a analisar valores sem sentido.

Agora sim! Estamos prontos para construir uma heap a partir de qualquer vetor, para isso, chamamos desce para todos os nós acima da última linha:

```C
void constroi_heap(int v[], int tam) {
    for (int n = pai(tam); n >= 0; n--)
        desce(v, tam, n);
}
```

Pronto! Sua heap está construída, agora podemos finalmente criar as funções para as quais essa estrutura foi criada, `acessa_max` e `extrai_max`:

```C
int acessa_max(int v[]) {
    return v[0];
}

int extrai_max(int v[], int *tam) {
    int max = v[0];
    *tam -= 1;
    v[0] = v[*tam];
    desce(v, *tam, 0);
    return max;
}
```

Acessar o maior valor é trivial, basta retornar o primeiro elemento do vetor, já que a estrutura nos garante que esse é sempre o caso, agora note que `extrai_max` te devolve o resultado e remove aquele valor do vetor. Como não podemos realmente remover um valor, simplesmente copiamos o último elemento para a primeira posição e "diminuímos" o tamanho dele, isso, é claro, vai quebrar nossa estrutura, para consertar chamamos a função desce na primeira posição.

Já temos a função `desce`, mas agora precisamos implementar a `sobe`, para podermos executar as outras operações, essa função pega um nó n e compara se existe a necessidade de trocá-lo de lugar com o seu pai, e caso a troca seja feita, ela é chamada recursivamente:

```C
void sobe(int v[], int n) {
    int p = pai(n);
    if (v[p] < v[n]) {
        troca(&v[p], &v[n]);
        sobe(v, p);
    }
}
```

No momento não temos como inserir novos elementos depois da estrutura ter sido criada, criemos então a função `insere_elemento`:

```C
int insere_elemento(int v[], int *tam, int max, int valor) {
    if (*tam == max)
        return EXIT_FAILURE;

    v[*tam] = valor;
    sobe(v, *tam);
    *tam += 1;

    return EXIT_SUCCESS;
}
```

Note que inserimos um novo valor caso o vetor possua espaço disponível, caso contrário a função retorna a constante [EXIT_FAILURE](Constantes.md).

Mas digamos que queremos alterar um valor já existente na nossa estrutura, para isso, vamos criar a função `altera_prioridade`:

```C
void altera_prioridade(int v[], int tam, int n, int valor) {
    int aux = v[n];
    v[n] = valor;

    if (v[n] > aux)
        sobe(v, n);
    if (v[n] < aux)
        desce(v, tam, n);
}
```

A ideia aqui é simples, trocamos o valor no índice indicado, e caso o novo valor seja maior que o anterior, chamamos sobe, se não, chamamos desce.

Tem outra operação muito interessante que podemos fazer com uma estrutura heap, podemos usar um algoritmo de ordenação chamado `heapsort`.

A ideia por trás do heap sort é a seguinte:

- Troque o valor do primeiro elemento com o último (assim já ordenando o maior valor na última posição)
- "Diminua" o tamanho do vetor em 1 (para não mexer no valor que já está correto)
- Chame a função desce para a primeira posição (para termos a garantia que a estrutura está correta novamente)

E repita até que o tamanho seja 0.

```C
void heap_sort(int v[], int tam) {
    for (int i = tam - 1; i > 0; i--) {
        troca(&v[0], &v[i]);
        desce(v, i, 0);
    }
}
```

A complexidade de tempo desse algoritmo é O(log n) e O(1) em complexidade de espaço, vale adicionar que o heapsort é considerado um algoritmo de ordenação instável, isso porque, quando ordenamos objetos com a mesma chave, a ordem original não é preservada.