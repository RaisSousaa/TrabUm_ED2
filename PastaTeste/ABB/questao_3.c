/* questao_3.c  — driver de inserção e busca com medição de tempo via clock()
 *
 * Passos implementados:
 * 1) Lê o arquivo de dados sintéticos (Stream -> Categoria -> Programa)
 * 2) Começa a contagem de tempo (inserção)
 * 3) Inserção hierárquica usando as funções já existentes dos módulos
 * 4) Contagem do tempo final
 * 5) Mostra duração da inserção
 * 6) Salva tempo inicial (buscas)
 * 7) Busca: primeira stream, todas as categorias, e cada programa
 * 8) Salva tempo final
 * 9) Mostra duração das buscas
 *
 * Módulos usados:
 *   - streamAVL.c/.h: alocarNoStream, InserirStream, buscarStream, imprimirInOrdem  :contentReference[oaicite:4]{index=4}
 *   - categoriasAVL.c/.h: alocarMemoriaNo, inserirCategoria, buscarCategoria        :contentReference[oaicite:5]{index=5}
 *   - programasAVL.c/.h: alocarProgramas, inserirProgramas, buscarProgramas         :contentReference[oaicite:6]{index=6}
 *
 * O arquivo 'dados_streams.txt' segue o layout fornecido.                              :contentReference[oaicite:7]{index=7}
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "stream.h"
#include "categorias.h"
#include "programas.h"

/* =======================
 * PARÂMETROS DE FÁCIL ACESSO
 * ======================= */
static const char *CAMINHO_ARQ = "dados_streams.txt";
static const int   MOSTRAR_LOG_PARSER = 0;
static const int   MOSTRAR_RESUMO     = 1;

/* =======================
 * ESTRUTURAS AUXILIARES (parsing)
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

/* Mapeia texto do tipo (do arquivo) para o enum Tipo dos módulos */
/* Mapeia texto do tipo (do arquivo) para o enum Tipo dos módulos */
static int mapearTipoCategoria(const char *tipoTxt)
{
    if (!tipoTxt) return Cultura;

    if (strncasecmp(tipoTxt, "Esporte", 7) == 0)           return Esporte;
    if (strncasecmp(tipoTxt, "Noticia", 7) == 0)           return Noticia;

    /* aceita as duas grafias no arquivo, mas usa o enum existente: Entreterimento */
    if (strncasecmp(tipoTxt, "Entretenimento", 14) == 0)   return Entreterimento;
    if (strncasecmp(tipoTxt, "Entreterimento", 14) == 0)   return Entreterimento;

    if (strncasecmp(tipoTxt, "Cultura", 7) == 0)           return Cultura;

    return Cultura;
}


/* =======================
 * PARSER DO ARQUIVO
 * ======================= */

/* remove \n/\r do fim */
static void rstrip(char *s)
{
    if (!s) return;
    size_t n = strlen(s);
    while (n && (s[n-1] == '\n' || s[n-1] == '\r')) s[--n] = '\0';
}

/* Lê uma linha “Stream N: Nome | Site: X | QtdeCategorias: Z” */
static int parseLinhaStream(const char *linha, LinhaStream *out)
{
    if (!linha || !out) return 0;

    int idx = 0;
    char nomeTemp[128] = {0};
    char siteTemp[128] = {0};
    int qtd = 0;

    int got = sscanf(linha, "Stream %d: %127[^|] | Site: %127[^|] | QtdeCategorias: %d",
                     &idx, nomeTemp, siteTemp, &qtd);
    if (got != 4) return 0;

    /* tira espaços à direita do nome */
    size_t nn = strlen(nomeTemp);
    while (nn && nomeTemp[nn-1] == ' ') nomeTemp[--nn] = '\0';

    snprintf(out->nome, sizeof(out->nome), "%s", nomeTemp);
    snprintf(out->site, sizeof(out->site), "%s", siteTemp);
    out->qtdCategorias = qtd;
    (void)idx; /* não precisamos do índice */
    return 1;
}

