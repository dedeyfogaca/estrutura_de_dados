#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_TABELA 7   /* tabela pequena de proposito, para mostrar colisoes */
#define TAM_BUFFER 256

/* ================== ESTRUTURAS ================== */

/* Cada registro guarda palavra + definicao; "prox" encadeia colisoes. */
typedef struct No
{
    char *palavra;
    char *definicao;
    struct No *prox;
} No;

/* Vetor de buckets + contadores para as estatisticas. */
typedef struct TabelaHash
{
    No **buckets;
    int tamanho;
    int qtdElementos;
    int qtdColisoes;
} TabelaHash;

/* ================== AUXILIARES ================== */

/* Duplica uma string em memoria alocada dinamicamente. */
static char *duplicarString(const char *origem)
{
    size_t tamanho = strlen(origem) + 1;
    char *copia = malloc(tamanho);
    if (copia == NULL)
    {
        fprintf(stderr, "Erro: falha ao alocar memoria para string.\n");
        exit(EXIT_FAILURE);
    }
    memcpy(copia, origem, tamanho);
    return copia;
}

/* Cria um no com palavra e definicao ja copiadas. */
static No *criarNo(const char *palavra, const char *definicao)
{
    No *novo = malloc(sizeof(No));
    if (novo == NULL)
    {
        fprintf(stderr, "Erro: falha ao alocar memoria para no.\n");
        exit(EXIT_FAILURE);
    }
    novo->palavra = duplicarString(palavra);
    novo->definicao = duplicarString(definicao);
    novo->prox = NULL;
    return novo;
}

/* ================== TABELA HASH ================== */

/* Cria a tabela com "tamanho" buckets, todos vazios. */
TabelaHash *criarTabela(int tamanho)
{
    if (tamanho <= 0)
        tamanho = 1;

    TabelaHash *tabela = malloc(sizeof(TabelaHash));
    if (tabela == NULL)
    {
        fprintf(stderr, "Erro: falha ao alocar memoria para a tabela.\n");
        exit(EXIT_FAILURE);
    }

    tabela->buckets = calloc((size_t)tamanho, sizeof(No *));
    if (tabela->buckets == NULL)
    {
        fprintf(stderr, "Erro: falha ao alocar memoria para os buckets.\n");
        free(tabela);
        exit(EXIT_FAILURE);
    }

    tabela->tamanho = tamanho;
    tabela->qtdElementos = 0;
    tabela->qtdColisoes = 0;
    return tabela;
}

/* Funcao hash djb2: hash = hash*33 + caractere, comecando em 5381. */
unsigned long funcaoHash(const char *palavra)
{
    unsigned long hash = 5381;
    int c;
    while ((c = (unsigned char)*palavra++) != 0)
        hash = ((hash << 5) + hash) + (unsigned long)c;
    return hash;
}

/* Converte o hash em indice valido dentro da tabela. */
int indiceHash(TabelaHash *tabela, const char *palavra)
{
    return (int)(funcaoHash(palavra) % (unsigned long)tabela->tamanho);
}

/* Insere/atualiza uma palavra. Conta colisao quando o bucket ja tinha no. */
void inserir(TabelaHash *tabela, const char *palavra, const char *definicao)
{
    int indice = indiceHash(tabela, palavra);
    No *atual = tabela->buckets[indice];

    while (atual != NULL)
    {
        if (strcmp(atual->palavra, palavra) == 0)
        {
            free(atual->definicao);
            atual->definicao = duplicarString(definicao);
            printf("  > Palavra \"%s\" ja existia. Definicao atualizada.\n", palavra);
            return;
        }
        atual = atual->prox;
    }

    if (tabela->buckets[indice] != NULL)
        tabela->qtdColisoes++;

    No *novo = criarNo(palavra, definicao);
    novo->prox = tabela->buckets[indice];
    tabela->buckets[indice] = novo;
    tabela->qtdElementos++;

    printf("  > Palavra \"%s\" inserida no bucket [%d].\n", palavra, indice);
}

/* Busca uma palavra; retorna a definicao ou NULL. */
const char *buscar(TabelaHash *tabela, const char *palavra)
{
    int indice = indiceHash(tabela, palavra);
    No *atual = tabela->buckets[indice];

    while (atual != NULL)
    {
        if (strcmp(atual->palavra, palavra) == 0)
            return atual->definicao;
        atual = atual->prox;
    }
    return NULL;
}

/* Remove uma palavra; retorna 1 se removeu, 0 se nao encontrou. */
int remover(TabelaHash *tabela, const char *palavra)
{
    int indice = indiceHash(tabela, palavra);
    No *atual = tabela->buckets[indice];
    No *anterior = NULL;

    while (atual != NULL)
    {
        if (strcmp(atual->palavra, palavra) == 0)
        {
            if (anterior == NULL)
                tabela->buckets[indice] = atual->prox;
            else
                anterior->prox = atual->prox;

            free(atual->palavra);
            free(atual->definicao);
            free(atual);
            tabela->qtdElementos--;
            return 1;
        }
        anterior = atual;
        atual = atual->prox;
    }
    return 0;
}

