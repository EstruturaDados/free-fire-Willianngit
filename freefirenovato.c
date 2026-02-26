#include <stdio.h>
#include <string.h>
#include <ctype.h>  // Para tolower()

// Struct Item da mochila.
struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

void mostrarMochila(struct Item mochila[], int numItens) {
    printf("\n--- ITENS NA MOCHILA (%d/10) ---\n", numItens);
    if (numItens == 0) {
        printf("Nenhum item cadastrado.\n");
    } else {
        printf("NOME              | TIPO       | QUANTIDADE\n");
        for (int i = 0; i < numItens; i++) {
            printf("%-18s| %-11s| %d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
        }
    }
    printf("\nPressione Enter para continuar...");
    getchar();
}

// Compara strings ignorando case.
int strcmp_insensivel(char *s1, char *s2) {
    while (*s1 && *s2) {
        if (tolower(*s1) != tolower(*s2)) {
            return tolower(*s1) - tolower(*s2);
        }
        s1++;
        s2++;
    }
    return tolower(*s1) - tolower(*s2);
}

int main() {
    struct Item mochila[10];
    int numItens = 0;
    int opcao;

    printf("MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA\n");

    do {
        printf("\nItens na mochila: %d/10\n\n", numItens);
        printf("1. Adicionar Item (Loot)\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens na Mochila\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 1) {
            if (numItens < 10) {
                printf("\n--- Adicionar Novo Item ---\n");
                printf("Nome do item: ");
                scanf("%29s", mochila[numItens].nome);
                printf("Tipo do item (arma, municao, cura, etc.): ");
                scanf("%19s", mochila[numItens].tipo);
                printf("Quantidade: ");
                scanf("%d", &mochila[numItens].quantidade);
                getchar();
                numItens++;
                printf("Item '%s' adicionado com sucesso!\n", mochila[numItens-1].nome);
                mostrarMochila(mochila, numItens);
            } else {
                printf("Mochila cheia!\n");
                mostrarMochila(mochila, numItens);
            }
        } else if (opcao == 2) {
            if (numItens > 0) {
                printf("\n--- Remover Item ---\n");
                printf("Digite o nome do item a ser removido: ");
                char nomeRemover[30];
                scanf("%29s", nomeRemover);
                getchar();
                int encontrado = 0;
                for (int i = 0; i < numItens; i++) {
                    if (strcmp_insensivel(mochila[i].nome, nomeRemover) == 0) {
                        mochila[i].quantidade -= 1;  // Remove -1 quantidade!
                        printf("Item '%s' removido com sucesso! (Qtd agora: %d)\n", mochila[i].nome, mochila[i].quantidade);
                        if (mochila[i].quantidade <= 0) {
                            // Se zerou, shift remove.
                            for (int j = i; j < numItens - 1; j++) {
                                mochila[j] = mochila[j + 1];
                            }
                            numItens--;
                        }
                        encontrado = 1;
                        mostrarMochila(mochila, numItens);
                        break;
                    }
                }
                if (!encontrado) {
                    printf("Item nao encontrado!\n");
                    mostrarMochila(mochila, numItens);
                }
            } else {
                printf("Mochila vazia!\n");
                mostrarMochila(mochila, numItens);
            }
        } else if (opcao == 3) {
            mostrarMochila(mochila, numItens);
        }

    } while (opcao != 0);
    

    return 0;
}
