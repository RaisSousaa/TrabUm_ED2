#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "apresentadores.h"

/*Observação: !!!! Ao buscar apresentador, não esta sendo verificado antes 
se ele esta na lista de apresentadores cadastrados.*/

/*ver se cria o menu em outro arquivo ou se deixa no menu mesmo
analisar se o cadastro de datas pode esta da forma que foi deixada!*/

/*teste não esta 100% aprovado.*/


/* =================== funções locais =================== */

/* opcional, mas recomendado para limpar o \n pendente ao usar %49[^\n] seguido de leituras */
static void limparEntrada(void) 
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { /* descarta até o fim da linha */ }
}

/* ler uma linha inteira (com espaços) com limite de tamanho; garante \0 */
static int lerLinha(char *buf, size_t tam)
{
    if (!buf || tam == 0) return 0;
    if (fgets(buf, (int)tam, stdin) == NULL) return 0;
    /* remove \n final, se houver */
    size_t n = strlen(buf);
    if (n > 0 && buf[n-1] == '\n') buf[n-1] = '\0';
    return 1;
}

/* liberar memória da lista (bom pra não vazar no teste) */
static void liberarApresentadores(Apresentadores **inicio) 
{
    Apresentadores *atual = (inicio ? *inicio : NULL);
    while (atual) {
        /* libera a lista de historico de cada apresentador, se existir */
        if (atual->info.historico) {
            liberarHistorico(&atual->info.historico);
        }
        Apresentadores *prox = atual->prox;
        free(atual);
        atual = prox;
    }
    if (inicio) *inicio = NULL;
}


/* =================== main com o novo caso 4 =================== */

int main(void) {
    Apresentadores *inicio = NULL;
    int opcao;

    do {
        printf("\n===== MENU DE TESTE DE APRESENTADORES =====\n");
        printf("0 - Sair\n");
        printf("1 - Cadastrar Apresentador\n");
        printf("2 - Buscar Apresentador (simples)\n");
        printf("3 - Mostrar Apresentadores\n");
        printf("4 - Buscar Apresentador (menu de Historico)\n"); /* <== NOVO CASO */
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

                /* copiar os dados para o nó antes de inserir */
                no->info = dados;
                no->info.historico = NULL; /* garante histórico vazio ao iniciar */

                /* insere na lista ordenada (sem duplicar nomes) */
                int resultado = inserirApresentador(&inicio, no);

                if (resultado == 1) {
                    printf("Apresentador '%s' inserido com sucesso.\n", no->info.nome);
                } else {
                    printf("Apresentador '%s' ja cadastrado.\n", no->info.nome);
                    /* se inserirApresentador NÃO deu free(no) quando duplicado, liberar aqui */
                    free(no);
                }
                break;
            }

            case 2: {
                char nome[50];
                printf("Digite o nome do apresentador para buscar: ");
                if (!lerLinha(nome, sizeof(nome))) {
                    printf("Entrada invalida para nome.\n");
                    break;
                }

                int flag = 0;
                Apresentadores *res = buscarApresentadores(inicio, nome, &flag);

                if (res != NULL && flag == 1) {
                    printf("Encontrou: %s | Stream Atual: %s | Categoria: %d\n",
                           res->info.nome, res->info.streamAtual, res->info.ondeTrabalha);
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

            case 4: { /* ====== NOVO: busca + submenu de histórico ====== */
                char nome[50];
                printf("Digite o nome do apresentador: ");
                if (!lerLinha(nome, sizeof(nome))) {
                    printf("Entrada invalida para nome.\n");
                    break;
                }

                int flag = 0;
                Apresentadores *res = buscarApresentadores(inicio, nome, &flag);
                if (res == NULL || flag != 1) {
                    printf("Apresentador '%s' nao encontrado.\n", nome);
                    break;
                }

                printf("Apresentador encontrado: %s | Stream Atual: %s | Categoria: %d\n",
                       res->info.nome, res->info.streamAtual, res->info.ondeTrabalha);

                int opHist = -1;
                do {
                    printf("\n--- MENU HISTORICO de '%s' ---\n", res->info.nome);
                    printf("0 - Voltar\n");
                    printf("1 - Adicionar item de Historico\n");
                    printf("2 - Listar Historico\n");
                    printf("Escolha: ");
                    if (scanf("%d", &opHist) != 1) {
                        printf("Entrada invalida.\n");
                        limparEntrada();
                        continue;
                    }
                    limparEntrada();

                    if (opHist == 1) {
                        InfoHistorico ih;
                        /* lendo nome da stream (com espaços) */
                        printf("Nome da stream passada: ");
                        if (!lerLinha(ih.nomeStream, sizeof(ih.nomeStream))) {
                            printf("Entrada invalida para nome da stream.\n");
                            continue;
                        }

                        /* datas como inteiro AAAAMMDD (conforme seu comentario) */
                        printf("Data de inicio (AAAAMMDD): ");
                        if (scanf("%d", &ih.dataInicio) != 1) {
                            printf("Entrada invalida para data de inicio.\n");
                            limparEntrada();
                            continue;
                        }
                        limparEntrada();

                        printf("Data de termino (AAAAMMDD): ");
                        if (scanf("%d", &ih.dataTermino) != 1) {
                            printf("Entrada invalida para data de termino.\n");
                            limparEntrada();
                            continue;
                        }
                        limparEntrada();

                        /* insere ordenado no historico do apresentador */
                        int ok = inserirHistoricoOrdenado(&res->info.historico, &ih);
                        if (ok == 1) {
                            printf("Historico inserido.\n");
                        } else {
                            printf("Nao inserido (duplicata ou erro de memoria).\n");
                        }

                    } else if (opHist == 2) {
                        printf("\nHistorico de '%s':\n", res->info.nome);
                        imprimirHistorico(res->info.historico);
                    } else if (opHist == 0) {
                        /* voltar */
                    } else {
                        printf("Opcao invalida.\n");
                    }

                } while (opHist != 0);

                break;
            }

            default:
                printf("Opcao invalida.\n");
                break;
        }

    } while (opcao != 0);

    /* libera toda a lista antes de sair */
    liberarApresentadores(&inicio);
    return 0;
}
