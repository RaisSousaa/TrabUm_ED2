#ifndef STREAM_H
#define STREAM_H

#include "categorias.h"
#include "programas.h"

typedef struct Categorias Categorias;

typedef struct InfoStream
{
    char nomeStream[50];
    char nomeSite[50];
    Categorias *categoria;
}InfoStream;

typedef struct Stream{
    InfoStream info;
    struct Stream *esq, *dir;
}Stream;

Stream *CriarStream();
Stream *alocarNoStream(InfoStream stream);
InfoStream preencherDadosStream();
int InserirStream(Stream **raiz, Stream *no);
int remover(struct Stream **raiz, char *stream_remove);

#endif