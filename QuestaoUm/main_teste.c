#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"apresentadores.h"
#include"categorias.h"
#include"historico.h"
#include"programas.h"
#include"stream.h"




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

 //sugestão chat para não deixar com printf dentro de uma função só
void imprimirApresentadorLinha(const Apresentadores *apresentador) {
    printf("Nome: %s | Stream: %s | Categoria (id): %d\n",
           apresentador->info.nome,
           apresentador->info.streamAtual,
           apresentador->info.ondeTrabalha);
}

/* 
   xii) Mostrar todos os apresentadores de uma determinada stream.
*/
void mostrarApresentadoresPorStream(Apresentadores *listaApresentadores, const char *nomeStream) {
    int encontrou = 0;

    if (listaApresentadores && nomeStream) {
        Apresentadores *atual = listaApresentadores;

        do {
            if (atual->info.streamAtual && strcmp(atual->info.streamAtual, nomeStream) == 0) {
                imprimirApresentadorLinha(atual);
                encontrou = 1;
            }
            atual = atual->prox;
        } while (atual && atual != listaApresentadores);
    }

    if (!encontrou) {
        printf("Nenhum apresentador encontrado para a stream '%s'.\n", nomeStream);
    }
}

/* 
   xiii) Mostrar todos os apresentadores de uma determinada categoria 
   (independente da stream).
*/
void mostrarApresentadoresPorCategoria(Apresentadores *listaApresentadores, int categoriaId) {
    int encontrou = 0;

    if (listaApresentadores) {
        Apresentadores *atual = listaApresentadores;

        do {
            if (atual->info.ondeTrabalha == categoriaId) {
                imprimirApresentadorLinha(atual);
                encontrou = 1;
            }
            atual = atual->prox;
        } while (atual && atual != listaApresentadores);
    }

    if (!encontrou) {
        printf("Nenhum apresentador encontrado para a categoria id=%d.\n", categoriaId);
    }
}


void menuCategoria(Stream *stream, Categorias *categorias, Stream *streams)
{
    Categorias *noCategoria = criarCategoria();
    Categorias *categorias;

    Programas *programas;

    int opcao;

    do
    {
        printf("0 - Sair\n");
        printf("1 - Cadastrar Categoria\n");
        printf("2 - Mostrar Categoria\n");
        printf("3 - Buscar Categoria\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);


        switch (opcao)
        {
        case 1:
            /* cadastrar categoria */
            
            //insere
            Categorias *lista = criarCategoria();
            Categorias  *nomeCategoria[TAM_STRING];

        


            break;
        case 2:
            /* mostrar categoria */
            printf("===Catalogo Categoria===\n");
            mostrarStreams(noCategoria);
            break;

        case 3:
            /* buscar categoria e entrar no menu programas */
            char nomeCategoria[TAM_STRING];
            printf("Digite nome da Categoria: "); scanf("%s", nomeCategoria);
            Categorias *auxCategoria = buscarStream(noCategoria, nomeCategoria);

            int cmp = strcmp( nomeCategoria, noCategoria->nomeCategoria);

            if (cmp == 0)
            {
                printf("\nCategoria: %s\n\n", auxCategoria->nomeCategoria);
                printf("===Menu para Categoria===\n\n");
                //criar menu de categoria e chamar aqui
                //menuCategoria(auxCategoria, categoria, stream);

            }else printf("Categoria não cadastrada!\n");

            break;
        default:
            break;
        }
    } while (opcao != 0);
    


    
} 


int main()
{
    Stream *raizStream = NULL;
    InfoStream dados;
    Stream *stream;
    
    Categorias *categoria;
    int opcao;


    do
    {
        printf("0 - Sair\n");
        printf("1 - Cadastrar Stream\n");
        printf("2 - Mostrar Stream\n");
        printf("3 - Buscar Stream\n");
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
            break;

        case 3:
            char nomeStream[TAM_STRING];
            printf("Digite nome da Stream: "); scanf("%s", nomeStream);
            Stream *auxStream = buscarStream(raizStream, nomeStream);

            int cmp = strcmp( nomeStream, raizStream->info.nomeStream);

            if (cmp == 0)
            {
                printf("\n\nStream: %s\n\n", auxStream->info.nomeStream);
                printf("===Menu para Categoria===\n\n");
                //criar menu de categoria e chamar aqui
                menuCategoria(auxStream, categoria, stream);

            }else printf("Stream não cadastrada!\n");
            
            break;
        default:
            printf("Opção inválida.\n");
          break;
        }


    } while (opcao != 0);
    


    return 0;
}