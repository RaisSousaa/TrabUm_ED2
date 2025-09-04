#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stream.h"
#include "categorias.h"


void menuStreams();
void menuCategorias();

int main() {
    Stream *raiz = CriarStream();
    int opcao;

    do {
        printf("\n==============================\n");
        printf("  SISTEMA DE STREAMS\n");
        printf("==============================\n");
        printf("1. Gerenciar Streams\n");
        printf("2. Gerenciar Categorias\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: menuStreams(&raiz); break;
            case 2: menuCategorias(&raiz); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while(opcao != 0);

    return 0;
}

// ---------------- STREAMS ----------------
void menuStreams(Stream **raiz)
{
    Categorias *lista;
    int opcao;
    
    do
    {
        printf("1. Cadastrar strem\n");
        printf("2. Mostrar Stream\n");
        printf("3. Mostrar streams que tem uma determinada categoria\n");
        printf("4. Mostrar as streams que tem uma determinada categoria\n");
        printf("0. voltar\n");
        scanf("%d", &opcao);   
        
        switch (opcao)
        {
        //i) Cadastrar Stream: cadastrar dados de streams organizados em uma árvore binária pelo nome da stream, o usuário pode //cadastrar uma stream a qualquer momento, não permita cadastro repetido.
            case 1:
            {
                InfoStream dados = preencherDadosStream();
                Stream *novoNo = alocarNoStream(dados);
                if(InserirStream(raiz, novoNo))
                    printf("Stream cadastrada!\n");
                else
                    printf("A stream nao foi cadastrada pois ja existe!\n");

                break;
            }

            // v) Mostrar todas as streams cadastradas.
            case 2:
            {
                if (*raiz)
                    imprimirInOrdem(*raiz);
                else
                    printf("Nenhuma stream cadastrada.\n");
                break;
            }
            // case 3:
            // {
            //     char streamRemover[50];
            //     printf("Digite o nome da stream para remover:\n");
            //     setbuf(stdin, NULL); // limpar o buff
            //     scanf("%[^\n]", streamRemover);
            //     remover(&raiz, streamRemover);   
            //     break;    
            // }

            //viii)Mostrar todas as streams que tem uma determinada categoria.
            case 3:
            {
                char nomecategoria[50];
                printf("Digite o nome da categoria:\n");
                setbuf(stdin, NULL);
                scanf("%[^\n]", nomecategoria);
                mostrarStreamDeCategoria(*raiz, nomecategoria);
                break;
            }

            // x) Mostrar todas as streams que tem um determinado tipo de categoria.
            case 4:
            {
                int escolha = 0;
                printf("Escolha o tipo da categoria: \n");
                printf("1 - Esporte \n");
                printf("2 - Noticia \n");
                printf("3 - Entretenimento \n");
                printf("4 - Cultura \n");
                printf("Sua escolha -> ");
                scanf("%d", &escolha);
                mostrarStreamDoTipoCategoria(*raiz, escolha);
                break;
            }

            case 0: break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
    
}

// ---------------- CATEGORIAS ----------------
void menuCategorias(Stream **raiz)
{
    Stream *streamBuscada = CriarStream();
    int opcao;
    int inseriu;
    char nomeStream[50];
    char nomeCategoria[50];
    
    do
    {
        printf("\n=== MENU DE CATEGORIAS ===\n");
        printf("1. Cadastrar Categoria em uma Stream\n");
        printf("2. Mostrar Categorias de uma Stream\n");
        printf("3. Mostrar Programas de uma Categoria de uma Stream\n");
        printf("4. Remover Categoria (somente se nao tiver programas)\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); 

        switch (opcao)
        {
            // ii) Cadastrar Categoria
            case 1:
            {

                printf("Digite o nome da stream: ");
                scanf("%[^\n]", nomeStream);
                streamBuscada = buscarStream(*raiz, nomeStream);

                if (streamBuscada)
                {
                    Categorias *novoNo = alocarMemoriaNo();
                    prencherCategoria(novoNo);
                    inseriu = inserirCategoria(&(streamBuscada)->info.categoria, novoNo);
                }
                else 
                {
                    printf("Stream nao existe!\n");
                }
                break;
            }

            case 2:
            {
                printf("Digite o nome da stream: ");
                setbuf(stdin, NULL);
                scanf("%[^\n]", nomeStream);
                streamBuscada = buscarStream(*raiz, nomeStream);
                
                if (streamBuscada)
                {
                    mostrarCategorias(streamBuscada->info.categoria);
                }
                else
                {
                    printf("Nao tem categorias cadastradas!\n");
                }
                break;
            }

            case 3:
            {
                printf("Digite o nome da stream:\n");
                setbuf(stdin, NULL);
                scanf("%[^\n]", nomeStream);
                streamBuscada = buscarStream(*raiz, nomeStream);

                printf("Digite o nome da categoria:\n");
                setbuf(stdin, NULL);
                scanf("%[^\n]", nomeCategoria);
                Categorias *categoriabuscada = buscarCategoria(streamBuscada->info.categoria, nomeCategoria);

                if (categoriabuscada)
                {
                    mostrarProgramas((*raiz)->info.categoria->programas);
                }
                else
                {
                    printf("Nao existe programas cadastrados\n");
                }
                break;
            }
            case 4:
            {
                printf("Digite o nome da stream: ");
                setbuf(stdin, NULL);
                scanf("%[^\n]", nomeStream);
                streamBuscada = buscarStream(*raiz, nomeStream);

                printf("Digite o nome da categoria:\n");
                setbuf(stdin, NULL);
                scanf("%[^\n]", nomeCategoria);
                Categorias *categoriabuscada = buscarCategoria(streamBuscada->info.categoria, nomeCategoria);

                if (categoriabuscada)
                {
                    if(!categoriabuscada->programas)
                    {
                        removerCategoria(&categoriabuscada, nomeCategoria);
                    }
                }
                break;
            }
            case 0:
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);
}
