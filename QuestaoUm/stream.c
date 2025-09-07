#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "stream.h"

Stream *CriarStream()
{
    return NULL;
}

// alocacao do no da arvore
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
        no->info.categoria = NULL; // importante!
    }
    return no;
}



// Preenche o no da arvore
InfoStream preencherDadosStream()
{
    InfoStream dados;
    printf("Digite o nome da Stream:\n");
    setbuf(stdin, NULL);
    scanf("%[^\n]", dados.nomeStream);
    printf("Digite o nome do site:\n");
    setbuf(stdin, NULL);
    scanf("%[^\n]", dados.nomeSite);
    dados.categoria = NULL; 
    return dados;
}


//Insere o no da arvore
int InserirStream(Stream **raiz, Stream *no) 
{
    int inseriu = 0;
    if (!(*raiz)) 
    {
        *raiz = no; 
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



// Buscar stream
Stream *buscarStream(Stream *raiz, char *nomedastream)
{
    Stream *resultado = NULL;

    if (raiz != NULL) {
        int comparastream = strcmp(nomedastream, raiz->info.nomeStream);

        if (comparastream == 0) {
            resultado = raiz;
        } else if (comparastream < 0) {
            resultado = buscarStream(raiz->esq, nomedastream);
        } else {
            resultado = buscarStream(raiz->dir, nomedastream);
        }
    }
    return resultado;
}


// vi) Mostrar todas as categorias cadastradas para uma determinada stream.
void mostrarCategoriasStream(Stream *raiz, char *nomeStream)
{
    if (raiz) 
    {
        int compara = strcmp(raiz->info.nomeStream, nomeStream);

        if (compara == 0) // achou a stream desejada
        {
            mostrarCategorias(raiz->info.categoria);
        }
        else if (compara > 0) // percorre a esquerda
        {
            mostrarCategoriasStream(raiz->esq, nomeStream);
        }
        else // percorre a direita
        {
            mostrarCategoriasStream(raiz->dir, nomeStream);
        }
    }

    return;
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
void mostrarStreamDeCategoria(Stream *raiz, char *nomeDaCategoria)
{
    int encontrou = 0;

    if (raiz != NULL)
    {
        // percorre esquerda
        mostrarStreamDeCategoria(raiz->esq,  nomeDaCategoria);

        // verifica categorias desta stream
        Categorias *cat = raiz->info.categoria;
        if (cat != NULL) 
        {
            Categorias *aux = cat;
            do {
                if (strcmp(aux->nomeCategoria, nomeDaCategoria) == 0) {
                    encontrou = 1;
                }
                aux = aux->prox;
            } while (aux != cat && encontrou == 0);
        }

        if (encontrou) {
            printf("Stream: %s | Site: %s\n", raiz->info.nomeStream, raiz->info.nomeSite);
        }

        // percorre direita
        mostrarStreamDeCategoria(raiz->dir,  nomeDaCategoria);
    }

    return;  // único return
}


//x) Mostrar todas as streams que tem um determinado tipo de categoria.
void mostrarStreamDoTipoCategoria(Stream *stream, int nometipocategoria)
{
    int achou = 0; // flag para indicar se a stream possui a categoria do tipo buscado

    if (stream) 
    {
        Categorias *aux = stream->info.categoria;

        if (aux) 
        {
            Categorias *inicio = aux;
            do 
            {
                if (aux->tipo == nometipocategoria)
                {
                    achou = 1; // marca que encontrou
                }
                aux = aux->prox;
            } while (aux != inicio && achou == 0); // percorre até voltar ao início ou achar a categoria
        }

        if (achou) 
        {
            printf("Stream: %s\n", stream->info.nomeStream);
        }

        mostrarStreamDoTipoCategoria(stream->esq, nometipocategoria);
        mostrarStreamDoTipoCategoria(stream->dir, nometipocategoria);
    }

    return;
}



// v) Mostrar todas as streams cadastradas.
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
    Categorias *categoriabuscada = NULL;

    if (stream != NULL && *stream != NULL)
    {
        categoriabuscada = buscarCategoria((*stream)->info.categoria, categoriasremover);

        if (categoriabuscada != NULL)
        {
            if (categoriabuscada->programas == NULL)
            {
                removerCategoria(&(*stream)->info.categoria, categoriasremover);
                removeu = 1;
            }
        }
    }

    return removeu; // único return
}


