#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "streamAVL.h"
#include "programasAVL.h"



static int alturaStream(Stream *no)
{
    int alt = 0;
    if (no != NULL) {
        alt = no->altura;
    }
    return alt;
}

static int maiorAlt(int altEsq, int altDir)
{
    int maior = altEsq;
    if (altDir > altEsq) {
        maior = altDir;
    }
    return maior;
}

static void attAlturaStream(Stream *no)
{
    if (no != NULL) {
        int altEsq = alturaStream(no->esq);
        int altDir = alturaStream(no->dir);
        no->altura = 1 + maiorAlt(altEsq, altDir);
    }
}

static int fbStream(Stream *no)
{
    int fb = 0;
    if (no != NULL) {
        fb = alturaStream(no->esq) - alturaStream(no->dir);
    }
    return fb;
}

static Stream* rotDirStream(Stream *raiz)
{
    Stream *novaRaiz = raiz;
    if (raiz != NULL && raiz->esq != NULL) {
        Stream *filhoEsq = raiz->esq;
        Stream *subDir   = filhoEsq->dir;

        filhoEsq->dir = raiz;
        raiz->esq     = subDir;

        attAlturaStream(raiz);
        attAlturaStream(filhoEsq);

        novaRaiz = filhoEsq;
    }
    return novaRaiz;
}

static Stream* rotEsqStream(Stream *raiz)
{
    Stream *novaRaiz = raiz;
    if (raiz != NULL && raiz->dir != NULL) {
        Stream *filhoDir = raiz->dir;
        Stream *subEsq   = filhoDir->esq;

        filhoDir->esq = raiz;
        raiz->dir     = subEsq;

        attAlturaStream(raiz);
        attAlturaStream(filhoDir);

        novaRaiz = filhoDir;
    }
    return novaRaiz;
}

static Stream* balancearStream(Stream *raiz)
{
    Stream *novaRaiz = raiz;
    if (raiz != NULL) {
        int fb = fbStream(raiz);

        if (fb > 1 && fbStream(raiz->esq) >= 0) {
            novaRaiz = rotDirStream(raiz);                /* Esq-Esq */
        } else if (fb > 1 && fbStream(raiz->esq) < 0) {
            raiz->esq = rotEsqStream(raiz->esq);          /* Esq-Dir */
            novaRaiz  = rotDirStream(raiz);
        } else if (fb < -1 && fbStream(raiz->dir) <= 0) {
            novaRaiz = rotEsqStream(raiz);                /* Dir-Dir */
        } else if (fb < -1 && fbStream(raiz->dir) > 0) {
            raiz->dir = rotDirStream(raiz->dir);          /* Dir-Esq */
            novaRaiz  = rotEsqStream(raiz);
        }
    }
    return novaRaiz;
}

/* ===== Públicas ===== */

Stream *alocarNoStream(InfoStream stream)
{
    Stream *no = (Stream*) malloc(sizeof(Stream));
    if (no == NULL) {
        printf("Erro ao alocar memoria\n");
    } else {
        no->dir = NULL;
        no->esq = NULL;
        no->info = stream;
        no->info.categoria = NULL;
        no->altura = 1; /* AVL: nó novo */
    }
    return no;
}

InfoStream preencherDadosStream(void)
{
    InfoStream d;
    printf("Digite o nome da Stream:\n");
    setbuf(stdin, NULL);
    scanf("%[^\n]", d.nomeStream);
    printf("Digite o nome do site:\n");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", d.nomeSite);
    d.categoria = NULL;
    return d;
}

int InserirStream(Stream **raiz, Stream *no)
{
    int inseriu = 0;

    if (raiz != NULL && no != NULL) {
        if (*raiz == NULL) {
            *raiz = no;
            inseriu = 1;
        } else {
            int cmp = strcmp(no->info.nomeStream, (*raiz)->info.nomeStream);
            if (cmp < 0) {
                inseriu = InserirStream(&(*raiz)->esq, no);
            } else if (cmp > 0) {
                inseriu = InserirStream(&(*raiz)->dir, no);
            } else {
                /* duplicado: não insere */
                free(no);
                inseriu = 0;
            }
            if (inseriu == 1 && *raiz != NULL) {
                attAlturaStream(*raiz);
                *raiz = balancearStream(*raiz);
            }
        }
    }
    return inseriu;
}

