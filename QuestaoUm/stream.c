#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "stream.h"

Stream *CriarStream()
{
    return NULL;
}

Stream *alocarNoStream(InfoStream stream)
{
    Stream *no = (Stream*) malloc(sizeof(Stream));
    if (no == NULL)
    {
        printf("Erro ao alocar memoria\n");

    }
    else
    {
        no->dir = NULL;
        no->esq = NULL;
        no->info = stream;
    }
    return no;
}


InfoStream preencherDadosStream()
{
    InfoStream dados;
    printf("Digite o nome da Stream:\n");
    scanf("%s", dados.nomeStream);
    printf("Digite o nome do site:\n");
    scanf("%s", dados.nomeSite);
    return dados;
}


int InserirStream(Stream **raiz, Stream *no) 
{
    int inseriu = 0;
    if (!(*raiz)) // verifica se e nulo
    // tem um ponteiro pois estou acessando o conteudo da no atual da Streamore
    {
        *raiz = no; //A percorrer ate o nulo para adicionar o no
        inseriu = 1;
    }
    else
    {

        int compara = strcmp(no->info.nomeStream, (*raiz)->info.nomeStream);

        if (compara < 0)
            inseriu = InserirStream(&(*raiz)->esq, no);
        else if (compara > 0)
            inseriu = InserirStream(&(*raiz)->dir, no);
    }

    return inseriu;
}


int ehFolha(Stream *raiz) {
    return (raiz->esq == NULL && raiz->dir == NULL);
}// vi) Mostrar todas as categorias cadastradas para uma determinada stream.


Stream *soUmFilho(Stream *no) {
    if (no->esq == NULL && no->dir != NULL) {
        return no->dir;
    } else if (no->esq != NULL && no->dir == NULL) {
        return no->esq;
    } else {
        return NULL;
    }
}

Stream* maiorValor(Stream* no) {
    Stream* aux = no;
    while (aux->dir != NULL) {
        aux = aux->dir;
    }
    return aux;
}

int remover(struct Stream **raiz, char *stream_remove) {
    if (*raiz) {
        if (strcmp(stream_remove, (*raiz)->info.nomeStream) < 0) {
            remover(&(*raiz)->esq, stream_remove);
        } else if (strcmp(stream_remove, (*raiz)->info.nomeStream) > 0) {
            remover(&(*raiz)->dir, stream_remove);
        } else {
            Stream *aux;
            if (ehFolha(*raiz)) {
                aux = *raiz;
                *raiz = NULL;
                free(aux);
            } else {
                Stream *filho;
                if ((filho = soUmFilho(*raiz)) != NULL) {
                    aux = *raiz;
                    *raiz = filho;
                    free(aux);
                } 
                else {
                    Stream *Mesq = maiorValor((*raiz)->esq);
                    strcpy((*raiz)->info.nomeStream, Mesq->info.nomeStream);
                    strcpy((*raiz)->info.nomeSite, Mesq->info.nomeSite);
                    remover(&(*raiz)->esq, Mesq->info.nomeStream);
                }
            }

        }
    }
    return 0;
}

// v) Mostrar todas as streams cadastradas.
void mostrarStreams(Stream *raiz)
{
    if (raiz)
    {
        mostrarStreams(raiz->esq);
        printf("Stream: %s\n", raiz->info.nomeStream);
        mostrarStreams(raiz->dir);
    }
}

Stream *buscarStream(Stream *raiz, char *nomedastream)
{
    int retorno = 0;
    Stream *aux = raiz;
    if (raiz)
    {
        int compara = strcmp(nomedastream, aux->info.nomeStream);

        if (compara == 0) {
            retorno = 1;
        } 
        else if (compara < 0) 
        {
            buscarStream(aux->esq, nomedastream);
        } 
        else if (compara > 0)
        {
            buscarStream(aux->dir, nomedastream);
        }
    }
    return aux;
}

// vi) Mostrar todas as categorias cadastradas para uma determinada stream.
void mostrarCategoriasStream(Stream *raiz, char *nomeStream)
{
    if (raiz)
    {
        int compara = strcmp(raiz->info.nomeStream, nomeStream);

        if (compara == 0)
        {
            mostrarCategorias(raiz->info.categoria);
        }
        else if (compara < 0)
        {
            mostrarCategoriasStream(raiz->esq, nomeStream);
        }
        else
        {
            mostrarCategoriasStream(raiz->dir, nomeStream);
        }
    }    
}


