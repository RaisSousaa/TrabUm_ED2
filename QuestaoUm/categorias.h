#ifndef CATEGORIAS_H
#define CATEGORIAS_H

#include "programas.h"

typedef struct Programa programa;

typedef enum Tipo {
    Esporte, 
    Noticia,
    Entreterimento,
    Cultura
}Tipo;

typedef struct Categorias
{
    Tipo tipo;
    char nomeCategoria[50];
    Programas *programas;
}Categorias;


#endif