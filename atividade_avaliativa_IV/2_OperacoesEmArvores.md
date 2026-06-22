## Parte 2 – Operações em Árvores

### Rotação simples à direita

Serve pra arrumar a árvore quando ela pendeu demais pra esquerda. Acontece no caso LL: o nó ficou com fator +2 e o problema veio do filho esquerdo do filho esquerdo. A rotação puxa o filho da esquerda pra cima.

Exemplo, inserindo 30, 20 e 10:

```
Antes                      Depois
      30                     20
     /                      /  \
    20          →         10   30
   /
  10
```

### Rotação simples à esquerda

É o espelho da de cima. Arruma quando a árvore pendeu pra direita (caso RR: fator -2 vindo do filho direito do filho direito).

Exemplo:

```
Antes                      Depois
   10                        20
     \                      /  \
      20          →       10   30
        \
         30
```

### Rotação dupla

Quando o desequilíbrio é em "zigue-zague", uma rotação só não resolve, aí precisa de duas.

A LR (esquerda-direita) acontece quando o problema tá no filho direito do filho esquerdo. Primeiro você roda o filho pra esquerda, depois roda a raiz pra direita. Inserindo 30, 10 e 20:

```
Inicial         Roda o 10            Roda o 30
                pra esquerda         pra direita

   30               30                    20
  /               /                      /  \
 10       →     20            →       10   30
   \           /
    20        10
```

A RL (direita-esquerda) é o contrário: o problema tá no filho esquerdo do filho direito. Primeiro roda o filho pra direita, depois a raiz pra esquerda. Inserindo 10, 30 e 20:

```
Inicial         Roda o 30            Roda o 10
                pra direita          pra esquerda

 10               10                    20
   \                \                  /  \
    30      →        20        →     10   30
   /                   \
  20                    30
```

### Inversão (espelhamento)

Aqui você troca o filho da esquerda pelo da direita em todos os nós, de forma recursiva. No fim a árvore vira a imagem dela no espelho.

Onde se usa: é uma questão clássica de entrevista pra testar recursão, aparece em processamento de imagem (quando você quer espelhar) e serve pra checar se uma árvore é simétrica (ela é simétrica se for igual à versão espelhada).

Exemplo:

```
Original                 Espelhada
     4                      4
    / \                    / \
   2   6        →         6   2
  / \ / \                / \ / \
 1  3 5  7              7  5 3  1
```

Cada nó teve o filho da esquerda trocado pelo da direita.
