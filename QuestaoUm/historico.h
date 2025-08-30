#ifndef HISTORICO_H
#define HISTORICO_H

typedef struct InfoHistorico
{
    char nomeStream[50];
    int dataInicio, dataTermino;
}InfoHistorico;


typedef struct Historico
{
    InfoHistorico info;
    struct Historico *prox;
}Historico;

Historico* alocarHistorico(const InfoHistorico *dado);
int inserirHistorico(Historico **inicio, const InfoHistorico *dado);
Historico* buscar(Historico *inicio, const char *nome);
void imprimirHistorico(const Historico *inicio);
void liberarHistorico(Historico **inicio);

#endif