#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No *prox;
} No;

void inserirFim(No **head, int valor) {
    No *novo = (No*) malloc(sizeof(No));
    novo->valor = valor;
    novo->prox = NULL;

    if (*head == NULL) {
        *head = novo;
        return;
    }

    No *atual = *head;
    while (atual->prox != NULL) {
        atual = atual->prox;
    }
    atual->prox = novo;
}

void exibirLista(No *head) {
    No *atual = head;
    while (atual != NULL) {
        printf("%d -> ", atual->valor);
        atual = atual->prox;
    }
    printf("NULL\n");
}

void liberarLista(No **head) {
    No *atual = *head;
    while (atual != NULL) {
        No *temp = atual;
        atual = atual->prox;
        free(temp);
    }
    *head = NULL;
}

void inserirPosicao(No **head, int valor, int posicao) {
    if (posicao < 0) {
        printf("Erro: posicao invalida.\n");
        return;
    }

    No *novo = (No*) malloc(sizeof(No));
    novo->valor = valor;
    novo->prox = NULL;

    if (posicao == 0) {
        novo->prox = *head;
        *head = novo;
        return;
    }

    No *atual = *head;
    int i = 0;
    while (atual != NULL && i < posicao - 1) {
        atual = atual->prox;
        i++;
    }

    if (atual == NULL) {
        printf("Erro: posicao %d invalida.\n", posicao);
        free(novo);
        return;
    }

    novo->prox = atual->prox;
    atual->prox = novo;
}

int buscarValor(No *head, int valor) {
    No *atual = head;
    int posicao = 0;

    while (atual != NULL) {
        if (atual->valor == valor) {
            return posicao;
        }
        atual = atual->prox;
        posicao++;
    }

    return -1;
}

void inverterLista(No **head) {
    No *anterior = NULL;
    No *atual = *head;
    No *proximo = NULL;

    while (atual != NULL) {
        proximo = atual->prox;
        atual->prox = anterior;
        anterior = atual;
        atual = proximo;
    }

    *head = anterior;
}

void dividirLista(No *head, No **lista1, No **lista2) {
    if (head == NULL) {
        *lista1 = NULL;
        *lista2 = NULL;
        return;
    }

    No *lento = head;
    No *rapido = head->prox;

    while (rapido != NULL && rapido->prox != NULL) {
        lento = lento->prox;
        rapido = rapido->prox->prox;
    }

    *lista1 = head;
    *lista2 = lento->prox;
    lento->prox = NULL;
}

int main(void) {
    No *lista = NULL;
    int opcao, valor, pos;

    do {
        printf("\n===== GERENCIADOR DE LISTA ENCADEADA =====\n");
        printf("1 - Inserir no fim\n");
        printf("2 - Inserir em posicao especifica\n");
        printf("3 - Buscar valor\n");
        printf("4 - Inverter lista\n");
        printf("5 - Dividir lista em duas\n");
        printf("6 - Exibir lista\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Valor: ");
                scanf("%d", &valor);
                inserirFim(&lista, valor);
                break;

            case 2:
                printf("Valor: ");
                scanf("%d", &valor);
                printf("Posicao: ");
                scanf("%d", &pos);
                inserirPosicao(&lista, valor, pos);
                break;

            case 3:
                printf("Valor a buscar: ");
                scanf("%d", &valor);
                int resultado = buscarValor(lista, valor);
                if (resultado == -1) {
                    printf("Valor nao encontrado.\n");
                } else {
                    printf("Valor encontrado na posicao %d.\n", resultado);
                }
                break;

            case 4:
                inverterLista(&lista);
                printf("Lista invertida:\n");
                exibirLista(lista);
                break;

            case 5: {
                No *l1 = NULL;
                No *l2 = NULL;
                dividirLista(lista, &l1, &l2);
                printf("Primeira metade: ");
                exibirLista(l1);
                printf("Segunda metade: ");
                exibirLista(l2);
                liberarLista(&l1);
                liberarLista(&l2);
                lista = NULL;
                break;
            }

            case 6:
                exibirLista(lista);
                break;

            case 0:
                liberarLista(&lista);
                printf("Encerrando.\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    return 0;
}