/* Lê “Categoria: Nome | Tipo: T | QtdeProgramas: N” (com ou sem 3 espaços) */
static int parseLinhaCategoria(const char *linha, LinhaCategoria *out)
{
    if (!linha || !out) return 0;

    char nomeTemp[128] = {0};
    char tipoTemp[64]  = {0};
    int qtd = 0;

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

/* Lê “Programa: Nome | Per: P | Dur: x.xh | Ini: y.yh | Grv: G | Apres: Z” */
static int parseLinhaPrograma(const char *linha, infoProgramas *out)
{
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

    if (strncasecmp(perTxt, "Diario", 6) == 0)       out->periocidade = Diario;
    else if (strncasecmp(perTxt, "Semanal", 7) == 0) out->periocidade = Semanal;
    else                                             out->periocidade = Mensal;

    if (strncasecmp(grvTxt, "AoVivo", 6) == 0)       out->gravacao = AoVivo;
    else                                             out->gravacao = SobDemanda;

    return 1;
}

/* =======================
 * INSERÇÃO (usa funções dos módulos)
 * ======================= */

/* Stream: busca ou insere na AVL */
static Stream *obterOuInserirStream(Stream **raiz, const LinhaStream *ls)
{
    Stream *achou = buscarStream(*raiz, ls->nome);                 /* :contentReference[oaicite:8]{index=8} */
    if (achou) return achou;

    InfoStream info = {0};
    snprintf(info.nomeStream, sizeof(info.nomeStream), "%s", ls->nome);
    snprintf(info.nomeSite,   sizeof(info.nomeSite),   "%s", ls->site);
    info.categoria = NULL;

    Stream *novo = alocarNoStream(info);                           /* :contentReference[oaicite:9]{index=9} */
    InserirStream(raiz, novo);                                     /* :contentReference[oaicite:10]{index=10} */
    return novo;
}

/* Categoria: busca ou insere na lista circular da stream */
static Categorias *obterOuInserirCategoria(Stream *st, const LinhaCategoria *lc)
{
    Categorias *cat = buscarCategoria(st->info.categoria, (char*)lc->nome); /* :contentReference[oaicite:11]{index=11} */
    if (cat) return cat;

    Categorias *no = alocarMemoriaNo();                            /* :contentReference[oaicite:12]{index=12} */
    snprintf(no->nomeCategoria, sizeof(no->nomeCategoria), "%s", lc->nome);
    no->tipo = mapearTipoCategoria(lc->tipoTxt);
    no->programas = NULL;

    inserirCategoria(&st->info.categoria, no);                     /* :contentReference[oaicite:13]{index=13} */
    return no;
}

/* Programa: insere na AVL de programas da categoria */
static Programas *inserirProgramaNaCategoria(Categorias *cat, const infoProgramas *ip)
{
    Programas *noProg = alocarProgramas(*ip);                      /* :contentReference[oaicite:14]{index=14} */
    inserirProgramas(&cat->programas, noProg);                     /* :contentReference[oaicite:15]{index=15} */
    return noProg;
}

/* =======================
 * LEITURA + INSERÇÃO (passos 1–5)
 * ======================= */

static void carregarDadosEInserir(const char *caminho, Stream **raizStreams,
                                  char *primeiraStream, size_t lenPrimeira)
{
    FILE *fp = fopen(caminho, "r");
    if (!fp) {
        fprintf(stderr, "Erro abrindo arquivo: %s\n", caminho);
        exit(EXIT_FAILURE);
    }

    clock_t t0 = clock(); /* (2) início do tempo de INSERÇÃO */

    char linha[512];
    LinhaStream    ls = {0};
    LinhaCategoria lc = {0};
    int lendoStream = 0, lendoCategoria = 0;
    int jaCapturouPrimeiraStream = 0;

    Stream     *stAtual  = NULL;
    Categorias *catAtual = NULL;

    while (fgets(linha, sizeof(linha), fp)) {
        rstrip(linha);
        if (!linha[0]) continue;

        /* STREAM */
        LinhaStream tmpS;
        if (parseLinhaStream(linha, &tmpS)) {
            if (MOSTRAR_LOG_PARSER) {
                printf("[PARSE] Stream: %s | Site: %s | QtdeCategorias=%d\n",
                       tmpS.nome, tmpS.site, tmpS.qtdCategorias);
            }
            ls = tmpS;
            stAtual = obterOuInserirStream(raizStreams, &ls);

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
                    printf("  [PARSE] Categoria: %s | Tipo: %s | QtdeProgramas=%d\n",
                           tmpC.nome, tmpC.tipoTxt, tmpC.qtdProgramas);
                }
                lc = tmpC;
                catAtual = obterOuInserirCategoria(stAtual, &lc);
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
                inserirProgramaNaCategoria(catAtual, &ip);
                continue;
            }
        }
    }

    fclose(fp);

    clock_t t1 = clock(); /* (4) fim do tempo de INSERÇÃO */

    /* (5) duração */
    double duracao = (double)(t1 - t0) / CLOCKS_PER_SEC;
    printf("\n== INSERÇÃO CONCLUÍDA ==\n");
    printf("Tempo de inserção: %.6f s\n", duracao);
}

