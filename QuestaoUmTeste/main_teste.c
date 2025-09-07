#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"apresentadores.h"
#include"categorias.h"
#include"historico.h"
#include"programas.h"
#include"stream.h"


void menuCategoria(Stream *stream, Apresentadores *listaApresentadores);
void menuProgramas(Stream *stream ,Categorias *categoriaSelecionada, Apresentadores *listaApresentadores);
void menuApresentadores(Apresentadores **listaApresentadores);
void menuHistorico(Apresentadores *ap);



int main()
{
    Stream *raizStream = NULL;
    InfoStream dados;
    Stream *stream;

    Categorias *categoria;

    InfoApresentador dadosApre;
    Apresentadores *listaApresentadores = NULL;

    int opcao;

    do
    {
        printf("0 - Sair\n");
        printf("1 - Cadastrar Stream\n");
        printf("2 - Mostrar Stream\n");
        printf("3 - Buscar Stream\n");
        printf("4 - Menu Apresentador\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 0:
            printf("Finalizando...\n");
            break;
        case 1:
        
            dados = preencherDadosStream();
            stream = alocarNoStream(dados);

            int res = InserirStream(&raizStream, stream);

            if (res == 1)
                printf("Stream cadastrada com sucesso.\n");
            else printf("Stram já cadastrada!.\n");
            break;
        case 2:
            printf("===Catalogo Stream===\n");
            mostrarStreams(raizStream);
            printf("\n");
            break;

        case 3:
            char nomeStream[TAM_STRING];
            printf("Digite nome da Stream: ");
            scanf("%s", nomeStream);

            Stream *auxStream = buscarStream(raizStream, nomeStream);
            if (auxStream) {
                printf("\n\nStream: %s\n\n", auxStream->info.nomeStream);
                printf("===Menu para Categoria===\n\n");
                menuCategoria(auxStream, listaApresentadores); // só a stream selecionada
            } else {
                printf("Stream não cadastrada!\n");
            }
            break;
            
        case 4:
            menuApresentadores(&listaApresentadores);
            break;

        default:
            printf("Opção inválida.\n");
          break;
        }

    } while (opcao != 0);
    

    return 0;
}