/* Exibe a tabela inteira, bucket por bucket. */
void exibirTabela(TabelaHash *tabela)
{
    printf("\n=============== TABELA HASH ===============\n");
    for (int i = 0; i < tabela->tamanho; i++)
    {
        printf("[%2d] ", i);
        No *atual = tabela->buckets[i];

        if (atual == NULL)
        {
            printf("(vazio)\n");
            continue;
        }

        while (atual != NULL)
        {
            printf("-> {%s: %s} ", atual->palavra, atual->definicao);
            atual = atual->prox;
        }
        printf("\n");
    }
    printf("===========================================\n");
}

/* Exibe as estatisticas obrigatorias. */
void exibirEstatisticas(TabelaHash *tabela)
{
    int maiorLista = 0;
    int bucketsOcupados = 0;
    for (int i = 0; i < tabela->tamanho; i++)
    {
        int comprimento = 0;
        for (No *atual = tabela->buckets[i]; atual != NULL; atual = atual->prox)
            comprimento++;

        if (comprimento > 0)
            bucketsOcupados++;
        if (comprimento > maiorLista)
            maiorLista = comprimento;
    }

    double fatorCarga = (double)tabela->qtdElementos / (double)tabela->tamanho;

    printf("\n----------- ESTATISTICAS DA TABELA -----------\n");
    printf("Tamanho da tabela (buckets) : %d\n", tabela->tamanho);
    printf("Quantidade de elementos     : %d\n", tabela->qtdElementos);
    printf("Quantidade de colisoes      : %d\n", tabela->qtdColisoes);
    printf("Buckets ocupados            : %d\n", bucketsOcupados);
    printf("Fator de carga              : %.2f\n", fatorCarga);
    printf("Maior lista encadeada       : %d\n", maiorLista);
    printf("----------------------------------------------\n");
}

/* Libera toda a memoria. */
void liberarTabela(TabelaHash *tabela)
{
    if (tabela == NULL)
        return;

    for (int i = 0; i < tabela->tamanho; i++)
    {
        No *atual = tabela->buckets[i];
        while (atual != NULL)
        {
            No *prox = atual->prox;
            free(atual->palavra);
            free(atual->definicao);
            free(atual);
            atual = prox;
        }
    }
    free(tabela->buckets);
    free(tabela);
}

/* ================== MENU / MAIN ================== */

/* Le uma linha do teclado e remove o '\n' do final. */
static int lerLinha(char *buffer, int tamanho)
{
    if (fgets(buffer, tamanho, stdin) == NULL)
        return 0;
    buffer[strcspn(buffer, "\n")] = '\0';
    return 1;
}

static void exibirMenu(void)
{
    printf("\n========= DICIONARIO (TABELA HASH) =========\n");
    printf("1 - Inserir palavra e definicao\n");
    printf("2 - Buscar palavra\n");
    printf("3 - Remover palavra\n");
    printf("4 - Exibir tabela hash\n");
    printf("5 - Exibir estatisticas\n");
    printf("0 - Sair\n");
    printf("============================================\n");
    printf("Escolha uma opcao: ");
}

int main(void)
{
    TabelaHash *dicionario = criarTabela(TAMANHO_TABELA);
    char opcaoTexto[TAM_BUFFER];
    char palavra[TAM_BUFFER];
    char definicao[TAM_BUFFER];

    printf("Dicionario com Tabela Hash iniciado (%d buckets).\n", TAMANHO_TABELA);

    while (1)
    {
        exibirMenu();

        if (!lerLinha(opcaoTexto, TAM_BUFFER))
            break;

        int opcao = atoi(opcaoTexto);

        if (opcao == 0)
        {
            printf("\nEncerrando o programa...\n");
            break;
        }
        else if (opcao == 1)
        {
            printf("Digite a palavra: ");
            if (!lerLinha(palavra, TAM_BUFFER) || palavra[0] == '\0')
            {
                printf("  > Palavra invalida.\n");
                continue;
            }
            printf("Digite a definicao: ");
            if (!lerLinha(definicao, TAM_BUFFER))
                definicao[0] = '\0';

            inserir(dicionario, palavra, definicao);
        }
        else if (opcao == 2)
        {
            printf("Digite a palavra para buscar: ");
            if (!lerLinha(palavra, TAM_BUFFER))
                break;

            const char *resultado = buscar(dicionario, palavra);
            if (resultado != NULL)
                printf("  > \"%s\": %s\n", palavra, resultado);
            else
                printf("  > Palavra \"%s\" nao encontrada.\n", palavra);
        }
        else if (opcao == 3)
        {
            printf("Digite a palavra para remover: ");
            if (!lerLinha(palavra, TAM_BUFFER))
                break;

            if (remover(dicionario, palavra))
                printf("  > Palavra \"%s\" removida com sucesso.\n", palavra);
            else
                printf("  > Palavra \"%s\" nao encontrada.\n", palavra);
        }
        else if (opcao == 4)
        {
            exibirTabela(dicionario);
        }
        else if (opcao == 5)
        {
            exibirEstatisticas(dicionario);
        }
        else
        {
            printf("  > Opcao invalida. Tente novamente.\n");
        }
    }

    liberarTabela(dicionario);
    return 0;
}
