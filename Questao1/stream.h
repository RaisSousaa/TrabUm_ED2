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
void mostrarStreams(Stream *raiz);       //adicionei
Stream *buscarStream(Stream *raiz, const char *nomedastream);
void mostrarCategoriasStream(Stream *raiz, char *nomeStream);

//Questoes
void mostrarProgDeCatDeStream(Categorias *categoria, Stream *stream, char *nomeCategoria, char *nomeStream, Programas *programas);
void mostrarStreamDeCategoria(Stream *stream, char *nomeDaCategoria);
void imprimirInOrdem(Stream *raiz);
void mostrarStreamDoTipoCategoria(Stream *stream, int nometipocategoria);
void mostrarProgramasStreamPorPeriodicidadeEHorario(Stream *stream, Periocidade p, float h);
void mostrarProgramasDaCategoriaPorPeriodicidade(Stream *stream, const char *nomeCategoria, Periocidade periodicidade);
int removerProgramaDaCategoria(Categorias *categoria, const char *nomePrograma);
int removerProgramaDeCategoriaDaStream(Stream *raizStream, const char *nomeStream, const char *nomeCategoria, const char *nomePrograma);

int existeProgramaDoApresentadorNaStream(Stream *stream, const char *nomeApresentador);


#endif