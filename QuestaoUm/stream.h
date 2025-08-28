#ifndef STREAM_H
#define STREAM_H

#include "categorias.h"

typedef struct Categoria Categoria;

typedef struct InfoStream
{
    char nomeStream[50];
    char nomeSite[50];
}InfoStream;

typedef struct Stream{
    InfoStream info;
    struct Stream *esq, *dir;
    Categoria *categoria;
}Stream;

#endif