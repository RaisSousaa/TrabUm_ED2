#ifndef APRESENTADORES_H
#define APRESENTADORES_H

#define TAM_STRING 50

#include "historico.h"
#include "categorias.h"

//lista historico apresentador


typedef struct InfoApresentador
{
    Tipo ondeTrabalha;
    char nome[TAM_STRING];
    char streamAtual[TAM_STRING];
    Historico *historico;

}InfoApresentador;


typedef struct Apresentadores
{
    InfoApresentador info;
    struct Apresentadores *prox, *ant;

}Apresentadores;


// ===== Funções de apresentadores ======
Apresentadores* alocarApresentador(void) ;
InfoApresentador preencherDadosApresentador(void);
int inserirApresentador(Apresentadores **inicio, Apresentadores *novo);
Apresentadores* buscarApresentadores(Apresentadores *inicio, const char *nome_busca, int *encontrou);
void imprimirApresentadores(Apresentadores *inicio);
void liberarApresentadores(Apresentadores **inicio);


// ===== Funções da lista de histórico  ===== 
Historico* alocarHistorico(const InfoHistorico *dado);
int inserirHistorico(Historico **inicio, const InfoHistorico *dado);
void imprimirHistorico(const Historico *inicio);
void liberarHistorico(Historico **inicio);



//funções do main
static void limparEntrada(void) ;
static int lerLinha(char *buf, size_t tam);



#endif