void menuCategoria(Stream *stream, Apresentadores *listaApresentadores)
{
    Categorias **inicioCat = &stream->info.categoria; 
    int opcao;

    if (!stream) {
        printf("Lista de Stream vazia.\n");
        
    }else{

        do {
            printf("0 - Sair\n");
            printf("1 - Cadastrar Categoria\n");
            printf("2 - Mostrar Categoria\n");
            printf("3 - Buscar Categoria\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &opcao);

            switch (opcao) {
            case 0: 
                printf("Voltando para Menu Stream.\n");
                break;
            case 1: {
                Categorias *novoNo = alocarCategorias();
                if (novoNo != NULL) {
                    *novoNo = preencherDadosCategoria();
                    inserirCategoria(inicioCat, novoNo);   // usa a lista da stream
                }
                break;
            }
            case 2:
                printf("=== Catalogo Categoria ===\n");
                mostrarCategorias(*inicioCat);
                printf("\n");
                break;
            case 3: {
                char nome[TAM_STRING];
                printf("Nome do tipo de categoria: ");
                scanf("%s", nome);
                Categorias *achou = buscarCategoria(*inicioCat, nome);
                if (achou) {
                    printf("Tipo Categoria '%s' encontrada!\n", achou->nomeCategoria);
                    printf("=== Menu de Programas para essa Categoria ===\n");
                    menuProgramas(stream, achou, listaApresentadores);
                } else {
                    printf("Tipo Categoria nao cadastrada.\n");
                }
                break;
            }
            default:
                printf("Opção inválida.\n");
            }
        } while (opcao != 0);
    }
}


void menuProgramas(Stream *stream ,Categorias *categoriaSelecionada, Apresentadores *listaApresentadores)
{
    Programas **raizProgramas = &categoriaSelecionada->programas; //pegando o endereço do programa dentro da lista de categoria
    int opcao;

    if (categoriaSelecionada == NULL)
    {
        printf("Lista categoria vazia.\n");
    }else
    {
        do{
            printf("0 - Sair\n");
            printf("1 - Cadastrar Programa\n");
            printf("2 - Mostrar Programa\n");
            printf("3 - Buscar Programas\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &opcao);

            switch (opcao)
            {
            case 0:
                printf("Voltando para Menu Categoria.\n");
                break;

            case 1: 
                char nomeApresentador[TAM_STRING];

                //cadastrar programas
                printf("Digite nome do Apresentador do Programa: \n"); scanf("%s", nomeApresentador);
                
                /*
                1 - informar nome do apresentador
                2 - buscar na lista apresentador categoria que ele pertence, se ok

                    verificar se a stream que ele trabalha atualmente é a mesma stream do programa que quer criar

                    se o apresentador não trabalha na stream do programa que quer cadastrar 
                        3 - acessar o ponteiro da stream que apresentador trabalha
                        4 - acessar a categoria que o apresentador trabalha dentro da stream
                        5 - percorrer todos os programas e verificar se esse apresentador esta trabalhando em alguns dos programas
                        
                        se apresentador foi encontrado em algum programa
                            não pode cadatsrar apresnetador
                        senão
                            atualizar historico da stream e
                                finalizar o ultimo stream (função ainda sera criada)
                                criar um novo no de historico (preencher e inserir historico) 
                            mudar ponteiro da stream de apresentador
                    se o não trabalha em nem um lugar
                        criar um novo no de historico (preencher e inserir historico) 
                        mudar ponteiro da stream de apresentador

                                                                                        
                2 - dados = preencherDadosProgramas (então em preencher passo a stream ou passo aqui e lá tiro cadastrar apresentador ?)
                3 - *prog = alocarProgramas
                4 - se prog ok , inserirProgrmas

                é assim ?
                
            */
                infoProgramas dados = preencherDadosPrograma();
                Programas *prog = alocarProgramas(dados);

                if (prog) {
                    int res = inserirProgramas(raizProgramas, prog); // use sua função correta aqui
                    if (res == 1) 
                        printf("Programa cadastrado com sucesso.\n");

                    else    printf("Programa já cadastrado!.\n");
                }else printf("Falha ao alocar programa.\n");
                break;
            
            case 2:
                printf("===Catalogo de Programas===\n");
                mostrarProgramas(*raizProgramas);
                printf("\n");
                break;

            case 3: 
                //antes de poder cadastrar um programa, preciso que na lista apresentador
                //tenha um apresentador que trabalha nessa stream e pertence a categoria que quero cadastrar o programa
                //como eu poderia fazer isso aqui ?

                char nomePrograma[TAM_STRING];
                printf("Digite nome do Programa: ");
                scanf("%s", nomePrograma);

                Programas *auxPrograma = buscarProgramas(*raizProgramas, nomePrograma);
                if (auxPrograma) {
                    printf("\n\nPrograma: %s \n\n", auxPrograma->infoProgramas.nomePrograma);
                    // aqui você pode abrir submenu específico de um programa, se quiser
                } else {
                    printf("Programa não cadastrado!.\n");
                }
                break;

            default:
                printf("Opção inválida.\n");
                break;
            }
            
        } while (opcao != 0);
    }
}

void menuApresentadores(Apresentadores **listaApresentadores)
{
    int opcao;

    if (listaApresentadores == NULL) {
        printf("Erro: lista de apresentadores invalida.\n");
    } else {
        do {
            printf("\n=== Menu Apresentadores ===\n");
            printf("0 - Voltar\n");
            printf("1 - Cadastrar Apresentador\n");
            printf("2 - Listar Apresentadores\n");
            printf("3 - Buscar Apresentador\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &opcao);

            switch (opcao)
            {
            case 0:
                printf("Voltando para o menu principal.\n");
                break;

            case 1: 
                InfoApresentador dadosApre = preencherDadosApresentador();

                Apresentadores *novo = alocarApresentador();
                if (novo != NULL) {
                    strcpy(novo->info.nome,        dadosApre.nome);
                    strcpy(novo->info.streamAtual, dadosApre.streamAtual);
                    novo->info.ondeTrabalha = dadosApre.ondeTrabalha;

                    int ok = inserirApresentador(listaApresentadores, novo);
                    if (ok) {
                        printf("Apresentador cadastrado com sucesso.\n");
                    } else {
                        printf("Apresentador ja existente. Nao inserido.\n");
                        free(novo);
                    }
                } else {
                    printf("Erro ao alocar apresentador.\n");
                }
                break;
            
            case 2:
                if (*listaApresentadores == NULL) {
                    printf("Nenhum apresentador cadastrado.\n");
                } else {
                    printf("\n=== Lista de Apresentadores ===\n");
                    imprimirApresentadores(*listaApresentadores);
                    printf("\n");
                }
                break;

            case 3: 
                if (*listaApresentadores == NULL) {
                    printf("Lista vazia.\n");
                    break;
                }
                char nomeBuscado[TAM_STRING];
                int encontrado = 0;

                printf("Digite o nome do apresentador para buscar: ");
                scanf("%s", nomeBuscado);

                Apresentadores *ap = buscarApresentadores(*listaApresentadores,nomeBuscado, &encontrado);
                
                if (ap && encontrado) 
                {
                    printf("Encontrado: Nome: %s | Stream Atual: %s | Categoria: %d\n",
                           ap->info.nome,
                           ap->info.streamAtual,
                           ap->info.ondeTrabalha);
                } else {
                    printf("Apresentador nao encontrado.\n");
                }
                break;

            default:
                printf("Opcao invalida.\n");
                break;
            }

        } while (opcao != 0);
    }
}

void menuHistorico(Apresentadores *ap)
{
    int opcao;

    if (ap == NULL) {
        printf("Erro: apresentador invalido.\n");
    } else {
        do {
            printf("\n--- Historico de %s ---\n", ap->info.nome);
            printf("0 - Voltar\n");
            printf("1 - Cadastrar Informacoes\n");
            printf("2 - Mostrar Historico\n");
            printf("Escolha: ");
            scanf("%d", &opcao);

            switch (opcao) {
            case 0:
                printf("Voltando para o menu do apresentador.\n");
                break;

            case 1: 
                InfoHistorico historico = preencherDadosHistorico();
                int ok = inserirHistorico(&ap->info.historico, &historico);
                if (ok) {
                    printf("Informacoes cadastradas no historico.\n");
                } else {
                    printf("Falha ao inserir informacoes.\n");
                }
                break;

            case 2:
                imprimirHistorico(ap->info.historico);
                break;

            default:
                printf("Opcao invalida.\n");
                break;
            }

        } while (opcao != 0);
    }
}




/*
ix) Mostrar todos os programas de uma determinada stream que acontecem em um determinado dia e horário. ok

xi) Mostrar todos os programas de um determinado dia da semana de uma determinada categoria de uma stream.

xii) Mostrar todos os apresentadores de uma determinada stream. ok

xiii)Mostrar todos os apresentadores de um determinada categoria independente da stream que o mesmo trabalha. ok

xv) Permita remover um program de uma determinada categoria de uma stream.

xvi) Permita remover uma categoria de uma stream, só pode ser removida se não tiver nenhum programa cadastrado nela.

xvii)Permita alterar a stream que um apresentador trabalha atualmente. Lembre-se que não pode haver programa naquela stream apresentado pelo apresentador ( programa removido ou alterado o
apresentador).

*/

//  //sugestão chat para não deixar com printf dentro de uma função só
// void imprimirApresentadorLinha(const Apresentadores *apresentador) {
//     printf("Nome: %s | Stream: %s | Categoria (id): %d\n",
//            apresentador->info.nome,
//            apresentador->info.streamAtual,
//            apresentador->info.ondeTrabalha);
// }

// /* 
//    xii) Mostrar todos os apresentadores de uma determinada stream.
// */
// void mostrarApresentadoresPorStream(Apresentadores *listaApresentadores, const char *nomeStream) {
//     int encontrou = 0;

//     if (listaApresentadores && nomeStream) {
//         Apresentadores *atual = listaApresentadores;

//         do {
//             if (atual->info.streamAtual && strcmp(atual->info.streamAtual, nomeStream) == 0) {
//                 imprimirApresentadorLinha(atual);
//                 encontrou = 1;
//             }
//             atual = atual->prox;
//         } while (atual && atual != listaApresentadores);
//     }

//     if (!encontrou) {
//         printf("Nenhum apresentador encontrado para a stream '%s'.\n", nomeStream);
//     }
// }

// /* 
//    xiii) Mostrar todos os apresentadores de uma determinada categoria 
//    (independente da stream).
// */
// void mostrarApresentadoresPorCategoria(Apresentadores *listaApresentadores, int categoriaId) 
// {
//     int encontrou = 0;

//     if (listaApresentadores) {
//         Apresentadores *atual = listaApresentadores;

//         do {
//             if (atual->info.ondeTrabalha == categoriaId) {
//                 imprimirApresentadorLinha(atual);
//                 encontrou = 1;
//             }
//             atual = atual->prox;
//         } while (atual && atual != listaApresentadores);
//     }

//     if (!encontrou) {
//         printf("Nenhum apresentador encontrado para a categoria id=%d.\n", categoriaId);
//     }
// }



