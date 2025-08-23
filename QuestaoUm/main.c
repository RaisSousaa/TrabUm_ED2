#include <stdio.h>
#include <stdlib.h>
#include "categorias.h"

// aqui estão as funções que você já tem implementadas
// (prencherCategoria, inserirCategoria, alocarMemoriaNo, mostrarCategorias)

int main() {
    Categorias *lista = NULL;   // lista começa vazia
    int opcao;

    do {
        printf("\n--- MENU ---\n");
        printf("1 - Inserir nova categoria\n");
        printf("2 - Mostrar categorias\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: {
                Categorias *novo = alocarMemoriaNo();
                if (novo != NULL) {
                    prencherCategoria(novo);
                    inserirCategoria(&lista, novo);
                }
                break;
            }
            case 2:
                if (lista == NULL) {
                    printf("Lista vazia!\n");
                } else {
                    mostrarCategorias(lista);
                }
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
