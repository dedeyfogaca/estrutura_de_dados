## Parte 1 – Tipos de Árvores

### AVL

A AVL é uma BST que se equilibra sozinha. O nome vem dos pesquisadores que criaram ela em 1962, Adelson-Velsky e Landis. A regra é simples: cada nó tem um "fator de balanceamento", que é a altura da subárvore da esquerda menos a da direita. Esse fator só pode ser -1, 0 ou 1. Se passar disso depois de uma inserção ou remoção, a árvore faz uma rotação pra voltar ao normal.

A vantagem é que, como ela nunca fica torta, busca e inserção são sempre O(log n), mesmo no pior caso. Isso deixa as buscas bem rápidas e previsíveis.

A desvantagem é que, pra manter esse equilíbrio tão rígido, ela acaba fazendo bastante rotação na inserção e na remoção, e ainda precisa guardar a altura de cada nó.

Exemplo: se você inserir 10, 20 e 30 nessa ordem, a árvore pende toda pra direita e o nó 10 fica com fator -2. Uma rotação à esquerda resolve:

```
Antes (torta)              Depois da rotação à esquerda
   10                            20
     \                          /  \
      20          →           10   30
        \
         30
```

### Rubro-Negra

A ideia aqui é parecida com a da AVL (manter a árvore equilibrada), mas em vez de medir altura ela pinta cada nó de vermelho ou preto e segue umas regras de cor. Com essas regras, nenhum caminho da raiz até a folha consegue ser mais que o dobro de outro, então a árvore fica "mais ou menos balanceada".

As regras de cor são:

- todo nó é vermelho ou preto;
- a raiz é sempre preta;
- folha nula (NIL) conta como preta;
- nó vermelho não pode ter filho vermelho (nada de dois vermelhos seguidos);
- todo caminho de um nó até as folhas tem a mesma quantidade de nós pretos.

A vantagem é que ela equilibra com menos rotação que a AVL, então rende melhor quando tem muita inserção e remoção. É por isso que ela aparece dentro de várias bibliotecas de linguagem de programação.

A desvantagem é que ela é bem mais chata de implementar por causa do controle de cor, e como o balanceamento é só aproximado a busca pode ser um pouquinho mais lenta que a da AVL.

Exemplo de uma rubro-negra válida, com (P) pra preto e (R) pra vermelho:

```
        20(P)
       /     \
    10(R)     30(R)
   /   \      /   \
  5(P) 15(P) 25(P) 35(P)
```

A raiz é preta, não tem dois vermelhos seguidos e todos os caminhos têm a mesma quantidade de pretos.

### N-ária

Diferente das outras, na n-ária um nó pode ter vários filhos, não só dois. Por causa disso ela é boa pra representar hierarquia, tipo uma pasta com várias subpastas.

A diferença pra binária é direta: na binária o nó tem no máximo 2 filhos e a busca segue o "menor à esquerda, maior à direita". Na n-ária não tem esse limite, e a organização depende da aplicação. Normalmente cada nó guarda uma lista de filhos em vez de dois ponteiros fixos.

A vantagem é representar hierarquia de um jeito natural, com a flexibilidade de cada nó ter quantos filhos precisar. A desvantagem é que, se não tiver um esquema de balanceamento, a busca pode ficar lenta, e mexer nela costuma ser mais complicado que na binária.

Exemplo, um pedaço de um sistema de arquivos:

```
            / (raiz)
          /   |    \
       home  etc   usr
       /  \          |
    ana  bruno      bin
```

Onde ela aparece na prática: sistema de arquivos, estrutura de página HTML (o DOM, onde uma tag contém várias outras), organograma de empresa, e as árvores B/B+ que os bancos de dados usam nos índices.
