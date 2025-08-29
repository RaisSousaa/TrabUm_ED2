#ifndef CATEGORIAS_H
#define CATEGORIAS_H

#include "programas.h"

typedef struct Programas programas;


typedef enum Tipo {
    Esporte = 1, 
    Noticia,
    Entreterimento,
    Cultura
}Tipo;

const char *tipos_char = {
    "Esporte",
    "Noticia",
    "Entreterimento",
    "Cultura"
};

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
Categorias *buscarCategoria(Categorias *categoria, char *buscarCat);

#endif