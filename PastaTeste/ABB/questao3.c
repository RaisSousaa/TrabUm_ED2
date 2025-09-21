/* questao_3.c — Driver de inserção (streams) e busca (todos os programas de uma categoria)
 * Medições em ms com clock() / CLOCKS_PER_SEC + validação com time().
 *
 * (a) Tempo de INSERÇÃO de streams (apenas inserções reais; sem pré-busca)
 * (b) Tempo de “mostrar todos os programas” de UMA categoria de UMA stream (item vii),
 *     repetido REPS vezes para alongar a medição.
 *
 * Observações:
 * - NÃO há I/O entre t0 e t1 nas medições.
 * - O arquivo 'dados_streams.txt' deve seguir o layout:
 *   Stream N: Nome | Site: X | QtdeCategorias: Z
 *     Categoria: Nome | Tipo: T | QtdeProgramas: M
 *       Programa: Nome | Per: P | Dur: x.xh | Ini: y.yh | Grv: G | Apres: Z
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>   /* strncasecmp */
#include <time.h>      /* clock(), CLOCKS_PER_SEC, time() */

#include "stream.h"
#include "categorias.h"
#include "programas.h"

/* =======================
 * CONFIG
 * ======================= */
#ifndef NOME_IMPL
#define NOME_IMPL "ABB"   /* Defina para "ABB" ou "AVL" na compilação */
#endif

#ifndef CAMINHO_ARQ
#define CAMINHO_ARQ "/home/sthefany/Documentos/5Periodo/EDII/TrabUm_ED2/ABB/TrabUm_ED2/PastaTeste/AVL/dados_streams.txt"
#endif

static const int   MOSTRAR_LOG_PARSER = 0;  /* 1 = log detalhado do parser */
static const int   MOSTRAR_RESUMO     = 0;  /* 1 = imprime in-ordem das streams ao final */

#ifndef REPS
#define REPS 5000   /* ajuste: 1000, 5000, 10000… conforme sua máquina */
#endif

/* =======================
 * TIPOS AUXILIARES (parsing)
 * ======================= */
typedef struct {
    char nome[64];
    char site[64];
    int  qtdCategorias;
} LinhaStream;

typedef struct {
    char nome[64];
    char tipoTxt[32];
    int  qtdProgramas;
} LinhaCategoria;

/* =======================
 * UTILS
 * ======================= */
static inline double clocks_to_ms(clock_t dt) {
    return 1000.0 * (double)dt / (double)CLOCKS_PER_SEC;
}

static void rstrip(char *s) {
    if (!s) return;
    size_t n = strlen(s);
    while (n && (s[n-1] == '\n' || s[n-1] == '\r')) s[--n] = '\0';
}

static int mapearTipoCategoria(const char *tipoTxt) {
    if (!tipoTxt) return Cultura;
    if (strncasecmp(tipoTxt, "Esporte", 7) == 0)           return Esporte;
    if (strncasecmp(tipoTxt, "Noticia", 7) == 0)           return Noticia;
    if (strncasecmp(tipoTxt, "Entretenimento", 14) == 0)   return Entreterimento;
    if (strncasecmp(tipoTxt, "Entreterimento", 14) == 0)   return Entreterimento;
    if (strncasecmp(tipoTxt, "Cultura", 7) == 0)           return Cultura;
    return Cultura;
}

/* =======================
 * PARSER
 * ======================= */
static int parseLinhaStream(const char *linha, LinhaStream *out) {
    if (!linha || !out) return 0;
    int idx = 0; char nomeTemp[128] = {0}; char siteTemp[128] = {0}; int qtd = 0;
    int got = sscanf(linha, "Stream %d: %127[^|] | Site: %127[^|] | QtdeCategorias: %d",
                     &idx, nomeTemp, siteTemp, &qtd);
    if (got != 4) return 0;
    size_t nn = strlen(nomeTemp);
    while (nn && nomeTemp[nn-1] == ' ') nomeTemp[--nn] = '\0';
    snprintf(out->nome, sizeof(out->nome), "%s", nomeTemp);
    snprintf(out->site, sizeof(out->site), "%s", siteTemp);
    out->qtdCategorias = qtd;
    (void)idx;
    return 1;
}