// vii) Mostrar todos os programas de uma determinada categoria de uma determinada stream.
void mostrarProgDeCatDeStream(Categorias *categoria, Stream *stream, char *nomeCategoria, char *nomeStream, Programas *programas)
{
    if (stream)
    {
        Stream *streamBuscada = buscarStream(stream, nomeStream);
        
        if (streamBuscada->info.categoria)
        {
            Categorias *categoriaBuscada = buscarCategoria(categoria, nomeCategoria);

            if (categoriaBuscada->programas)
            {
                mostrarProgramas(programas);
            }   
        }
    }
}

// viii)Mostrar todas as streams que tem uma determinada categoria.
void mostrarStreamDeCategoria(Stream *stream, Categorias *categoria, char *nomeDaCategoria)
{
    if (stream)
    {
        int comparaStream = strcmp(stream->info.categoria->nomeCategoria, nomeDaCategoria);
        if (comparaStream == 0)
        {
            printf("Stream: %s\n", stream->info.nomeStream);
        }
        else if (comparaStream < 0)
        {
            mostrarStreamDeCategoria(stream->esq, categoria, nomeDaCategoria);
        }
        else 
        {
            mostrarStreamDeCategoria(stream->dir, categoria, nomeDaCategoria);
        }
    }
}


void imprimirInOrdem(Stream *raiz) {
    if (raiz != NULL) {
        imprimirInOrdem(raiz->esq);
        printf("Stream: %s | Site: %s\n", raiz->info.nomeStream, raiz->info.nomeSite);
        imprimirInOrdem(raiz->dir);
    }
}

// xvi) Permita remover uma categoria de uma stream, só pode ser removida se não tiver nenhum programa
//cadastrado nela.

int removerCategoriaDaStream(Stream **stream, char *categoriasremover)
{
    int removeu = 0;
    Categorias* categoriabuscada = buscarCategoria((*stream)->info.categoria, categoriasremover);

    if (categoriabuscada)
    {
        if (categoriabuscada->programas == NULL )
        {
            removerCategoriaDaStream(stream, categoriasremover);
            removeu = 1;
        }
    }
    return removeu;
}



// int main() {
//     Stream *raiz = CriarStream();
//     int opcao;
//     char nomeBusca[50];
//     char nomeRemover[50];

//     do {
//         printf("\n===== MENU STREAM =====\n");
//         printf("1 - Inserir Stream\n");
//         printf("2 - Mostrar Streams (ordem alfabetica)\n");
//         printf("3 - Buscar Stream\n");
//         printf("4 - Remover Stream\n");
//         printf("0 - Sair\n");
//         printf("Escolha: ");
//         scanf("%d", &opcao);

//         switch (opcao) {
//             case 1: {
//                 InfoStream dados = preencherDadosStream();
//                 Stream *no = alocarNoStream(dados);
//                 if (InserirStream(&raiz, no))
//                     printf("Stream inserida com sucesso!\n");
//                 else
//                     printf("Stream já existe!\n");
//                 break;
//             }
//             case 2:
//                 printf("\n--- Lista de Streams ---\n");
//                 imprimirInOrdem(raiz);
//                 break;
//             case 3:
//                 printf("Digite o nome da Stream para buscar: ");
//                 scanf("%s", nomeBusca);
//                 {
//                     Stream *resultado = buscarStream(raiz, nomeBusca);
//                     if (resultado)
//                         printf("Encontrada: %s | Site: %s\n", 
//                                resultado->info.nomeStream, resultado->info.nomeSite);
//                     else
//                         printf("Stream não encontrada!\n");
//                 }
//                 break;
//             case 4:
//                 printf("Digite o nome da Stream para remover: ");
//                 scanf("%s", nomeRemover);
//                 remover(&raiz, nomeRemover);
//                 printf("Se existia, a Stream foi removida.\n");
//                 break;
//             case 0:
//                 printf("Encerrando programa...\n");
//                 break;
//             default:
//                 printf("Opção inválida!\n");
//         }
//     } while (opcao != 0);

//     return 0;
// }



