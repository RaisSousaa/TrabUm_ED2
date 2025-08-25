#ifndef APRESENTADORES_H
#define APRESENTADORES_H

#define TAM_STRING 50

//lista 2
typedef struct InfoHistorico
{
    char nomeStream[50];
    int dataIn, dataTermino;
}InfoHistorico;


typedef struct Historico
{
    struct Historico *prox;
}Historico;

//lista 1
typedef enum Categoria 
{
    Esporte = 1, 
    Noticia = 2 ,
    Entreterimento = 3 ,
    Cultura = 4
}Categoria;

typedef struct InfoApresentador
{
    Categoria ondeTrabalha;
    char nome[TAM_STRING];
    char streamAtual[TAM_STRING];

}InfoApresentador;


typedef struct Apresentadores
{
    InfoApresentador info;
    struct Apresentadores *prox, *ant;

}Apresentadores;


//Funções de apresentadores
Apresentadores* alocarApresentador(void) ;
InfoApresentador preencherDadosApresentador(void);
int inserirApresentador(Apresentadores **inicio, Apresentadores *novo);
Apresentadores* buscarApresentadores(Apresentadores *inicio, const char *nome_busca, int *flag);
void imprimirApresentadores(Apresentadores *inicio);
static void limparEntrada(void) ;
static void liberarApresentadores(Apresentadores **inicio) ;

#endif