/* gerador_dados.c: gera um arquivo texto com dados aleatórios
   para as estruturas Stream -> Categorias -> Programas, com comentários em todas as linhas. */

#include <stdio.h>      /* printf, fprintf, FILE, fopen, fclose */  // include da stdio para IO
#include <stdlib.h>     /* rand, srand, malloc, free */              // include da stdlib para aleatoriedade e memória
#include <string.h>     /* strcpy, strncpy, strlen */                // include da string para manipulação de strings
#include <time.h>       /* time */                                   // include para srand com time(NULL)

/* ======= Definições de tipos/estruturas conforme solicitado ======= */  // seção de tipos

#define TAM_STRING 50                                                  // tamanho padrão para strings

typedef enum Tipo {                                                    // enum de tipos de categoria
    Esporte = 1,                                                       // 1 = Esporte
    Noticia = 2,                                                       // 2 = Noticia
    Entreterimento = 3,                                                // 3 = Entreterimento
    Cultura = 4                                                        // 4 = Cultura
} Tipo;                                                                // nome do enum

typedef struct InfoStream {                                            // dados descritivos de uma stream
    char nomeStream[50];                                               // nome da stream
    char nomeSite[50];                                                 // nome do site
    struct Categorias *categoria;                                      // lista de categorias (lista simples circular ou NULL)
} InfoStream;                                                          // typedef

typedef struct Stream {                                                // nó da árvore de streams (AVL), não vamos montar a árvore aqui
    InfoStream info;                                                   // informações da stream
    struct Stream *esq, *dir;                                          // ponteiros da árvore (não usados aqui)
    int altura;                                                        // campo AVL (não usado aqui)
} Stream;                                                              // typedef

typedef enum Periocidade {                                             // enum de periodicidade
    Diario = 1,                                                        // 1 = Diário
    Semanal = 2,                                                       // 2 = Semanal
    Mensal = 3                                                         // 3 = Mensal
} Periocidade;                                                         // typedef

typedef enum Gravacao {                                                // enum de tipo de gravação
    AoVivo = 1,                                                        // 1 = Ao Vivo
    SobDemanda = 2                                                     // 2 = Sob Demanda
} Gravacao;                                                            // typedef

typedef struct infoProgramas {                                         // dados do programa
    char nomePrograma[TAM_STRING];                                     // nome do programa
    Periocidade periocidade;                                           // periodicidade
    float duracao;                                                     // duração em horas
    float tempoInicio;                                                 // horário de início (ex.: 8.5 = 08:30)
    Gravacao gravacao;                                                 // tipo de gravação
    char nomeApresentador[50];                                         // nome do apresentador
} infoProgramas;                                                       // typedef

typedef struct Programas {                                             // nó de programa (AVL), aqui usado como payload
    struct Programas *esq, *dir;                                       // ponteiros (não usados aqui)
    int altura;                                                        // campo AVL (não usado aqui)
    infoProgramas infoProgramas;                                       // dados do programa
} Programas;                                                           // typedef

typedef struct Categorias {                                            // categoria dentro de uma stream
    Tipo tipo;                                                         // tipo da categoria
    char nomeCategoria[50];                                            // nome da categoria
    struct Categorias *prox;                                           // próximo (p/ lista simples; aqui podemos só encadear linearmente)
    Programas *programas;                                              // raiz da ABB/AVL de programas (aqui não vamos montar de fato)
} Categorias;                                                          // typedef

/* ======= Parâmetros de geração ======= */                            // seção com parâmetros ajustáveis
#define NUM_STREAMS 100                                                  // quantas streams aleatórias gerar
#define MIN_CATS 20                                                     // mínimo de categorias por stream
#define MAX_CATS 30                                                     // máximo de categorias por stream
#define MIN_PROGS 25                                                    // mínimo de programas por categoria
#define MAX_PROGS 30                                                    // máximo de programas por categoria
#define ARQ_SAIDA "dados_streams.txt"                                  // nome do arquivo de saída

