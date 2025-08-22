#ifndef PROGRAMAS_H
#define PROGRAMAS_H

#define TAM_STRING 50

typedef enum Periocidade
{
    Diario = 1,
    Semanal = 2,
    Mensal = 3
}Periocidade;

typedef enum Gravacao
{
    AoVivo = 1,
    SobDemanda = 2
}Gravacao;

typedef struct infoProgramas
{
    char nomePrograma[TAM_STRING];
    Periocidade periocidade;
    float duracao;
    float tempoInicio;
    Gravacao gravacao;
    char nomeApresentador[50];
}infoProgramas;

typedef struct Programas
{

    struct Programas *esq, *dir;
    struct infoProgramas infoProgramas; // struct embutida
}Programas;


#endif
