#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "apresentadores.h"


//======Código feito pelo GPT com base no meu teste de programas=======


/* opcional, mas recomendado para limpar o \n pendente ao usar %49[^\n] seguido de leituras */
static void limparEntrada(void) 
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { /* descarta até o fim da linha */ }
}

/* liberar memória da lista (bom pra não vazar no teste) */
static void liberarApresentadores(Apresentadores **inicio) 
{
    Apresentadores *atual = (inicio ? *inicio : NULL);
    while (atual) {
        Apresentadores *prox = atual->prox;
        free(atual);
        atual = prox;
    }
    if (inicio) *inicio = NULL;
}

int main(void) {
    Apresentadores *inicio = NULL;
    int opcao;

    do {
        printf("\n===== MENU DE TESTE DE APRESENTADORES =====\n");
        printf("0 - Sair\n");
        printf("1 - Cadastrar Apresentador\n");
        printf("2 - Buscar Apresentador\n");
        printf("3 - Mostrar Apresentadores\n");
        printf("Escolha uma opcao: ");
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida.\n");
            limparEntrada();
            continue;
        }
        limparEntrada(); /* remove o \n depois do número */

        switch (opcao) {

            case 0:
                printf("Saindo...\n");
                break;

            case 1: {
                /* preenche os dados (usa seus scanf com %49[^\n]) */
                InfoApresentador dados = preencherDadosApresentador();
                limparEntrada(); /* garantir buffer limpo para o próximo input */

                /* aloca o nó */
                Apresentadores *no = alocarApresentador();
                if (no == NULL) {
                    printf("Falha ao alocar apresentador.\n");
                    break;
                }

                /* IMPORTANTÍSSIMO: copiar os dados para o nó antes de inserir */
                no->info = dados;

                /* insere na lista ordenada (sem duplicar nomes) */
                int resultado = inserirApresentador(&inicio, no);

                if (resultado == 1) {
                    printf("Apresentador '%s' inserido com sucesso.\n", no->info.nome);
                } else {
                    printf("Apresentador '%s' ja cadastrado.\n", no->info.nome);
                    /* como inserirApresentador NAO deu free(no) quando duplicado,
                       precisamos liberar aqui para não vazar memória */
                    free(no);
                }
                break;
            }

            case 2: {
                char nome[50];
                printf("Digite o nome do apresentador para buscar: ");
                /* espaço antes do % para pular \n pendente; lê até fim da linha (com espaços) */
                if (scanf(" %49[^\n]", nome) != 1) {
                    printf("Entrada invalida para nome.\n");
                    limparEntrada();
                    break;
                }
                limparEntrada();

                int flag = 0;
                Apresentadores *res = buscarApresentadores(inicio, nome, &flag);

                if (res != NULL && flag == 1) {
                    printf("Encontrou\n");
                } else {
                    printf("Apresentador '%s' nao encontrado.\n", nome);
                }
                break;
            }

            case 3:
                if (inicio == NULL) {
                    printf("Lista vazia.\n");
                } else {
                    printf("\n--- Lista de Apresentadores ---\n");
                    imprimirApresentadores(inicio);
                    printf("-------------------------------\n");
                }
                break;

            default:
                printf("Opcao invalida.\n");
                break;
        }

    } while (opcao != 0);

    /* libera toda a lista antes de sair */
    liberarApresentadores(&inicio);
    return 0;
}