/* ======= Utilitários de nomes/strings ======= */                     // arrays auxiliares para nomes
static const char *NOMES_STREAM[] = {                                  // nomes base para streams
    "Alpha", "Beta", "Gamma", "Delta", "Epsilon", "Kappa", "Sigma", "Zeta", "Orion", "Lyra"
};                                                                      // fim do array
static const char *NOMES_SITE[] = {                                    // nomes base para sites
    "alpha.com", "beta.tv", "gamma.live", "delta.fm", "epsilon.net", "kappa.io", "sigma.media", "zeta.news", "orion.app", "lyra.plus"
};                                                                      // fim do array
static const char *NOMES_CAT[] = {                                     // nomes base para categorias
    "Esportes Top", "Noticias 24h", "Entretenimento+", "Cultura Viva", "Arena Esportiva", "Jornal Agora", "ShowTime", "Arte&Historia"
};                                                                      // fim do array
static const char *NOMES_PROG[] = {                                    // nomes base para programas
    "ManhaTotal", "NoiteNews", "Arena360", "PopShow", "CulturaMix", "Esporte10", "CityLive", "MundoHoje", "Talk+, " "ShowDas5"
};                                                                      // fim do array
static const char *NOMES_APRES[] = {                                   // nomes base para apresentadores
    "Ana", "Bruno", "Carla", "Diego", "Eva", "Felipe", "Gabi", "Heitor", "Iris", "Joao", "Katia", "Leo", "Mila", "Nando", "Olivia"
};                                                                      // fim do array

/* ======= Helpers aleatórios ======= */                               // funções auxiliares

int rand_int(int min, int max)                                         // retorna inteiro aleatório no intervalo [min, max]
{                                                                       // abre função
    int val = min + rand() % (max - min + 1);                          // cálculo do valor
    return val;                                                         // retorna
}                                                                       // fecha função

float rand_float_range(float min, float max, float step)               // retorna float aleatório entre min e max com passo (ex.: 0.5)
{                                                                       // abre função
    int nsteps = (int)((max - min) / step) + 1;                        // número de degraus possíveis
    int k = rand_int(0, nsteps - 1);                                   // degrau aleatório
    float val = min + k * step;                                        // valor calculado
    return val;                                                         // retorna
}                                                                       // fecha função

const char* pick(const char **arr, int n)                              // escolhe um item aleatório de um array de const char*
{                                                                       // abre função
    const char *s = arr[rand_int(0, n - 1)];                           // pega índice aleatório
    return s;                                                           // retorna ponteiro para string
}                                                                       // fecha função

const char* tipo_to_str(Tipo t)                                        // converte enum Tipo para string
{                                                                       // abre função
    const char *s = "Desconhecido";                                    // default
    if      (t == Esporte)        s = "Esporte";                       // caso Esporte
    else if (t == Noticia)        s = "Noticia";                       // caso Noticia
    else if (t == Entreterimento) s = "Entreterimento";                // caso Entreterimento
    else if (t == Cultura)        s = "Cultura";                       // caso Cultura
    return s;                                                           // retorna
}                                                                       // fecha função

const char* per_to_str(Periocidade p)                                  // converte enum Periocidade para string
{                                                                       // abre função
    const char *s = "??";                                              // default
    switch (p) {                                                       // switch em p
        case Diario:   s = "Diario";   break;                          // caso Diario
        case Semanal:  s = "Semanal";  break;                          // caso Semanal
        case Mensal:   s = "Mensal";   break;                          // caso Mensal
        default:       s = "??";       break;                          // default
    }                                                                   // fim switch
    return s;                                                           // retorna
}                                                                       // fecha função

const char* grv_to_str(Gravacao g)                                     // converte enum Gravacao para string
{                                                                       // abre função
    const char *s = "??";                                              // default
    switch (g) {                                                       // switch em g
        case AoVivo:      s = "AoVivo";      break;                    // caso AoVivo
        case SobDemanda:  s = "SobDemanda";  break;                    // caso SobDemanda
        default:          s = "??";          break;                    // default
    }                                                                   // fim switch
    return s;                                                           // retorna
}                                                                       // fecha função

/* ======= Geração e escrita no arquivo ======= */                     // funções de geração

void gerar_programa(FILE *fp)                                          // gera um programa e escreve no arquivo
{                                                                       // abre função
    infoProgramas ip;                                                  // instancia dados do programa
    strncpy(ip.nomePrograma, pick(NOMES_PROG,                           // copia nome aleatório
            (int)(sizeof(NOMES_PROG)/sizeof(NOMES_PROG[0]))), TAM_STRING-1); // limite de cópia
    ip.nomePrograma[TAM_STRING-1] = '\0';                              // garante terminação

    ip.periocidade = (Periocidade)rand_int(Diario, Mensal);            // sorteia periodicidade
    ip.duracao = rand_float_range(0.5f, 4.0f, 0.5f);                   // sorteia duração 0.5..4.0, passo 0.5
    ip.tempoInicio = rand_float_range(5.0f, 23.0f, 0.5f);              // sorteia início 5.0..23.0, passo 0.5
    ip.gravacao = (Gravacao)rand_int(AoVivo, SobDemanda);              // sorteia gravação
    strncpy(ip.nomeApresentador, pick(NOMES_APRES,                      // sorteia apresentador
            (int)(sizeof(NOMES_APRES)/sizeof(NOMES_APRES[0]))), 49);   // limite de cópia
    ip.nomeApresentador[49] = '\0';                                    // garante terminação

    fprintf(fp, "      Programa: %s | Per: %s | Dur: %.1fh | Ini: %.1fh | Grv: %s | Apres: %s\n",
            ip.nomePrograma, per_to_str(ip.periocidade),               // escreve campos formatados
            ip.duracao, ip.tempoInicio, grv_to_str(ip.gravacao),       // continua a linha
            ip.nomeApresentador);                                      // finaliza com apresentador
}                                                                       // fecha função

