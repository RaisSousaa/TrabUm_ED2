#ifndef CATEGORIAS_H
#define CATEGORIAS_H

#include "tipos.h"

/*
Amiga, eu só tirei isso pq eu tinha um mesmo enum, ai como dava muito erro, eu adicionei tipos.h 
que usa o mesmo enum. deixei aqui só pra tu ver, depois apaga.
*/


// #include "programas.h"

// typedef struct Programas programas;


// typedef enum Tipo {
//     Esporte = 1, 
//     Noticia,
//     Entretenimento,
//     Cultura
// }Tipo;

// extern char *tipos_char[];

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

/* menu */
void menuCategoria(Stream *stream, Apresentadores *listaApresentadores);

#endif
