## Parte 3 – Aplicação Prática

Escolhi índice de banco de dados.

Banco de dados precisa achar registro rápido mesmo com milhões de linhas, e pra isso ele cria índices em vez de varrer a tabela inteira a cada consulta. Esses índices são montados em cima de árvore balanceada.

Se fosse uma BST normal ia dar problema. Campo de ID quase sempre entra em ordem crescente, e BST recebendo dado em ordem crescente vira praticamente uma lista, com busca O(n). Péssimo pra um banco.

A rubro-negra resolve isso porque mantém o equilíbrio com pouca rotação, e o banco faz inserção e remoção o tempo todo, não só busca. Na vida real os bancos usam uma variação n-ária balanceada, a árvore B (ou B+), porque cada nó guarda várias chaves de uma vez. Isso deixa a árvore mais baixa e, principalmente, reduz o número de acessos ao disco, que é a parte mais lenta de tudo.

Resumindo a justificativa:

- **Desempenho:** busca e inserção O(log n) garantido, então não trava conforme a base cresce.
- **Organização:** as chaves ficam ordenadas, então busca por intervalo (tipo "clientes de 20 a 30 anos") também fica rápida.
- **Operações:** como o banco faz busca, inserção e remoção direto, todas precisam ser rápidas, e não só a busca. É por isso que uma árvore balanceada ganha de uma BST simples nesse caso.
