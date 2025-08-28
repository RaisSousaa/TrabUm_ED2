#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "stream.h"

Stream *CriarArv()
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
    return dados;
}


void InserirElemento(Stream **raiz, Stream *no) 
{
    if (!*raiz) // verifica se e nulo
    // tem um ponteiro pois estou acessando o conteudo da no atual da arvore
    {
        *raiz = no; //A percorrer ate o nulo para adicionar o no
    }
    else
    {
        if ()
        {
            /* code */
        }
        
        if (no->info.nomeStream < (*raiz)->info.nomeStream)
        {
            InserirElemento(&((*raiz)->esq), no);
        }
        else
        {
            InserirElemento(&((*raiz)->dir), no);
        }
    }
}

