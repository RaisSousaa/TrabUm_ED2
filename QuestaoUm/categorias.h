#ifndef CATEGORIAS_H
#define CATEGORIAS_H

#include "programas.h"

typedef struct Programa programa;


typedef enum Tipo {
    Esporte = 1, 
    Noticia,
    Entreterimento,
    Cultura
}Tipo;

typedef struct Categorias
{
    Tipo tipo;
    char nomeCategoria[50];
    struct Categorias *prox;
    Programas *programas;
}Categorias;

void prencherCategoria(Categorias *no);
void inserirCategoria(Categorias **lista, Categorias *no);
Categorias *alocarMemoriaNo();
void mostrarCategorias(Categorias *lista);

#endif