Stream *buscarStream(Stream *raiz, const char *nome)
{
    Stream *res = NULL;
    if (raiz != NULL && nome != NULL) {
        int cmp = strcmp(nome, raiz->info.nomeStream);
        if (cmp == 0) {
            res = raiz;
        } else if (cmp < 0) {
            res = buscarStream(raiz->esq, nome);
        } else {
            res = buscarStream(raiz->dir, nome);
        }
    }
    return res;
}

Stream* maiorValor(Stream* no)
{
    Stream* nav = no;
    if (nav != NULL) {
        while (nav->dir != NULL) {
            nav = nav->dir;
        }
    }
    return nav;
}

/* v) Mostrar todas as streams cadastradas. */
void mostrarStreams(Stream *raiz)
{
    if (raiz != NULL) {
        mostrarStreams(raiz->esq);
        printf("Stream: %s\n", raiz->info.nomeStream);
        mostrarStreams(raiz->dir);
    }
}

/* vi) Mostrar todas as categorias de uma stream específica. */
void mostrarCategoriasStream(Stream *raiz, char *nomeStream)
{
    if (raiz != NULL && nomeStream != NULL) {
        int cmp = strcmp(raiz->info.nomeStream, nomeStream);
        if (cmp == 0) {
            mostrarCategorias(raiz->info.categoria);
        } else if (cmp > 0) {
            mostrarCategoriasStream(raiz->esq, nomeStream);
        } else {
            mostrarCategoriasStream(raiz->dir, nomeStream);
        }
    }
}

/* vii) Programas de uma categoria específica de uma stream específica. */
void mostrarProgDeCatDeStream(Categorias *categoria, Stream *raiz, char *nomeCategoria, char *nomeStream, Programas *programas)
{
    if (raiz != NULL && categoria != NULL && nomeCategoria != NULL && nomeStream != NULL) {
        Stream *st = buscarStream(raiz, nomeStream);
        if (st != NULL && st->info.categoria != NULL) {
            Categorias *cat = buscarCategoria(categoria, nomeCategoria);
            if (cat != NULL && cat->programas != NULL) {
                mostrarProgramas(programas);
            }
        }
    }
}

/* viii) Streams que possuem determinada categoria. */
void mostrarStreamDeCategoria(Stream *raiz, char *nomeCat)
{
    int tem = 0;
    if (raiz != NULL && nomeCat != NULL) {
        mostrarStreamDeCategoria(raiz->esq, nomeCat);

        Categorias *ini = raiz->info.categoria;
        if (ini != NULL) {
            Categorias *nav = ini;
            do {
                if (strcmp(nav->nomeCategoria, nomeCat) == 0) {
                    tem = 1;
                } else {
                    nav = nav->prox;
                }
            } while (nav != ini && tem == 0);
        }

        if (tem) {
            printf("Stream: %s | Site: %s\n", raiz->info.nomeStream, raiz->info.nomeSite);
        }

        mostrarStreamDeCategoria(raiz->dir, nomeCat);
    }
}

/* x) Streams que possuem um tipo de categoria. */
void mostrarStreamDoTipoCategoria(Stream *raiz, int tipoCat)
{
    int tem = 0;
    if (raiz != NULL) {
        Categorias *nav = raiz->info.categoria;
        if (nav != NULL) {
            Categorias *ini = nav;
            do {
                if (nav->tipo == tipoCat) {
                    tem = 1;
                } else {
                    nav = nav->prox;
                }
            } while (nav != ini && tem == 0);
        }

        if (tem) {
            printf("Stream: %s\n", raiz->info.nomeStream);
        }

        mostrarStreamDoTipoCategoria(raiz->esq, tipoCat);
        mostrarStreamDoTipoCategoria(raiz->dir, tipoCat);
    }
}

/* v) In-ordem com site. */
void imprimirInOrdem(Stream *raiz)
{
    if (raiz != NULL) {
        imprimirInOrdem(raiz->esq);
        printf("Stream: %s | Site: %s\n", raiz->info.nomeStream, raiz->info.nomeSite);
        imprimirInOrdem(raiz->dir);
    }
}