static int parseLinhaCategoria(const char *linha, LinhaCategoria *out) {
    if (!linha || !out) return 0;
    char nomeTemp[128] = {0}; char tipoTemp[64]  = {0}; int qtd = 0;
    int got = sscanf(linha, " Categoria: %127[^|] | Tipo: %63[^|] | QtdeProgramas: %d",
                     nomeTemp, tipoTemp, &qtd);
    if (got != 3) {
        got = sscanf(linha, "   Categoria: %127[^|] | Tipo: %63[^|] | QtdeProgramas: %d",
                     nomeTemp, tipoTemp, &qtd);
        if (got != 3) return 0;
    }
    size_t nn = strlen(nomeTemp);
    while (nn && nomeTemp[nn-1] == ' ') nomeTemp[--nn] = '\0';
    snprintf(out->nome, sizeof(out->nome), "%s", nomeTemp);
    snprintf(out->tipoTxt, sizeof(out->tipoTxt), "%s", tipoTemp);
    out->qtdProgramas = qtd;
    return 1;
}

static int parseLinhaPrograma(const char *linha, infoProgramas *out) {
    if (!linha || !out) return 0;
    char nomeProg[64]={0}, perTxt[32]={0}, grvTxt[32]={0}, apres[64]={0};
    float dur=0.f, ini=0.f;

    int ok = sscanf(linha,
        " Programa: %63[^|] | Per: %31[^|] | Dur: %f%*c | Ini: %f%*c | Grv: %31[^|] | Apres: %63s",
        nomeProg, perTxt, &dur, &ini, grvTxt, apres);
    if (ok != 6) {
        ok = sscanf(linha,
        "      Programa: %63[^|] | Per: %31[^|] | Dur: %f%*c | Ini: %f%*c | Grv: %31[^|] | Apres: %63s",
        nomeProg, perTxt, &dur, &ini, grvTxt, apres);
        if (ok != 6) return 0;
    }

    memset(out, 0, sizeof(*out));
    snprintf(out->nomePrograma, sizeof(out->nomePrograma), "%s", nomeProg);
    out->duracao = dur;
    out->tempoInicio = ini;
    snprintf(out->nomeApresentador, sizeof(out->nomeApresentador), "%s", apres);

    if      (strncasecmp(perTxt, "Diario",   6) == 0) out->periocidade = Diario;
    else if (strncasecmp(perTxt, "Semanal",  7) == 0) out->periocidade = Semanal;
    else                                              out->periocidade = Mensal;

    if (strncasecmp(grvTxt, "AoVivo", 6) == 0)        out->gravacao = AoVivo;
    else                                              out->gravacao = SobDemanda;

    return 1;
}

/* =======================
 * INSERÇÃO PURA (sem pré-busca)
 * ======================= */
static Stream *inserirStreamPura(Stream **raiz, const LinhaStream *ls, int *inseriu) {
    if (inseriu) *inseriu = 0;

    InfoStream info = (InfoStream){0};
    snprintf(info.nomeStream, sizeof(info.nomeStream), "%s", ls->nome);
    snprintf(info.nomeSite,   sizeof(info.nomeSite),   "%s", ls->site);
    info.categoria = NULL;

    Stream *novo = alocarNoStream(info);
    if (!novo) return NULL;

    int ok = InserirStream(raiz, novo);
    if (ok) {
        if (inseriu) *inseriu = 1;
        return novo;           /* inseriu de verdade */
    } else {
        free(novo);            /* duplicata */
        return NULL;
    }
}

/* Categoria/Programa: usa suas funções existentes */
static Categorias *obterOuInserirCategoria(Stream *st, const LinhaCategoria *lc) {
    Categorias *cat = buscarCategoria(st->info.categoria, (char*)lc->nome);
    if (cat) return cat;

    Categorias *no = alocarMemoriaNo();
    if (!no) return NULL;

    snprintf(no->nomeCategoria, sizeof(no->nomeCategoria), "%s", lc->nome);
    no->tipo = mapearTipoCategoria(lc->tipoTxt);
    no->programas = NULL;

    inserirCategoria(&st->info.categoria, no);
    return no;
}

static Programas *inserirProgramaNaCategoria(Categorias *cat, const infoProgramas *ip) {
    Programas *noProg = alocarProgramas(*ip);
    if (!noProg) return NULL;

    int ok = inserirProgramas(&cat->programas, noProg);
    if (!ok) return NULL;
    return noProg;
}

/* =======================
 * BUSCA (item vii)
 * ======================= */
