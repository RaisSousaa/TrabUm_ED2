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

void finalizarUltimoHistoricoSeAberto(Historico *hist, int dataTermino);
int programasContemApresentador(Programas *raiz, const char *nomeApresentador);
Categorias* encontrarCategoriaPorTipoNaStream(Stream *stream, Tipo tipo);



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
        printf("4 - Mostrar streams que tem uma determinada categoria\n");
        printf("5 - Mostrar as streams que tem uma determinada categoria\n");
        printf("6 - Menu Apresentador\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
            case 0:
            {
                printf("Finalizando...\n");
                break;
            }
 //i) Cadastrar Stream: cadastrar dados de streams organizados em uma árvore binária pelo nome da stream, o usuário pode //cadastrar uma stream a qualquer momento, não permita cadastro repetido.
            case 1:
            {
                InfoStream dados = preencherDadosStream();
                Stream *novoNo = alocarNoStream(dados);
                if(InserirStream(&raizStream, novoNo))
                    printf("Stream cadastrada!\n");
                else
                    printf("A stream nao foi cadastrada pois ja existe!\n");

                break;
            }
// v) Mostrar todas as streams cadastradas.
            case 2:
            {
                printf("===Catalogo Stream===\n");
                // AQUI FOI FEITA A CORREÇÃO
                mostrarStreams(raizStream);
                printf("\n");
                break;
            }

            case 3: 
            {
                char nomeStream[TAM_STRING];
                printf("Digite nome da Stream: ");
                scanf("%s", nomeStream);

                // AQUI FOI FEITA A CORREÇÃO
                Stream *auxStream = buscarStream(raizStream, nomeStream);
                if (auxStream) {
                    //menu para categoria
                    menuCategoria(auxStream, listaApresentadores); // só a stream selecionada
                } else {
                    printf("Stream não cadastrada!\n");
                }
                break;
            }

//viii)Mostrar todas as streams que tem uma determinada categoria.
            case 4:
            {
                char nomecategoria[50];
                printf("Digite o nome da categoria:\n");
                setbuf(stdin, NULL);
                scanf("%[^\n]", nomecategoria);
                // AQUI FOI FEITA A CORREÇÃO
                mostrarStreamDeCategoria(raizStream, nomecategoria);
                break;
            }

// x) Mostrar todas as streams que tem um determinado tipo de categoria.
            case 5:
            {
                int escolha = 0;
                printf("Escolha o tipo da categoria: \n");
                printf("1 - Esporte \n");
                printf("2 - Noticia \n");
                printf("3 - Entretenimento \n");
                printf("4 - Cultura \n");
                printf("Sua escolha -> ");
                scanf("%d", &escolha);
                // AQUI FOI FEITA A CORREÇÃO
                mostrarStreamDoTipoCategoria(raizStream, escolha);
                break;
            }       

            case 6:
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
    int opcao = -1;
    Categorias **inicioCat = NULL;

    if (stream == NULL) 
    {
        printf("Lista de Stream vazia.\n");
        opcao = 0;          
    } 
    else 
    {
        inicioCat = &stream->info.categoria; //inicializa dentro de stream
    }

    while (opcao != 0) 
    {
        printf("\n=== Menu Categoria (%s) ===\n", stream->info.nomeStream);
        printf("0 - Voltar\n");
        printf("1 - Cadastrar Categoria\n");
        printf("2 - Mostrar Categorias\n");
        printf("3 - Buscar Categoria\n");
        printf("4 - Remover Categoria\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) 
        {
            case 0:
                printf("Voltando para Menu Stream.\n");
                break;

// ii) Cadastrar Categoria
            case 1: {
                Categorias *novoNo = alocarMemoriaNo();

                if (novoNo) 
                {
                    prencherCategoria(novoNo);
                    if (!inserirCategoria(inicioCat, novoNo))  //
                    {
                        printf("Categoria ja cadastrada.\n");
                        free(novoNo);
                    } else {
                        printf("Categoria cadastrada.\n");
                    }
                } else {
                    printf("Falha de alocacao.\n");
                }
                break;
            }
// vi) Mostrar todas as categorias cadastradas para uma determinada stream.
            case 2:
                printf("\n=== Catalogo de Categorias ===\n");
                mostrarCategorias(inicioCat ? *inicioCat : NULL);
                printf("\n");
                break;

// vii) Mostrar todos os programas de uma determinada categoria de uma determinada stream.
            case 3: {
                char nome[TAM_STRING];
                printf("Nome da categoria: ");
                scanf(" %49[^\n]", nome);
                Categorias *achou = buscarCategoria(inicioCat ? *inicioCat : NULL, nome);
                if (achou) {
                    printf("Categoria '%s' encontrada! Abrindo menu de Programas...\n", achou->nomeCategoria);
                    menuProgramas(stream, achou, listaApresentadores);
                } else {
                    printf("Categoria nao cadastrada.\n");
                }
                break;
            }
// xvi) Permita remover uma categoria de uma stream, só pode ser removida se não tiver nenhum programa
//cadastrado nela
            case 4: {
                char nome[TAM_STRING];
                printf("Nome da categoria a remover: ");
                scanf(" %49[^\n]", nome);
                removerCategoria(inicioCat, nome);
                printf("Operacao de remocao concluida.\n");
                break;
            }

            default:
                printf("Opcao invalida.\n");
                break;
        }
    }
}



void menuProgramas(Stream *stream ,Categorias *categoriaSelecionada, Apresentadores *listaApresentadores)
{
    int opcao;
    Programas **raizProgramas = NULL;  /* só definimos depois do NULL-check */

    if (categoriaSelecionada == NULL) {
        printf("Lista categoria vazia.\n");
    } else {
        raizProgramas = &categoriaSelecionada->programas; // endereço da raiz da BST de programas

        do {
            printf("0 - Sair\n");
            printf("1 - Cadastrar Programa\n");
            printf("2 - Mostrar Programa\n");
            printf("3 - Buscar Programas\n");
            printf("4 - Cadastrar Apresentador.\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &opcao);

            switch (opcao)
            {
            case 0:
                printf("Voltando para Menu Categoria.\n");
                break;

            case 1: {
                /* 1) escolher apresentador */
                char nomeApresentador[TAM_STRING];
                printf("Digite nome do Apresentador do Programa: ");
                scanf("%49s", nomeApresentador);

                int encontrado = 0;
                Apresentadores *ap = buscarApresentadores(listaApresentadores, nomeApresentador, &encontrado);

                int ok = 1;

                if (!ap || !encontrado) {
                    printf("Apresentador nao encontrado.\n");
                    ok = 0;
                }

                /* 2) pertence à categoria? */
                if (ok && ap->info.ondeTrabalha != categoriaSelecionada->tipo) {
                    printf("Apresentador nao pertence a esta categoria.\n");
                    ok = 0;
                }

                /* 3) já tem programa nessa categoria/stream? */
                if (ok && programasContemApresentador(*raizProgramas, ap->info.nome)) {
                    printf("Apresentador ja possui programa nesta categoria/stream.\n");
                    ok = 0;
                }

                /* 4) vínculo de stream atual (transferência/histórico) */
                if (ok && ap->info.streamAtual != stream) {
                    if (ap->info.streamAtual) {
                        /* trabalha em outra stream: ver se já apresenta lá na MESMA categoria */
                        Categorias *catAtual = encontrarCategoriaPorTipoNaStream(ap->info.streamAtual, ap->info.ondeTrabalha);
                        if (catAtual && programasContemApresentador(catAtual->programas, ap->info.nome)) {
                            printf("Apresentador ja apresenta um programa na stream atual. Transferencia bloqueada.\n");
                            ok = 0;
                        } else {
                            int dataTermino, dataInicio;
                            printf("Digite data de termino na stream atual (AAAAMMDD): ");
                            scanf("%d", &dataTermino);
                            finalizarUltimoHistoricoSeAberto(ap->info.historico, dataTermino);

                            InfoHistorico historico;
                            strncpy(historico.nomeStream, stream->info.nomeStream, sizeof historico.nomeStream);
                            historico.nomeStream[sizeof historico.nomeStream - 1] = '\0';
                            printf("Digite data de inicio nesta stream (AAAAMMDD): ");
                            scanf("%d", &dataInicio);
                            historico.dataInicio  = dataInicio;
                            historico.dataTermino = 0;

                            inserirHistorico(&ap->info.historico, &historico);
                            ap->info.streamAtual = stream;
                        }
                    } else {
                        /* não trabalha em lugar nenhum: cria histórico direto */
                        int dataInicio;
                        InfoHistorico historico;
                        strncpy(historico.nomeStream, stream->info.nomeStream, sizeof historico.nomeStream);
                        historico.nomeStream[sizeof historico.nomeStream - 1] = '\0';
                        printf("Digite data de inicio nesta stream (AAAAMMDD): ");
                        scanf("%d", &dataInicio);
                        historico.dataInicio  = dataInicio;
                        historico.dataTermino = 0;

                        inserirHistorico(&ap->info.historico, &historico);
                        ap->info.streamAtual = stream;
                    }
                }

                /* 5) se tudo ok, cadastrar o programa e amarrar apresentador */
                if (ok) {
                    infoProgramas dados = preencherDadosPrograma();
                    strncpy(dados.nomeApresentador, ap->info.nome, sizeof dados.nomeApresentador);
                    dados.nomeApresentador[sizeof dados.nomeApresentador - 1] = '\0';

                    Programas *prog = alocarProgramas(dados);
                    if (!prog) {
                        printf("Falha ao alocar programa.\n");
                    } else {
                        int res = inserirProgramas(raizProgramas, prog);
                        if (res == 1) {
                            printf("Programa cadastrado com sucesso.\n");
                        } else {
                            printf("Programa ja cadastrado.\n");
                            free(prog); // evita vazamento se não inserir
                        }
                    }
                }
                break;
            }

            case 2:
                printf("===Catalogo de Programas===\n");
                mostrarProgramas(*raizProgramas);
                printf("\n");
                break;

            case 3: {
                char nomePrograma[TAM_STRING];
                printf("Digite nome do Programa: ");
                scanf("%49s", nomePrograma);

                Programas *auxPrograma = buscarProgramas(*raizProgramas, nomePrograma);
                if (auxPrograma) {
                    printf("\n\nPrograma: %s \n\n", auxPrograma->infoProgramas.nomePrograma);
                } else {
                    printf("Programa nao cadastrado.\n");
                }
                break;
            }
            case 4:
                menuApresentadores(&listaApresentadores);
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

            case 1: { // Adicione a chave de abertura aqui
                InfoApresentador dadosApre = preencherDadosApresentador();

                Apresentadores *novo = alocarApresentador();
                if (novo != NULL) {
                    strcpy(novo->info.nome, dadosApre.nome);
                    novo->info.streamAtual = dadosApre.streamAtual;
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
            } // Adicione a chave de fechamento aqui
            
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
                if (*listaApresentadores == NULL) 
                {
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
                    const char *nomeStreamAtual;

                    if (ap->info.streamAtual != NULL &&
                        ap->info.streamAtual->info.nomeStream[0] != '\0') {
                        nomeStreamAtual = ap->info.streamAtual->info.nomeStream;
                    } else {
                        nomeStreamAtual = "(sem stream)";
                    }

                    printf("Encontrado: Nome: %s | Stream Atual: %s | Categoria: %d\n",
                        ap->info.nome, nomeStreamAtual, ap->info.ondeTrabalha);
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
        do 
        {
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

            case 1: { // Adicione a chave de abertura aqui
                InfoHistorico historico = preencherDadosHistorico();
                int ok = inserirHistorico(&ap->info.historico, &historico);
                if (ok) {
                    printf("Informacoes cadastradas no historico.\n");
                } else {
                    printf("Falha ao inserir informacoes.\n");
                }
                break;
            } // Adicione a chave de fechamento aqui

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


Categorias* encontrarCategoriaPorTipoNaStream(Stream *stream, Tipo tipo)
{
    Categorias *resultado = NULL;

    if (stream) {
        Categorias *cat = stream->info.categoria;
        while (cat != NULL && resultado == NULL) {
            if (cat->tipo == tipo) {
                resultado = cat;        // guarda e continua condição encerra
            } else {
                cat = cat->prox;
            }
        }
    }

    return resultado; 
}


int programasContemApresentador(Programas *raiz, const char *nomeApresentador)
{
    int achou = 0;

    if (raiz) {
        if (strcmp(raiz->infoProgramas.nomeApresentador, nomeApresentador) == 0) {
            achou = 1;
        } else {
            if (programasContemApresentador(raiz->esq, nomeApresentador)) {
                achou = 1;
            } else if (programasContemApresentador(raiz->dir, nomeApresentador)) {
                achou = 1;
            }
        }
    }

    return achou; // único return
}


void finalizarUltimoHistoricoSeAberto(Historico *hist, int dataTermino)
{
    Historico *ultimo = hist;

    if (ultimo) {
        while (ultimo->prox) {
            ultimo = ultimo->prox;
        }
        if (ultimo->info.dataTermino == 0) {
            ultimo->info.dataTermino = dataTermino;
        }
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