#ifndef PROGRAMAS_H
#define PROGRAMAS_H

typedef enum Periocidade
{
    Diario,
    Semanal,
    Mensal
}Periocidade;

typedef enum Gravacao
{
    AoVivo,
    SobDemanda
}Gravacao;

typedef struct infoProgramas
{
    int nomePrograma;
    Periocidade periocidade;
    float duracao;
    float tempoInicio;
    Gravacao gravacao;
    char nomeApres[50];
} infoProgramas;

typedef struct Programas
{

    struct Programas *esq, *dir;
}Programas;


#endif