void gerar_categoria(FILE *fp)                                         // gera uma categoria com N programas
{                                                                       // abre função
    Categorias cat;                                                    // instancia categoria (stack)
    cat.tipo = (Tipo)rand_int(Esporte, Cultura);                       // sorteia tipo 1..4
    strncpy(cat.nomeCategoria, pick(NOMES_CAT,                          // define nome aleatório
            (int)(sizeof(NOMES_CAT)/sizeof(NOMES_CAT[0]))), 49);       // limita a cópia
    cat.nomeCategoria[49] = '\0';                                      // garante terminação
    cat.prox = NULL;                                                   // prox não usado na geração
    cat.programas = NULL;                                              // programas não usados como árvore aqui

    int qtdProg = rand_int(MIN_PROGS, MAX_PROGS);                      // sorteia nº de programas para esta categoria

    fprintf(fp, "   Categoria: %s | Tipo: %s | QtdeProgramas: %d\n",
            cat.nomeCategoria, tipo_to_str(cat.tipo),                  // escreve header da categoria
            qtdProg);                                                  // escreve quantidade

    for (int i = 0; i < qtdProg; i++) {                                // laço de programas
        gerar_programa(fp);                                            // gera e imprime um programa
    }                                                                   // fim for
}                                                                       // fecha função

void gerar_stream(FILE *fp, int idx)                                   // gera uma stream com M categorias
{                                                                       // abre função
    Stream st;                                                         // instancia stream (stack)
    st.esq = st.dir = NULL;                                            // ponteiros não usados aqui
    st.altura = 1;                                                     // altura default
    st.info.categoria = NULL;                                          // sem lista encadeada real aqui

    strncpy(st.info.nomeStream, pick(NOMES_STREAM,                      // escolhe nome de stream
            (int)(sizeof(NOMES_STREAM)/sizeof(NOMES_STREAM[0]))), 49); // limita cópia
    st.info.nomeStream[49] = '\0';                                     // garante terminação

    strncpy(st.info.nomeSite, pick(NOMES_SITE,                          // escolhe nome de site
            (int)(sizeof(NOMES_SITE)/sizeof(NOMES_SITE[0]))), 49);     // limita cópia
    st.info.nomeSite[49] = '\0';                                       // garante terminação

    int qtdCat = rand_int(MIN_CATS, MAX_CATS);                         // sorteia nº de categorias desta stream

    fprintf(fp, "Stream %d: %s | Site: %s | QtdeCategorias: %d\n",
            idx + 1, st.info.nomeStream, st.info.nomeSite,             // escreve header da stream
            qtdCat);                                                   // escreve quantidade

    for (int c = 0; c < qtdCat; c++) {                                 // laço de categorias
        gerar_categoria(fp);                                           // gera/printa uma categoria
    }                                                                   // fim for
}                                                                       // fecha função

int main(void)                                                          // main do gerador
{                                                                       // abre main
    srand((unsigned)time(NULL));                                       // semente do gerador de aleatórios
    FILE *fp = fopen(ARQ_SAIDA, "w");                                  // abre arquivo de saída em modo escrita

    if (fp == NULL) {                                                  // checa erro ao abrir
        printf("Erro ao criar arquivo '%s'.\n", ARQ_SAIDA);            // informa erro
        return 1;                                                      // retorna erro
    }                                                                   // fim if

    fprintf(fp, "=== DADOS GERADOS (Stream -> Categoria -> Programa) ===\n"); // cabeçalho do arquivo

    for (int i = 0; i < NUM_STREAMS; i++) {                            // laço de streams
        gerar_stream(fp, i);                                           // gera/printa uma stream
        fprintf(fp, "\n");                                             // linha em branco entre streams
    }                                                                   // fim for

    fclose(fp);                                                        // fecha arquivo
    printf("Arquivo '%s' gerado com sucesso.\n", ARQ_SAIDA);           // mensagem de sucesso
    return 0;                                                          // finaliza OK
}                                                                       // fecha main
