# Atividade Avaliativa 3 — Dicionário com Tabela Hash em C

Sistema de dicionário (palavra → definição) feito em linguagem C usando
**tabela hash** com tratamento de colisões por **encadeamento separado**
(listas encadeadas em cada posição da tabela).

Equipe: **Andrey Fogaça**, **Brayan Gabriel Biscaia**, **Matheus Saraiva Faustin**.

---

## Por que está tudo em um único arquivo

A versão principal de entrega (`dicionario_hash.c`) reúne **todo o código
num só arquivo**. O motivo é prático: compiladores online como o OnlineGDB
compilam e executam **um arquivo por vez**.

Se a gente dividisse o código em vários arquivos (por exemplo, um `.h` com
as definições, um `.c` com a implementação e outro `.c` com o menu), seria
preciso compilar e linkar os arquivos juntos. Localmente isso é simples,
mas no compilador online dá trabalho e costuma gerar erro de *"undefined
reference"*, porque ele tenta compilar só o arquivo principal e não
encontra as funções que estão nos outros.

Juntando tudo num arquivo só, basta **colar e clicar em Run**, sem
configuração nenhuma. Por isso essa é a versão que usamos para gravar e
testar no vídeo.

Mantivemos também uma versão organizada em três arquivos
(`dicionario.h`, `dicionario.c` e `main.c`), que serve para mostrar a
separação de responsabilidades do código e pode ser usada em um ambiente
com compilação local. As duas versões têm exatamente o mesmo
comportamento.

---

## Operações

- **Inserir**: calcula o índice e percorre a lista do bucket. Se a palavra
  já existe, atualiza a definição. Se é nova e o bucket já estava ocupado,
  conta uma colisão e encadeia o nó novo no início da lista.
- **Buscar**: calcula o índice e percorre a lista comparando as palavras
  com `strcmp`. Retorna a definição ou indica que não encontrou.
- **Remover**: localiza o nó, religa o anterior ao próximo e libera a
  memória com `free`.
- **Exibir tabela**: percorre todos os buckets e mostra as palavras de
  cada um, deixando as colisões visíveis.
- **Liberar memória**: ao sair, percorre tudo e dá `free` em cada nó, no
  vetor e na tabela, sem deixar vazamentos.

---

## Estatísticas exibidas

| Estatística | Como é calculada |
|-------------|------------------|
| Quantidade de elementos | Contador atualizado a cada inserção/remoção |
| Quantidade de colisões | Incrementado quando uma palavra nova cai em bucket já ocupado |
| Fator de carga | `qtdElementos / tamanho` (média de elementos por bucket) |
| Maior lista encadeada | Comprimento da maior lista entre todos os buckets |