/* =======================
 * BUSCAS (passos 6–9)
 * ======================= */

/* percorre em-ordem a AVL de programas e, para cada nome, re-busca pelo nome */
static void percorrerERebuscar(Programas *raiz, Programas *raizInteira)
{
    if (!raiz) return;
    percorrerERebuscar(raiz->esq, raizInteira);
    (void)buscarProgramas(raizInteira, raiz->infoProgramas.nomePrograma); /* :contentReference[oaicite:16]{index=16} */
    percorrerERebuscar(raiz->dir, raizInteira);
}

static void executarBuscas(Stream *raizStreams, const char *primeiraStream)
{
    clock_t t0 = clock(); /* (6) tempo inicial BUSCAS */

    /* (7) acessa e busca a primeira stream */
    Stream *st = buscarStream(raizStreams, primeiraStream);        /* :contentReference[oaicite:17]{index=17} */
    if (!st) {
        fprintf(stderr, "Primeira stream “%s” não encontrada para buscas.\n", primeiraStream);
        return;
    }

    /* (7.2) percorre categorias e busca cada uma; depois percorre e busca programas */
    Categorias *ini = st->info.categoria;
    if (ini) {
        Categorias *cat = ini;
        do {
            Categorias *catBuscada = buscarCategoria(st->info.categoria, cat->nomeCategoria); /* :contentReference[oaicite:18]{index=18} */
            if (catBuscada && catBuscada->programas) {
                percorrerERebuscar(catBuscada->programas, catBuscada->programas);
            }
            cat = cat->prox;
        } while (cat && cat != ini);
    }

    clock_t t1 = clock(); /* (8) tempo final BUSCAS */

    double duracao = (double)(t1 - t0) / CLOCKS_PER_SEC;  /* (9) duração */
    printf("\n== BUSCAS CONCLUÍDAS ==\n");
    printf("Tempo total de buscas: %.6f s\n", duracao);
}

/* =======================
 * MAIN
 * ======================= */
int main(void)
{
    Stream *raizStreams = NULL;
    char primeiraStream[64] = {0};

    /* (1–5) leitura e inserção */
    carregarDadosEInserir(CAMINHO_ARQ, &raizStreams, primeiraStream, sizeof(primeiraStream));

    if (MOSTRAR_RESUMO) {
        printf("\nPrimeira stream identificada: %s\n", primeiraStream[0] ? primeiraStream : "(nenhuma)");
        printf("Resumo (in-ordem):\n");
        imprimirInOrdem(raizStreams);                                    /* :contentReference[oaicite:19]{index=19} */
    }

    /* (6–9) buscas */
    if (primeiraStream[0]) {
        executarBuscas(raizStreams, primeiraStream);
    } else {
        fprintf(stderr, "Não foi possível identificar a primeira stream a partir do arquivo.\n");
    }

    return 0;
}
