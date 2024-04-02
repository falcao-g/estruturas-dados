Tabela hash (dispersão/espalhamento), é uma técnica com o objetivo de fazer busca, inserção e remoção em O(1).

Para isso, implementaremos uma função hash, que vai converter valores para um índice em um array, por exemplo, "senha" -> 5. Precisamos tomar cuidado ao escolher uma função hash, já que se escolhermos uma ingênua que atribui valores como a -> 1, b -> 2, c -> 3... e somar tudo no final, as strings "abc" e "cba" darão o mesmo resultado, isso é uma colisão.

# Sondagem linear

Esse é o método mais simples de trabalhar com uma tabela hash, se dois elementos resultam no mesmo índice, o novo elemento simplesmente é colocado no índice seguinte disponível

Os espaços do vetor são chamados de buckets, quando temos muitos elementos ocupando índices adjacentes chamamos isso de clusters, isso é ruim, vejamos o porque.

Para executar a busca por um elemento, vamos até o índice correspondente e caso ele não esteja lá, andamos em frente até achar o elemento ou um "buraco" (espaço vazio) no vetor, por isso clusters são ruins e queremos evitá-los.

Para a remoção, trocamos o valor daquela posição por um elemento que nunca vai aparecer no nosso conjunto de elementos.

Note que o cálculo do índice pode ser representado por: `h(k, i) = (h(k) + i) mod m`, onde k é o elemento, h a função hash, i o número de tentativas e m o número de buckets, isso só representa o que já falamos antes, colocamos o elemento no índice que a função hash nos deu e caso ele já esteja ocupado, adicionamos mais 1 até achar um espaço vazio.
![[Pasted image 20240323215439.png]]

> Caso médio: O(1)
> Pior caso: O(n)
# Hash duplo

Se trata de uma estratégia alternativa para evitar a formação de clusters no nosso array, ao invés de somarmos o número de tentativas quando ocorre uma colisão, somamos o número de tentativas multiplicado pela função hash, a fórmula fica assim: `h(k, i) = (h1(k) + i * h2(k)) mod m`.

![[Pasted image 20240323215946.png]]

> Caso médio: O(1)
> Pior caso: O(n)

# Endereçamento separado

A maneira de armazenar um elemento em cada índice também é chamada de endereçamento aberto, nessa nova estratégia, quando adicionamos um elemento a um novo índice, criamos uma lista encadeada com esse elemento, agora se uma colisão acontecer, adicionamos esse elemento novo a lista encadeada, isso diminui ainda mais os clusters de dados

> Caso médio: O(1)
> Pior caso: O(n)

![[Pasted image 20240323220601.png]]