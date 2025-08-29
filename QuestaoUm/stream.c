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

Stream *buscarStream(Stream *raiz, char nomedastream)
{
    int retorno = 0;
    Stream *aux = raiz;
    if (raiz)
    {
        int compara = strcpy(nomedastream, aux->info.nomeStream);

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
void mostrarProgDeCatDeStream(Categorias *categoria, Stream *stream, char nomeCategoria, char nomeStream, Programas *programas)
{
    if (stream)
    {
        Stream *streamBuscada = buscarStream(stream->info.nomeStream, nomeStream);
        
        if (streamBuscada->info.categoria)
        {
            Categorias *categoriaBuscada = buscarCategoria(categoria->nomeCategoria, nomeCategoria);

            if (categoriaBuscada->programas)
            {
                mostrarProgramas(programas);
            }   
        }
    }
}

// viii)Mostrar todas as streams que tem uma determinada categoria.
void mostrarStreamDeCategoria(Stream *stream, Categorias *categoria, char nomeDaCategoria)
{
    if (categoria)
    {
        Categorias *categoriaBuscada = buscarCategoria(categoria, nomeDaCategoria);
        
    }
    
}
// declara as funções que você já tem

// void imprimirInOrdem(Stream *raiz) {
//     if (raiz != NULL) {
//         imprimirInOrdem(raiz->esq);
//         printf("Stream: %s | Site: %s\n", raiz->info.nomeStream, raiz->info.nomeSite);
//         imprimirInOrdem(raiz->dir);
//     }
// }

// int main() {
//     Stream *raiz = CriarStream();

//     // Inserir 3 streams
//     printf("=== Inserindo Streams ===\n");
//     for (int i = 0; i < 5; i++) {
//         InfoStream dados = preencherDadosStream();
//         Stream *no = alocarNoStream(dados);
//         InserirStream(&raiz, no);
//     }

//     printf("\n--- Árvore em ordem (alfabética) ---\n");
//     imprimirInOrdem(raiz);

//     // Remover uma stream
//     char nomeRemover[50];
//     printf("\nDigite o nome da Stream para remover: ");
//     scanf("%s", nomeRemover);

//     remover(&raiz, nomeRemover);

//     printf("\n--- Árvore após remoção ---\n");
//     imprimirInOrdem(raiz);

//     return 0;
// }
