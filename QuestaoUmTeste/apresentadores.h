#ifndef APRESENTADORES_H
#define APRESENTADORES_H

#define TAM_STRING 50
#include "tipos.h"

typedef struct Stream Stream;
typedef struct Programas Programas;
typedef struct Historico Historico;


typedef struct InfoApresentador {
    Tipo ondeTrabalha;         // usa o mesmo enum
    char nome[TAM_STRING];
    Stream *streamAtual;
    Historico *historico;
    Programas *programas;
} InfoApresentador;


typedef struct Apresentadores
{
    InfoApresentador info;
    struct Apresentadores *prox, *ant; // lista duplamente encadeada
} Apresentadores;


// ===== Tipos =====
typedef struct InfoHistorico
{
    char nomeStream[50];
    int dataInicio, dataTermino; // AAAAMMDD; dataTermino == 0 "Em curso"
} InfoHistorico;

typedef struct Historico
{
    InfoHistorico info;
    struct Historico *prox;
} Historico;

// ===== Funções de apresentadores ======
Apresentadores* alocarApresentador(void);
InfoApresentador preencherDadosApresentador(void);
int inserirApresentador(Apresentadores **inicio, Apresentadores *novo);
Apresentadores* buscarApresentadores(Apresentadores *inicio, const char *nome_busca, int *encontrou);
void imprimirApresentadores(Apresentadores *inicio);
void liberarApresentadores(Apresentadores **inicio);

// ===== Funções de histórico ======
Historico* alocarHistorico(const InfoHistorico *dado);
InfoHistorico preencherDadosHistorico(void);     // <<< ADICIONADO AQUI
int inserirHistorico(Historico **inicio, const InfoHistorico *dado);
Historico* buscar(Historico *inicio, const char *nome);
void imprimirHistorico(const Historico *inicio);
void liberarHistorico(Historico **inicio);

#endif
