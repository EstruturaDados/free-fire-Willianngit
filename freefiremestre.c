#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
    int prioridade; // 1 = menor, 5 = maior
};

int strcmp_insensivel(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        int c1 = tolower((unsigned char)*s1);
        int c2 = tolower((unsigned char)*s2);
        if (c1 != c2) return c1 - c2;
        s1++; s2++;
    }
    return tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
}

long comparacoes_total = 0;

void mostrarMochila(struct Item mochila[], int numItens) {
    printf("\n--- INVENTARIO ATUAL (%d/10) ---\n", numItens);
    if (numItens == 0) {
        printf("Nenhum item cadastrado.\n");
    } else {
        printf("NOME             | TIPO      | QUANTIDADE | PRIORIDADE\n");
        for (int i = 0; i < numItens; i++) {
            printf("%-17s| %-10s| %-10d | %-9d\n",
                   mochila[i].nome,
                   mochila[i].tipo,
                   mochila[i].quantidade,
                   mochila[i].prioridade);
        }
    }
    printf("\nPressione Enter para continuar...");
    getchar();
}

void insertionSortNome(struct Item mochila[], int n) {
    comparacoes_total = 0;
    for (int i = 1; i < n; i++) {
        struct Item key = mochila[i];
        int j = i - 1;
        while (j >= 0) {
            comparacoes_total++;
            if (strcmp_insensivel(key.nome, mochila[j].nome) < 0) {
                mochila[j + 1] = mochila[j];
                j--;
            } else break;
        }
        mochila[j + 1] = key;
    }
}

void insertionSortTipo(struct Item mochila[], int n) {
    comparacoes_total = 0;
    for (int i = 1; i < n; i++) {
        struct Item key = mochila[i];
        int j = i - 1;
        while (j >= 0) {
            comparacoes_total++;
            if (strcmp_insensivel(key.tipo, mochila[j].tipo) < 0) {
                mochila[j + 1] = mochila[j];
                j--;
            } else break;
        }
        mochila[j + 1] = key;
    }
}


void selectionSortPrioridade(struct Item mochila[], int n) {
    comparacoes_total = 0;
    for (int i = 0; i < n - 1; i++) {
        int max_idx = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes_total++;
            if (mochila[j].prioridade > mochila[max_idx].prioridade) {
                max_idx = j;
            }
        }
        if (max_idx != i) {
            struct Item tmp = mochila[i];
            mochila[i] = mochila[max_idx];
            mochila[max_idx] = tmp;
        }
    }
}

int buscaBinariaNome(struct Item mochila[], int n, const char *nomeBusca) {
    comparacoes_total = 0;
    int l = 0, r = n - 1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        comparacoes_total++;
        int cmp = strcmp_insensivel(mochila[m].nome, nomeBusca);
        if (cmp == 0) return m;
        if (cmp < 0) l = m + 1;
        else r = m - 1;
    }
    return -1;
}

void menuOrdenacao(struct Item mochila[], int numItens, bool *ordenadoPorNome) {
    if (numItens == 0) {
        printf("Mochila vazia!\n");
        printf("\nPressione Enter para continuar...");
        getchar();
        return;
    }

    int criterio;
    printf("\n--- Estrategia de Organizacao ---\n");
    printf("Como deseja ordenar os componentes?\n");
    printf("1. Por Nome (Ordem Alfabetica)\n");
    printf("2. Por Tipo\n");
    printf("3. Por Prioridade de Montagem\n");
    printf("0. Cancelar\n");
    printf("Escolha o criterio: ");
    scanf("%d", &criterio);
    getchar();

    if (criterio == 1) {
        insertionSortNome(mochila, numItens);
        *ordenadoPorNome = true;
        printf("\nMochila organizada por NOME.\n");
        printf("Analise de Desempenho: Foram necessarias %ld comparacoes.\n", comparacoes_total);
    } else if (criterio == 2) {
        insertionSortTipo(mochila, numItens);
        *ordenadoPorNome = false;
        printf("\nMochila organizada por TIPO.\n");
        printf("Analise de Desempenho: Foram necessarias %ld comparacoes.\n", comparacoes_total);
    } else if (criterio == 3) {
        selectionSortPrioridade(mochila, numItens);
        *ordenadoPorNome = false;
        printf("\nMochila organizada por PRIORIDADE.\n");
        printf("Analise de Desempenho: Foram necessarias %ld comparacoes.\n", comparacoes_total);
    } else {
        printf("Operacao cancelada.\n");
        printf("\nPressione Enter para continuar...");
        getchar();
        return;
    }

    mostrarMochila(mochila, numItens);
}

