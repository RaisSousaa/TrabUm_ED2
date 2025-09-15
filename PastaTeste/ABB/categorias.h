#ifndef CATEGORIAS_H
#define CATEGORIAS_H

#include "tipos.h"


typedef struct Stream Stream;
typedef struct Apresentadores Apresentadores;
typedef struct Programas Programas;

typedef struct Categorias {
    Tipo tipo;
    char nomeCategoria[50];
    struct Categorias *prox;
    Programas *programas;
} Categorias;



Categorias *alocarMemoriaNo(void);
void prencherCategoria(Categorias *no);          
int inserirCategoria(Categorias **inicio, Categorias *novo);
void mostrarCategorias(Categorias *inicio);     
Categorias *buscarCategoria(Categorias *categoria, char *buscarCat);
void removerCategoria(Categorias **categoria, char *nomeCategoria);
Categorias* encontrarCategoriaPorTipoNaStream(Stream *stream, Tipo tipo);

/* menu */
void menuCategoria(Stream *stream, Apresentadores **listaApresentadores, Stream *raizStream);
#endif
