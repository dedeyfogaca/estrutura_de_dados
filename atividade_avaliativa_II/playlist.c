#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    char musica[100];
    struct No *prox;
    struct No *ant;
} No;

void adicionarMusica(No **head, char *nome) {
    No *novo = (No*) malloc(sizeof(No));
    strcpy(novo->musica, nome);

    if (*head == NULL) {
        novo->prox = novo;
        novo->ant = novo;
        *head = novo;
        return;
    }

    No *ultimo = (*head)->ant;
    novo->prox = *head;
    novo->ant = ultimo;
    ultimo->prox = novo;
    (*head)->ant = novo;
}

void proximaMusica(No **atual) {
    if (*atual == NULL) return;
    *atual = (*atual)->prox;
}

void musicaAnterior(No **atual) {
    if (*atual == NULL) return;
    *atual = (*atual)->ant;
}

void exibirPlaylist(No *head) {
    if (head == NULL) {
        printf("Playlist vazia.\n");
        return;
    }

    No *atual = head;
    int i = 1;
    do {
        printf("%d. %s\n", i, atual->musica);
        atual = atual->prox;
        i++;
    } while (atual != head);
}

int totalMusicas(No *head) {
    if (head == NULL) return 0;

    int cont = 0;
    No *atual = head;
    do {
        cont++;
        atual = atual->prox;
    } while (atual != head);

    return cont;
}

void tocarPlaylistCompleta(No *head) {
    if (head == NULL) {
        printf("Playlist vazia.\n");
        return;
    }

    int total = totalMusicas(head);
    No *atual = head;

    for (int i = 0; i < total; i++) {
        printf("Tocando agora: %s\n", atual->musica);
        atual = atual->prox;
    }
    printf("Fim da playlist.\n");
}

void liberarPlaylist(No **head) {
    if (*head == NULL) return;

    No *atual = *head;
    (*head)->ant->prox = NULL;

    while (atual != NULL) {
        No *temp = atual;
        atual = atual->prox;
        free(temp);
    }
    *head = NULL;
}

int main(void) {
    No *playlist = NULL;
    No *atual = NULL;
    int opcao;
    char nome[100];

    do {
        printf("\n===== PLAYLIST CIRCULAR =====\n");
        printf("1 - Adicionar musica\n");
        printf("2 - Exibir playlist\n");
        printf("3 - Total de musicas\n");
        printf("4 - Proxima musica\n");
        printf("5 - Musica anterior\n");
        printf("6 - Tocar playlist completa\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Nome da musica: ");
                scanf(" %[^\n]", nome);
                adicionarMusica(&playlist, nome);
                if (atual == NULL) atual = playlist;
                break;

            case 2:
                exibirPlaylist(playlist);
                break;

            case 3:
                printf("Total: %d musicas.\n", totalMusicas(playlist));
                break;

            case 4:
                proximaMusica(&atual);
                if (atual != NULL) printf("Agora tocando: %s\n", atual->musica);
                break;

            case 5:
                musicaAnterior(&atual);
                if (atual != NULL) printf("Agora tocando: %s\n", atual->musica);
                break;

            case 6:
                tocarPlaylistCompleta(playlist);
                break;

            case 0:
                liberarPlaylist(&playlist);
                printf("Encerrando.\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    return 0;
}
