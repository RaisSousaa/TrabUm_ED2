#ifndef CATEGORIAS_H
#define CATEGORIAS_H

typedef enum Tipo {
    Esporte, 
    Noticia,
    Entreterimento,
    Cultura
}Tipo;

typedef struct InfoCategoria {
    Tipo tipo;
    

}InfoCategoria;

typedef struct Categorias
{
    InfoCategoria info;
    
}Categorias;


#endif