static size_t contarProgramas(Programas *r) {
    if (!r) return 0;
    return 1 + contarProgramas(r->esq) + contarProgramas(r->dir);
}

static Categorias* categoriaComMaisProgramas(Stream *st) {
    if (!st || !st->info.categoria) return NULL;
    Categorias *ini = st->info.categoria, *p = ini, *best = ini;
    size_t bestCount = contarProgramas(ini->programas);
    p = p->prox;
    while (p && p != ini) {
        size_t c = contarProgramas(p->programas);
        if (c > bestCount) { bestCount = c; best = p; }
        p = p->prox;
    }
    return best;
}

static void medir_busca_todos_programas_de_categoria(Stream *raizStreams,
                                                     const char *nomeStream,
                                                     const char *nomeCategoria /* pode ser NULL */)
{
    Stream *st = buscarStream(raizStreams, nomeStream);
    if (!st) {
        printf("Stream '%s' não encontrada.\n", nomeStream);
        return;
    }
    Categorias *cat = NULL;
    if (nomeCategoria && *nomeCategoria) {
        cat = buscarCategoria(st->info.categoria, (char*)nomeCategoria);
        if (!cat) {
            printf("Categoria '%s' não encontrada na stream '%s'.\n", nomeCategoria, nomeStream);
            return;
        }
    } else {
        cat = categoriaComMaisProgramas(st);
        if (!cat) {
            printf("Stream sem categorias.\n");
            return;
        }
        nomeCategoria = cat->nomeCategoria;
    }

    size_t tam = contarProgramas(cat->programas);

    volatile size_t sink = 0;     /* evita otimização do compilador */

    clock_t c0 = clock();
    time_t  s0 = time(NULL);
    for (int r = 0; r < REPS; r++) {
        sink += contarProgramas(cat->programas); /* simula “mostrar todos” sem I/O */
    }
    time_t  s1 = time(NULL);
    clock_t c1 = clock();

    double total_ms  = clocks_to_ms(c1 - c0);
    double medio_ms  = total_ms / (double)REPS;

    printf("\n== BUSCA (todos os programas da categoria) ==\n");
    printf("Stream: '%s' | Categoria: '%s'\n", nomeStream, nomeCategoria);
    printf("Programas (1x): %zu | REPS: %d | acum: %zu\n", tam, REPS, sink);
    printf("Tempo total: %.3f ms (clock) | médio: %.6f ms/rep\n", total_ms, medio_ms);
    printf("Validação:  %ld s (time)\n", (long)(s1 - s0));

    printf("\n== RESUMO BUSCA (para relatório) ==\n");
    printf("Stream='%s' Categoria='%s' Programas=%zu REPS=%d | Total(ms)=%.3f | Médio(ms)=%.6f | Time(s)=%ld\n",
           nomeStream, nomeCategoria, tam, REPS, total_ms, medio_ms, (long)(s1 - s0));
}

/* =======================
 * LEITURA + INSERÇÃO (a) — mede apenas INSERÇÕES REAIS de streams
 * ======================= */
