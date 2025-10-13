#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Sala {
    char valor[50];
    struct Sala* esquerda;
    struct Sala* direita;
};

struct Sala* criarSala(char* valor) {
    struct Sala* novo = (struct Sala*) malloc(sizeof(struct Sala));
    strcpy(novo->valor, valor);
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

void explorarSalas(struct Sala** atual, char* direcao) {
    if (strcmp(direcao, "esquerda") == 0) {
        if ((*atual)->esquerda == NULL) {
            printf("Não há caminho para o lado esquerdo, tente outra direção.");
            return;
        }
        *atual = (*atual)->esquerda;
    } else if ((strcmp(direcao, "direita") == 0)) {
        if ((*atual)->direita == NULL) {
            printf("Não há caminho para o lado direito, tente outra direção.");
            return;
        }
        *atual = (*atual)->direita;
    }
}

void liberar(struct Sala* raiz) {
    if (raiz != NULL) {
        liberar(raiz->esquerda);
        liberar(raiz->direita);
        free(raiz);
    }
}


int main () {
    struct Sala* raiz = criarSala("Hall de Entrada");
    raiz->esquerda = criarSala("Sala de Estar");
    raiz->direita = criarSala("Biblioteca");
    raiz->esquerda->esquerda = criarSala("Quarto");

    char opcao[2];
    struct Sala* atual = raiz;

    do {
        printf("-+- Detective Quest -+-\n");
        printf("Sala atual: %s\n\n", atual->valor);

        if (atual->esquerda != NULL) {
            printf("e. Ir para a esquerda\n");
        }
        if (atual->direita != NULL) {
            printf("d. Ir para a direita\n");
        }
        printf("s. Sair\n");

        printf("Opção: ");
        scanf("%s", opcao);
        getchar();

        if (strcmp(opcao, "e") == 0) {
            explorarSalas(&atual, "esquerda");
        } else if (strcmp(opcao, "d") == 0) {
            explorarSalas(&atual, "direita");
        } else if (strcmp(opcao, "s") == 0) {
            printf("Saindo...\n");
        } else {
            printf("Opção inválida. Tente novamente.\n");
        }

        if (strcmp(opcao, "s") != 0) {
            printf("\nPressione ENTER para continuar...");
            getchar();
        }
    } while (strcmp(opcao, "s") != 0);

    liberar(raiz);

    return 0;
}