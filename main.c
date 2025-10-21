#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Sala {
    char valor[50];
    struct Sala* esquerda;
    struct Sala* direita;
    char pista[30];
} Sala;

typedef struct Pista {
    char valor[30];
    struct Pista* esquerda;
    struct Pista* direita;
} Pista;

Sala* criarSala(char* valor, char* pista) {
    Sala* novo = (Sala*) malloc(sizeof(Sala));
    strcpy(novo->valor, valor);
    novo->esquerda = NULL;
    novo->direita = NULL;
    strcpy(novo->pista, pista);
    return novo;
}

Pista* criarPista(const char* valor) {
    Pista* novo = (Pista*)malloc(sizeof(Pista));
    strcpy(novo->valor, valor);
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

Pista* inserirPista(Pista** raiz, const char* valor) {
    if (*raiz == NULL) {
    *raiz = criarPista(valor);
    return *raiz;
    } else if (strcmp(valor, (*raiz)->valor) < 0) {
        (*raiz)->esquerda = inserirPista(&((*raiz)->esquerda), valor);
    } else {
        (*raiz)->direita = inserirPista(&((*raiz)->direita), valor);
    }
    return *raiz;
}

void explorarSalasComPistas(Sala** atual, char* direcao, Pista** pistas) {
    if (strcmp(direcao, "esquerda") == 0) {
        if ((*atual)->esquerda == NULL) {
            printf("Não há caminho para o lado esquerdo, tente outra direção.\n");
            return;
        }
        *atual = (*atual)->esquerda;
    } else if ((strcmp(direcao, "direita") == 0)) {
        if ((*atual)->direita == NULL) {
            printf("Não há caminho para o lado direito, tente outra direção.\n");
            return;
        }
        *atual = (*atual)->direita;
    }
    if (strcmp((*atual)->pista, "nada") != 0) {
        inserirPista(pistas, (*atual)->pista);
    }
}

void liberarSalas(Sala* raiz) {
    if (raiz != NULL) {
        liberarSalas(raiz->esquerda);
        liberarSalas(raiz->direita);
        free(raiz);
    }
}

void exibirPistas(Pista* raiz) {
    if (raiz != NULL) {
        exibirPistas(raiz->esquerda);
        printf("%s ", raiz->valor);
        exibirPistas(raiz->direita);
    }
}

void liberarPistas(Pista* raiz) {
    if (raiz != NULL) {
        liberarPistas(raiz->esquerda);
        liberarPistas(raiz->direita);
        free(raiz);
    }
}

int main () {
    Sala* raiz = criarSala("Hall de Entrada", "nada");
    raiz->esquerda = criarSala("Sala de Estar", "Chave perdida");
    raiz->direita = criarSala("Biblioteca", "Livro com pagina faltando");
    raiz->esquerda->esquerda = criarSala("Quarto", "Lencol manchado");

    Pista* raizPistas = NULL;

    char opcao[2];
    Sala* atual = raiz;

    do {
        printf("\n-+- Detective Quest -+-\n");
        printf("Sala atual: %s\n", atual->valor);
        printf("Pista da sala: %s\n\n", atual->pista);

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
            explorarSalasComPistas(&atual, "esquerda", &raizPistas);
        } else if (strcmp(opcao, "d") == 0) {
            explorarSalasComPistas(&atual, "direita", &raizPistas);
        } else if (strcmp(opcao, "s") == 0) {
            printf("Pistas coletadas: ");
            exibirPistas(raizPistas);
            printf("\n\nSaindo...\n");
        } else {
            printf("Opção inválida. Tente novamente.\n");
        }
    } while (strcmp(opcao, "s") != 0);

    liberarSalas(raiz);
    liberarPistas(raizPistas);

    return 0;
}