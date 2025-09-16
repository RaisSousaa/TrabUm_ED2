#ifndef PROGRAMAS_H
#define PROGRAMAS_H

#define TAM_STRING 50

/* forward declarations para evitar include circular */
typedef struct Stream Stream;      
typedef struct Categorias Categorias;
typedef struct Programas Programas;
typedef struct Apresentadores Apresentadores;  
typedef struct Historico Historico;  

typedef enum Periocidade
{
    Diario = 1,
    Semanal = 2,
    Mensal = 3
} Periocidade;

typedef enum Gravacao
{
    AoVivo = 1,
    SobDemanda = 2
} Gravacao;

typedef struct infoProgramas
{
    char nomePrograma[TAM_STRING];
    Periocidade periocidade;
    float duracao;
    float tempoInicio;
    Gravacao gravacao;
    char nomeApresentador[50];
} infoProgramas;

struct Programas
{
    struct Programas *esq, *dir;
    int altura;                 /* AVL */
    infoProgramas infoProgramas;
};

/* === públicas usadas no projeto === */
Programas* alocarProgramas(infoProgramas dados);
infoProgramas preencherDadosPrograma(void);
int inserirProgramas(Programas **raizProgramas, Programas *no);
Programas *buscarProgramas(Programas *raiz, const char *nomeProgramas);
void mostrarProgramas(Programas *raiz);
int removerProgramas(Programas **raizProgramas, const char *nomePrograma);

/* outras que seu projeto referencia (mantidas) */
void menuProgramas(Stream *stream, Categorias *categoriaSelecionada, Apresentadores **listaApresentadores, Stream *raizStream);
void finalizarUltimoHistoricoSeAberto(Historico *hist, int dataTermino);

/* utilitárias de consulta/filtro já existentes */
int programasContemApresentador(Programas *raiz, const char *nomeApresentador);
void filtrarProgramasPorPeriodicidadeEHorario(Programas *raiz, Periocidade periodicidade, float horario);
void filtrarProgramasPorPeriodicidade(Programas *raiz, Periocidade periodicidade);

#endif
