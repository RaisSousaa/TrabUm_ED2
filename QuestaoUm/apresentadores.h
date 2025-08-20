#ifndef APRESENTADORES_H
#define APRESENTADORES_H

typedef struct InfoHistorico
{
    char nomeStream[50];
    int dataIn, dataTermino;
}InfoHistorico;


typedef struct Historico
{
    struct Historico *prox;
}Historico;

typedef enum Categoria 
{
    Esporte, 
    Noticia,
    Entreterimento,
    Cultura
}Categoria;

typedef struct InfoApres
{
    Categoria ondeTrabalha;
    char nome[50];
    char streamAtual;

}InfoApres;


typedef struct Apresentadores
{
    InfoApres info;
    struct Apresentadores *prox, *ant;

}Apresentadores;



#endif