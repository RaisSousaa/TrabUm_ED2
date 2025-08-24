#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "programas.h"

// teste de alocar
int main() {
    Programas *raiz = NULL;
    infoProgramas dados;
    Programas *programas;
    int opcao;

    do {
        printf("=====MENU DE TESTE DE PROGRAMAS.C=====\n");
        printf("0 - Sair\n");
        printf("1 - Cadastrar Programas\n");
        printf("2 - Buscar Programa\n");
        printf("3 - Mostrar Programas\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 0: {
                printf("Saindo...\n");
                break;
            }

            case 1: {
                dados = preencherDadosPrograma();
                programas = alocarProgramas(dados);

                int resultado = inserirProgramas(&raiz, programas);  // <-- insere de verdade

                if (resultado == 1) {
                    printf("Programa %s inserido com sucesso.\n",
                           programas->infoProgramas.nomePrograma);
                } else {
                    printf("Programa já cadastrado.\n");
                    // NADA de free(programas) aqui, o inserirProgramas já deu free(no) no duplicado
                }
                break;
            }

            case 2: {
                char nome[TAM_STRING];
                printf("Digite o nome do programa para buscar: ");
                scanf("%49s", nome);  // depois você ajusta para aceitar espaços, se quiser

                Programas *resultado = buscarProgramas(raiz, nome);

                if (resultado != NULL) {
                    printf("Programa %s encontrado!\n",
                           resultado->infoProgramas.nomePrograma);
                } else {
                    printf("Programa '%s' não encontrado. Verifique a grafia.\n", nome);
                }
                break;
            }

            case 3: {
                mostrarProgramas(raiz);
                printf("\n");
                break;
            }

            default: {
                printf("Opção invalida.\n");
                break;
            }
        }

    } while (opcao != 0);

    return 0;
}
