## Parte 4 – Comparação entre Estruturas

| Estrutura | Nº Máximo de Filhos | Balanceamento | Complexidade de Busca | Complexidade de Inserção | Vantagem Principal | Desvantagem Principal | Exemplo de Aplicação |
| --- | --- | --- | --- | --- | --- | --- | --- |
| BST | 2 | Não possui balanceamento automático. Pode ficar desbalanceada conforme a ordem de inserção. | O(log n) no melhor caso e O(n) no pior caso | O(log n) no melhor caso e O(n) no pior caso | Estrutura simples de entender e implementar | Pode perder desempenho se ficar desbalanceada | Árvores de busca básicas |
| AVL | 2 | Sim. Mantém o fator de balanceamento com rotações | O(log n) | O(log n) | Busca previsível e eficiente | Inserção e remoção são mais custosas por causa das rotações | Índices e estruturas que exigem leitura frequente |
| Rubro-Negra | 2 | Sim. Usa coloração e rotações para manter o balanceamento aproximado | O(log n) | O(log n) | Balanceamento eficiente com menos rotações que a AVL | Implementação mais complexa | Bibliotecas e estruturas internas de sistemas |
| N-ária | N (vários filhos) | Pode ou não possuir mecanismos de balanceamento, dependendo da variação | O(log n) em estruturas balanceadas, mas depende da aplicação | O(log n) ou proporcional à estrutura da árvore | Representa melhor hierarquias com muitos filhos | Não é tão simples quanto a árvore binária em alguns contextos | Sistema de arquivos, menus e taxonomias |

Explicando o que tá na tabela:

**Número de filhos.** BST, AVL e rubro-negra são todas binárias, então no máximo 2 filhos por nó. A n-ária é a única que permite vários.

**Balanceamento.** A BST não tem nenhum, e é justamente por isso que ela pode desbalancear. A AVL faz balanceamento rígido (fator mais rotação). A rubro-negra faz aproximado (cor mais rotação), que é mais leve. A n-ária depende da variação: a árvore B, por exemplo, é uma n-ária balanceada.

**Busca.** Nas balanceadas é sempre O(log n) porque a altura fica controlada. Na BST é O(log n) no melhor caso, mas vira O(n) se ela desbalancear.

**Inserção.** Mesma lógica da busca, porque pra inserir você primeiro tem que achar o lugar certo. Um detalhe: mesmo as duas sendo O(log n), a AVL roda mais que a rubro-negra na hora de inserir.

**Vantagem principal.** A BST ganha na simplicidade. A AVL ganha na busca rápida e previsível. A rubro-negra ganha por equilibrar com menos esforço. A n-ária ganha por representar hierarquia com muitos filhos.

**Desvantagem principal.** A BST pode ficar lenta se desbalancear. A AVL gasta muito em rotação. A rubro-negra é difícil de implementar. A n-ária é mais complicada de mexer.

**Exemplo de uso.** BST em caso didático, AVL quando tem muita leitura e pouca alteração, rubro-negra dentro de bibliotecas e sistemas, e n-ária em sistema de arquivos, menu e índice de banco (árvore B/B+).
