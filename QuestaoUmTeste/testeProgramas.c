#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "programas.h"


/*=======QUestoes Sthefany==========*/

// ix) Mostrar todos os programas de uma determinada stream que acontecem em um determinado dia e horário.  -IN PROGRESS
/*
1. Entrar no menu de Stream
2. Informar a frequencia desejada
3. Informar o horario desejado
4. Percorrer todas as categorias
    4.1. Percorrer todos os programas
        4.1.1. Verificar se tem a frequencia informada e o hoario de inicio informado
            4.1.1.1. Mostrar o programa

*/


// xi) Mostrar todos os programas de um determinado dia da semana de uma determinada categoria de uma stream. -IN PROGRESS
// 1. Entrar no menu de Stream
// 2. Informar a periodicaidade desejada
// 3. Informa categoria desejada
// 4. Bucas a categoria especifica
//     4.1. Percorrer todos os programas da Categorias
//         4.1.1. Verificar se o programa tem a periodicidade desejada



// xii) Mostrar todos os apresentadores de uma determinada stream. ok
// 1. Entrar no menu Stream
// 2. Usar o nome da Stream
// 5. Percorrer a lista de apresentadores
//     5.1. Verificar se o apresentador trabalha na stream
//         5.1.1. Mostrar o apresentador


// xiii)Mostrar todos os apresentadores de um determinada categoria independente da stream que o mesmo trabalha. ok
// 1. Informar a categoria desejada
// 2. Percorrer Apresentadores
//     2.1. Verificar se o apresentador trabalha na categoria informada
//         2.1.1. Mostrar o apresentador


// xv) Permita remover um program de uma determinada categoria de uma stream. ok
// Já feito

// xvii)Permita alterar a stream que um apresentador trabalha atualmente. Lembre-se que não pode haver programa naquela stream apresentado pelo apresentador ( programa removido ou alterado o
// apresentador).
// Já feito  




// teste de alocar

            // case 1:
            //     // Informar dados

            //     printf("Informe o nome do estado: \n"); scanf("%s", nome_estado);
            //     printf("Informe o nome da capital: \n"); scanf("%s", nome_capital);  

            //     n_cidade = 1;
            //     populacao = 0;

            //     novo = buscar_estado(estados, nome_estado, &encontrou);

            //     if (encontrou == 0)
            //     {
            //         novo = alocar_estado();
            //         preencher_estado(&novo->infoEstado, nome_estado, nome_capital,n_cidade,populacao);
                    
            //         preencherCidade(&auxInfoCidade, nome_capital, 0);
                    
            //         inseriu_cidade = inserirCidade(&novo->infoEstado.arv_cidade, auxInfoCidade);

            //         resp = inserir_estado_ordenado(&estados, novo);

            //         if (resp == 1){
            //             printf("Estado Cadastrado !!!\n");    
            //         }else{
            //             printf("Não foi possivel cadastrar o Estado %s !!!", nome_estado);
            //         }
                    
            //     }else{
            //         printf("Não foi possivel cadastrar o Estado %s, pois ele já existe!!!", nome_estado);
            //     }
            //     break;


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
                    printf("Programa '%s' não encontrado.\n", nome);
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