/* xvi) Remover categoria da stream (só se não tiver programas). */
int removerCategoriaDaStream(Stream **stream, char *nomeCat)
{
    int ok = 0;
    Categorias *cat = NULL;

    if (stream != NULL && *stream != NULL && nomeCat != NULL) {
        cat = buscarCategoria((*stream)->info.categoria, nomeCat);
        if (cat != NULL) {
            if (cat->programas == NULL) {
                removerCategoria(&(*stream)->info.categoria, nomeCat);
                ok = 1;
            }
        }
    }
    return ok;
}

/* Listar programas por periodicidade e horário em todas as categorias da stream. */
void mostrarProgramasStreamPorPeriodicidadeEHorario(Stream *st, Periocidade p, float h)
{
    if (st != NULL) {
        Categorias *ini = st->info.categoria;
        if (ini != NULL) {
            Categorias *cat = ini;
            while (1) {
                filtrarProgramasPorPeriodicidadeEHorario(cat->programas, p, h);
                cat = cat->prox;
                if (cat == ini) break;
            }
        } else {
            printf("(stream sem categorias)\n");
        }
    }
}

/* Listar programas de uma categoria por periodicidade. */
void mostrarProgramasDaCategoriaPorPeriodicidade(Stream *st, const char *nomeCat, Periocidade p)
{
    if (st != NULL && nomeCat != NULL) {
        Categorias *cats = st->info.categoria;
        Categorias *alvo = NULL;

        if (cats != NULL) {
            alvo = buscarCategoria(cats, (char*)nomeCat);
        }
        if (alvo != NULL) {
            if (alvo->programas != NULL) {
                filtrarProgramasPorPeriodicidade(alvo->programas, p);
            } else {
                printf("Categoria '%s' nao possui programas.\n", nomeCat);
            }
        } else {
            printf("Categoria '%s' nao encontrada nesta stream.\n", nomeCat);
        }
    }
}

/* Remover programa da ABB de uma categoria específica. */
int removerProgramaDaCategoria(Categorias *cat, const char *nomeProg)
{
    int ok = 0;
    if (cat != NULL && nomeProg != NULL) {
        if (cat->programas != NULL) {
            if (removerProgramas(&cat->programas, nomeProg)) {
                printf("Programa '%s' removido da categoria '%s'.\n", nomeProg, cat->nomeCategoria);
                ok = 1;
            } else {
                printf("Programa '%s' nao encontrado na categoria '%s'.\n", nomeProg, cat->nomeCategoria);
            }
        } else {
            printf("Categoria '%s' nao possui programas.\n", cat->nomeCategoria);
        }
    }
    return ok;
}

/* Versão completa: acha STREAM -> CATEGORIA -> remove PROGRAMA */
int removerProgramaDeCategoriaDaStream(Stream *raizStream,
                                       const char *nomeStream,
                                       const char *nomeCategoria,
                                       const char *nomePrograma)
{
    int ok = 0;
    if (raizStream != NULL && nomeStream != NULL &&
        nomeCategoria != NULL && nomePrograma != NULL)
    {
        Stream *st = buscarStream(raizStream, (char*)nomeStream);
        if (st == NULL) {
            printf("Stream '%s' nao encontrada.\n", nomeStream);
        } else {
            Categorias *cat = buscarCategoria(st->info.categoria, (char*)nomeCategoria);
            if (cat == NULL) {
                printf("Categoria '%s' nao encontrada na stream '%s'.\n", nomeCategoria, nomeStream);
            } else {
                ok = removerProgramaDaCategoria(cat, nomePrograma);
            }
        }
    }
    return ok;
}

int existeProgramaDoApresentadorNaStream(Stream *st, const char *nomeApresentador)
{
    int existe = 0;
    if (st != NULL && nomeApresentador != NULL) {
        Categorias *ini = st->info.categoria;
        if (ini != NULL) {
            Categorias *c = ini;
            while (existe == 0) {
                if (programasContemApresentador(c->programas, nomeApresentador)) {
                    existe = 1;
                } else {
                    c = c->prox;
                    if (c == ini) break;
                }
            }
        }
    }
    return existe;
}
