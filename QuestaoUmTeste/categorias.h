#ifndef CATEGORIAS_H
#define CATEGORIAS_H


typedef struct Stream Stream;       
typedef struct Categorias Categorias;
typedef struct Programas Programas;


typedef enum Tipo {
    Esporte = 1, 
    Noticia = 2,
    Entreterimento = 3,
    Cultura = 4
}Tipo;

extern char *tipos_char[];

typedef struct Categorias
{
    Tipo tipo;
    char nomeCategoria[50];
    struct Categorias *prox;
    Programas *programas;
}Categorias;

Categorias* alocarCategorias(void);
Categorias preencherDadosCategoria(void);
int inserirCategoria(Categorias **inicio, Categorias *novo);
void mostrarCategorias(const Categorias *inicio);
Categorias *buscarCategoria(Categorias *categoria, char *buscarCat);
void menuCategoria(Stream *stream, Apresentadores *listaApresentadores);

#endif