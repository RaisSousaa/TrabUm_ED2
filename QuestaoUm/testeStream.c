#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"stream.h"


//  para compilar é só roda:
//  gcc stream.c testeStream.c -o teste
//  ./teste

int main() {
    Stream *raiz = CriarStream();
    int opcao;
    char nomeBusca[50];
    char nomeRemover[50];

    do {
        printf("\n===== MENU STREAM =====\n");
        printf("1 - Inserir Stream\n");
        printf("2 - Mostrar Streams (ordem alfabetica)\n");
        printf("3 - Buscar Stream\n");
        printf("4 - Remover Stream\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                InfoStream dados = preencherDadosStream();
                Stream *no = alocarNoStream(dados);
                if (InserirStream(&raiz, no))
                    printf("Stream inserida com sucesso!\n");
                else
                    printf("Stream já existe!\n");
                break;
            }
            case 2:
                printf("\n--- Lista de Streams ---\n");
                imprimirInOrdem(raiz);
                break;
            case 3:
                printf("Digite o nome da Stream para buscar: ");
                scanf("%s", nomeBusca);
                {
                    Stream *resultado = buscarStream(raiz, nomeBusca);
                    if (resultado)
                        printf("Encontrada: %s | Site: %s\n", 
                               resultado->info.nomeStream, resultado->info.nomeSite);
                    else
                        printf("Stream não encontrada!\n");
                }
                break;
            case 4:
                printf("Digite o nome da Stream para remover: ");
                scanf("%s", nomeRemover);
                remover(&raiz, nomeRemover);
                printf("Se existia, a Stream foi removida.\n");
                break;
            case 0:
                printf("Encerrando programa...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}