void buscarBinaria(struct Item mochila[], int numItens, bool ordenadoPorNome) {
    if (numItens == 0) {
        printf("Mochila vazia!\n");
        printf("\nPressione Enter para continuar...");
        getchar();
        return;
    }

    if (!ordenadoPorNome) {
        printf("\nALERTA: A busca binaria requer que a mochila esteja ordenada por NOME.\n");
        printf("Use a Opcao 4 para organizar a mochila primeiro.\n");
        printf("\nPressione Enter para continuar...");
        getchar();
        return;
    }

    char nomeBusca[30];
    printf("\n--- Busca Binaria por Componente-Chave ---\n");
    printf("Nome do componente a buscar: ");
    scanf("%29s", nomeBusca);
    getchar();

    int idx = buscaBinariaNome(mochila, numItens, nomeBusca);
    if (idx != -1) {
        printf("\n--- Componente-Chave Encontrado! ---\n");
        printf("Nome: %s, Tipo: %s, Qtd: %d, Prio: %d\n",
               mochila[idx].nome,
               mochila[idx].tipo,
               mochila[idx].quantidade,
               mochila[idx].prioridade);
        printf("Analise de Desempenho: Foram necessarias %ld comparacoes.\n", comparacoes_total);
    } else {
        printf("\n--- Componente-Chave NAO encontrado! ---\n");
        printf("Analise de Desempenho: Foram necessarias %ld comparacoes.\n", comparacoes_total);
    }

    printf("\nPressione Enter para continuar...");
    getchar();
}

int main() {
    struct Item mochila[10];
    int numItens = 0;
    int opcao;
    bool ordenadoPorNome = false;

    do {
        printf("\n ====== PLANO DE FUGA - CODIGO DA ILHA (NIVEL MESTRE) ====== \n");
        printf("\nItens na Mochila: %d/10\n", numItens);
        printf("Status da Ordenacao por Nome: %s\n\n", ordenadoPorNome ? "ORDENADO" : "NAO ORDENADO");
        printf("1. Adicionar Componente\n");
        printf("2. Descartar Componente\n");
        printf("3. Listar Componentes (Inventario)\n");
        printf("4. Organizar Mochila (Ordenar Componentes)\n");
        printf("5. Busca Binaria por Componente-Chave (por nome)\n");
        printf("0. ATIVAR TORRE DE FUGA (Sair)\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 1) {
            if (numItens < 10) {
                printf("\n--- Coletando Novo Componente ---\n");
                printf("Nome: ");
                scanf("%29s", mochila[numItens].nome);
                printf("Tipo: (Estrutural, Eletronico, Energia): ");
                scanf("%19s", mochila[numItens].tipo);
                printf("Quantidade: ");
                scanf("%d", &mochila[numItens].quantidade);
                printf("Prioridade de Montagem (1-5): ");
                scanf("%d", &mochila[numItens].prioridade);
                getchar();
                printf("\nComponente '%s' adicionado!\n", mochila[numItens].nome);
                numItens++;
                ordenadoPorNome = false;
                mostrarMochila(mochila, numItens);
            } else {
                printf("Mochila cheia!\n");
                printf("\nPressione Enter para continuar...");
                getchar();
            }
        } else if (opcao == 2) {
            if (numItens > 0) {
                char nomeRemover[30];
                printf("\n--- Descartar Componente ---\n");
                printf("Nome do componente: ");
                scanf("%29s", nomeRemover);
                getchar();
                bool encontrado = false;
                for (int i = 0; i < numItens; i++) {
                    if (strcmp_insensivel(mochila[i].nome, nomeRemover) == 0) {
                        mochila[i].quantidade--;
                        printf("Componente '%s' descartado (qtd restante: %d)\n",
                               mochila[i].nome, mochila[i].quantidade);
                        if (mochila[i].quantidade <= 0) {
                            for (int j = i; j < numItens - 1; j++) {
                                mochila[j] = mochila[j + 1];
                            }
                            numItens--;
                        }
                        encontrado = true;
                        ordenadoPorNome = false;
                        break;
                    }
                }
                if (!encontrado) printf("Componente nao encontrado!\n");
                mostrarMochila(mochila, numItens);
            } else {
                printf("Mochila vazia!\n");
                printf("\nPressione Enter para continuar...");
                getchar();
            }
        } else if (opcao == 3) {
            mostrarMochila(mochila, numItens);
        } else if (opcao == 4) {
            menuOrdenacao(mochila, numItens, &ordenadoPorNome);
        } else if (opcao == 5) {
            buscarBinaria(mochila, numItens, ordenadoPorNome);
        }

    } while (opcao != 0);

    return 0;
}
