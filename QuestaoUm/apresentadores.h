#ifndef APRESENTADORES_H
#define APRESENTADORES_H

#define TAM_STRING 50

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
Apresentadores* buscarApresentadores(Apresentadores *inicio, const char *nome_busca, int *flag);
void imprimirApresentadores(Apresentadores *inicio);
static void limparEntrada(void) ;
static void liberarApresentadores(Apresentadores **inicio) ;

// ===== Funções da lista de histórico  ===== 
Historico* alocarHistorico(const InfoHistorico *dado);
int inserirHistoricoOrdenado(Historico **inicio, const InfoHistorico *dado); 
void imprimirHistorico(const Historico *inicio);
void liberarHistorico(Historico **inicio);

//funções do main
static void limparEntrada(void) ;
static int lerLinha(char *buf, size_t tam);




#endif