static void carregarDadosEInserir(const char *caminho,
                                  Stream **raizStreams,
                                  char *primeiraStream, size_t lenPrimeira,
                                  char *primeiraCategoria, size_t lenPrimeiraCat)
{
    FILE *fp = fopen(caminho, "r");
    if (!fp) {
        fprintf(stderr, "Erro abrindo arquivo: %s\n", caminho);
        exit(EXIT_FAILURE);
    }

    char linha[512];
    LinhaStream    ls = (LinhaStream){0};
    LinhaCategoria lc = (LinhaCategoria){0};

    int lendoStream = 0, lendoCategoria = 0;
    int jaCapturouPrimeiraStream = 0, jaCapturouPrimeiraCat = 0;

    Stream     *stAtual  = NULL;
    Categorias *catAtual = NULL;

    clock_t acc_streams_clk = 0;
    time_t  acc_streams_s   = 0;
    size_t  n_streams       = 0;

    while (fgets(linha, sizeof(linha), fp)) {
        rstrip(linha);
        if (!linha[0]) continue;

        /* STREAM */
        LinhaStream tmpS;
        if (parseLinhaStream(linha, &tmpS)) {
            if (MOSTRAR_LOG_PARSER) {
                printf("[PARSE] Stream: %s | Site: %s | QtdeCategorias: %d\n",
                       tmpS.nome, tmpS.site, tmpS.qtdCategorias);
            }
            ls = tmpS;

            int inseriu = 0;
            clock_t t0c = clock();
            time_t  t0s = time(NULL);

            stAtual = inserirStreamPura(raizStreams, &ls, &inseriu);

            time_t  t1s = time(NULL);
            clock_t t1c = clock();

            if (stAtual && inseriu) {
                acc_streams_clk += (t1c - t0c);
                acc_streams_s   += (t1s - t0s);
                n_streams++;
            }

            if (!jaCapturouPrimeiraStream) {
                snprintf(primeiraStream, lenPrimeira, "%s", ls.nome);
                jaCapturouPrimeiraStream = 1;
            }

            lendoStream = 1;
            lendoCategoria = 0;
            catAtual = NULL;
            continue;
        }

        /* CATEGORIA */
        if (lendoStream) {
            LinhaCategoria tmpC;
            if (parseLinhaCategoria(linha, &tmpC)) {
                if (MOSTRAR_LOG_PARSER) {
                    printf("  [PARSE] Categoria: %s | Tipo: %s | QtdeProgramas: %d\n",
                           tmpC.nome, tmpC.tipoTxt, tmpC.qtdProgramas);
                }
                lc = tmpC;
                catAtual = obterOuInserirCategoria(stAtual, &lc);

                if (jaCapturouPrimeiraStream && !jaCapturouPrimeiraCat && stAtual &&
                    strncmp(stAtual->info.nomeStream, primeiraStream, lenPrimeira) == 0) {
                    snprintf(primeiraCategoria, lenPrimeiraCat, "%s", lc.nome);
                    jaCapturouPrimeiraCat = 1;
                }

                lendoCategoria = 1;
                continue;
            }
        }

        /* PROGRAMA */
        if (lendoCategoria && catAtual) {
            infoProgramas ip;
            if (parseLinhaPrograma(linha, &ip)) {
                if (MOSTRAR_LOG_PARSER) {
                    printf("    [PARSE] Programa: %s | Per: %d | Dur: %.1fh | Ini: %.1fh | Grv: %d | Apres: %s\n",
                           ip.nomePrograma, ip.periocidade, ip.duracao, ip.tempoInicio, ip.gravacao, ip.nomeApresentador);
                }
                (void)inserirProgramaNaCategoria(catAtual, &ip);
                continue;
            }
        }
    }

    fclose(fp);

    double total_ms = clocks_to_ms(acc_streams_clk);
    double por_stream_us = (n_streams > 0) ? (1000.0 * total_ms / (double)n_streams) : 0.0;

    printf("\n== INSERÇÃO (apenas STREAMS) ==\n");
    printf("Streams inseridas (reais): %zu\n", n_streams);
    printf("Tempo total: %.3f ms (clock)\n", total_ms);
    printf("Validação:  %ld s (time)\n", (long)acc_streams_s);

    printf("\n== RESUMO INSERÇÃO (para relatório) ==\n");
    printf("Streams=%zu | Total(ms)=%.3f | Time(s)=%ld | Médio=%.3f µs/stream\n",
           n_streams, total_ms, (long)acc_streams_s, por_stream_us);
}

/* =======================
 * MAIN
 * ======================= */
int main(void)
{
    printf("=== IMPLEMENTAÇÃO: %s ===\n", NOME_IMPL);

    Stream *raizStreams = NULL;
    char primeiraStream[64]    = {0};
    char primeiraCategoria[64] = {0};

    carregarDadosEInserir(CAMINHO_ARQ, &raizStreams,
                          primeiraStream, sizeof(primeiraStream),
                          primeiraCategoria, sizeof(primeiraCategoria));

    if (MOSTRAR_RESUMO) {
        printf("\nPrimeira stream identificada: %s\n", primeiraStream[0] ? primeiraStream : "(nenhuma)");
        printf("Resumo (in-ordem) de streams:\n");
        imprimirInOrdem(raizStreams);
    }

    if (primeiraStream[0]) {
        /* passe NULL para pegar automaticamente a categoria “mais pesada” da primeira stream */
        medir_busca_todos_programas_de_categoria(raizStreams,
                                                 primeiraStream,
                                                 NULL /* ou primeiraCategoria */);
    } else {
        printf("\nNão foi possível identificar stream/categoria iniciais para a medição (b).\n");
    }

    return 0;
}
