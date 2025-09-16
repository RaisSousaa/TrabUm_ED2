#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "programasAVL.h"



static int alturaProg(Programas *no) // retorna altura do nó
{
    int alt = 0;
    if (no != NULL) {
        alt = no->altura;
    }
    return alt;
}

static int maiorAlt(int altEsq, int altDir) // retorna maior entre duas alturas
{
    int maior = altEsq;
    if (altDir > altEsq) {
        maior = altDir;
    }
    return maior;
}

static void atualizaAlt(Programas *no) // atualiza altura do nó
{
    if (no != NULL) {
        int altEsq = alturaProg(no->esq);
        int altDir = alturaProg(no->dir);
        no->altura = 1 + maiorAlt(altEsq, altDir);
    }
}

static int fbProg(Programas *no) // fator de balanceamento
{
    int fb = 0;
    if (no != NULL) {
        fb = alturaProg(no->esq) - alturaProg(no->dir);
    }
    return fb;
}

static Programas* rotDirProg(Programas *raiz) // rotaçao direita
{
    Programas *novaRaiz = raiz;
    if (raiz != NULL && raiz->esq != NULL) {
        Programas *filhoEsq = raiz->esq;
        Programas *subDir   = filhoEsq->dir;

        filhoEsq->dir = raiz;
        raiz->esq     = subDir;

        atualizaAlt(raiz);
        atualizaAlt(filhoEsq);

        novaRaiz = filhoEsq;
    }
    return novaRaiz;
}

static Programas* rotEsqProg(Programas *raiz)
{
    Programas *novaRaiz = raiz;
    if (raiz != NULL && raiz->dir != NULL) {
        Programas *filhoDir = raiz->dir;
        Programas *subEsq   = filhoDir->esq;

        filhoDir->esq = raiz;
        raiz->dir     = subEsq;

        atualizaAlt(raiz);
        atualizaAlt(filhoDir);

        novaRaiz = filhoDir;
    }
    return novaRaiz;
}

static Programas* balancearProg(Programas *raiz)
{
    Programas *novaRaiz = raiz;

    if (raiz != NULL) {
        int fb = fbProg(raiz);

        if (fb >= 2 && fbProg(raiz->esq) >= 0) 
        {
            novaRaiz = rotDirProg(raiz);                 /* Esq-Esq */
        } else 
            if (fb >= 2 && fbProg(raiz->esq) < 0) {
            raiz->esq = rotEsqProg(raiz->esq);           /* Esq-Dir */
            novaRaiz  = rotDirProg(raiz);
        } else 
            if (fb <= -2 && fbProg(raiz->dir) <= 0) {
            novaRaiz = rotEsqProg(raiz);                 /* Dir-Dir */
        } else 
            if (fb <= -2 && fbProg(raiz->dir) > 0) {
            raiz->dir = rotDirProg(raiz->dir);           /* Dir-Esq */
            novaRaiz  = rotEsqProg(raiz);
        }
    }
    return novaRaiz;
}

static Programas* minNoProg(Programas *no) // nó com o menor valor (mais à esquerda)
{
    Programas *atual = no;
    if (atual != NULL) {
        while (atual->esq != NULL) {
            atual = atual->esq;
        }
    }
    return atual;
}

Programas* alocarProgramas(infoProgramas dados) 
{
    Programas *no = (Programas*) malloc(sizeof(Programas));
    if (no == NULL) {
        printf("Erro ao alocar memoria para Programas.\n");
    } else {
        no->esq = NULL;
        no->dir = NULL;
        no->altura = 1;                 /* AVL: nó novo */
        no->infoProgramas = dados;
    }
    return no;
}

infoProgramas preencherDadosPrograma(void)
{
    infoProgramas d;

    printf("Digite o nome do programa: ");
    scanf("%49s", d.nomePrograma);

    printf("Digite a duracao do programa (em horas): ");
    scanf("%f", &d.duracao);

    printf("Digite o tempo de inicio do programa (em horas): ");
    scanf("%f", &d.tempoInicio);

    printf("Digite o nome do apresentador: ");
    scanf("%49s", d.nomeApresentador);

    printf("Escolha a periocidade do programa:\n1. Diario\n2. Semanal\n3. Mensal\n");
    int per = 0;
    scanf("%d", &per);
    switch (per) {
        case 1: d.periocidade = Diario;  break;
        case 2: d.periocidade = Semanal; break;
        case 3: d.periocidade = Mensal;  break;
        default:
            printf("Opcao invalida. Definindo periocidade como Diario.\n");
            d.periocidade = Diario;
            break;
    }

    printf("Escolha o tipo de gravacao do programa:\n1. Ao Vivo\n2. Sob Demanda\n");
    int grv = 0;
    scanf("%d", &grv);
    switch (grv) {
        case 1: d.gravacao = AoVivo;     break;
        case 2: d.gravacao = SobDemanda; break;
        default:
            printf("Opcao invalida. Definindo gravacao como Ao Vivo.\n");
            d.gravacao = AoVivo;
            break;
    }

    return d; 
}

int inserirProgramas(Programas **raiz, Programas *no)
{
    int inseriu = 0;

    if (raiz != NULL && no != NULL) 
    {
        if (*raiz == NULL) 
        {
            *raiz = no;
            inseriu = 1;
        } else {
            int cmp = strcmp(no->infoProgramas.nomePrograma, (*raiz)->infoProgramas.nomePrograma);
            if (cmp < 0) {
                inseriu = inserirProgramas(&(*raiz)->esq, no);
            } else if (cmp > 0) {
                inseriu = inserirProgramas(&(*raiz)->dir, no);
            } else {
                /* duplicado */
                free(no);
                inseriu = 0;
            }

            if (inseriu == 1 && *raiz != NULL) 
            {
                atualizaAlt(*raiz);
                *raiz = balancearProg(*raiz);
            }
        }
    }
    return inseriu;
}

Programas *buscarProgramas(Programas *raiz, const char *nome)
{
    Programas *achou = NULL;

    if (raiz != NULL && nome != NULL) {
        int cmp = strcmp(raiz->infoProgramas.nomePrograma, nome);
        if (cmp == 0) {
            achou = raiz;
        } else if (cmp > 0) {
            achou = buscarProgramas(raiz->esq, nome);
        } else {
            achou = buscarProgramas(raiz->dir, nome);
        }
    }
    return achou;
}

void mostrarProgramas(Programas *raiz)
{
    if (raiz != NULL) {
        mostrarProgramas(raiz->esq);

        printf("--------------------------------------------------\n");
        printf("Nome do programa : %s\n",  raiz->infoProgramas.nomePrograma);
        printf("Duração          : %.2fh\n", raiz->infoProgramas.duracao);
        printf("Horário de início: %.2fh\n", raiz->infoProgramas.tempoInicio);
        printf("Apresentador     : %s\n",  raiz->infoProgramas.nomeApresentador);
        printf("Periodicidade    : %d\n",  raiz->infoProgramas.periocidade);
        printf("Tipo de gravação : %d\n",  raiz->infoProgramas.gravacao);

        mostrarProgramas(raiz->dir);
    }
}

int removerProgramas(Programas **raiz, const char *nome)
{
    int removido = 0;

    if (raiz != NULL && *raiz != NULL && nome != NULL) {
        Programas *no = *raiz;
        int cmp = strcmp(nome, no->infoProgramas.nomePrograma);

        if (cmp < 0) {
            removido = removerProgramas(&no->esq, nome);
        } else if (cmp > 0) {
            removido = removerProgramas(&no->dir, nome);
        } else {
            /* achou o nó-alvo */
            if (no->esq == NULL && no->dir == NULL) {
                free(no);
                *raiz = NULL;
                removido = 1;
            } else if (no->esq == NULL || no->dir == NULL) {
                /* exatamente 1 filho */
                Programas *filho;
                if (no->esq != NULL) {
                    filho = no->esq;
                } else {
                    filho = no->dir;
                }
                free(no);
                *raiz = filho;
                removido = 1;
            } else {
                /* dois filhos: substitui pelo menor da subárvore direita (sucessor) */
                Programas *succ = minNoProg(no->dir);
                infoProgramas backup = succ->infoProgramas;   /* copia dados */
                removido = removerProgramas(&no->dir, succ->infoProgramas.nomePrograma);
                if (removido) {
                    (*raiz)->infoProgramas = backup;
                }
            }
        }

        if (removido == 1 && *raiz != NULL) {
            atualizaAlt(*raiz);
            *raiz = balancearProg(*raiz);
        }
    }

    return removido;
}

int programasContemApresentador(Programas *raiz, const char *nomeAp)
{
    int achou = 0;
    if (raiz != NULL && nomeAp != NULL) {
        if (strcmp(raiz->infoProgramas.nomeApresentador, nomeAp) == 0) {
            achou = 1;
        } else {
            if (programasContemApresentador(raiz->esq, nomeAp)) {
                achou = 1;
            } else if (programasContemApresentador(raiz->dir, nomeAp)) {
                achou = 1;
            }
        }
    }
    return achou;
}

void filtrarProgramasPorPeriodicidadeEHorario(Programas *raiz, Periocidade p, float h)
{
    if (raiz != NULL) {
        filtrarProgramasPorPeriodicidadeEHorario(raiz->esq, p, h);

        if (raiz->infoProgramas.periocidade == p &&
            raiz->infoProgramas.tempoInicio   == h) {
            printf("Programa: %s | Inicio: %.2fh | Duracao: %.2fh | Apresentador: %s\n",
                   raiz->infoProgramas.nomePrograma,
                   raiz->infoProgramas.tempoInicio,
                   raiz->infoProgramas.duracao,
                   raiz->infoProgramas.nomeApresentador);
        }

        filtrarProgramasPorPeriodicidadeEHorario(raiz->dir, p, h);
    }
}

void filtrarProgramasPorPeriodicidade(Programas *raiz, Periocidade p) // filtra por periodicidade
{
    if (raiz != NULL) {
        filtrarProgramasPorPeriodicidade(raiz->esq, p);

        if (raiz->infoProgramas.periocidade == p) {
            printf("Programa: %s | Inicio: %.2fh | Duracao: %.2fh | Apresentador: %s\n",
                   raiz->infoProgramas.nomePrograma,
                   raiz->infoProgramas.tempoInicio,
                   raiz->infoProgramas.duracao,
                   raiz->infoProgramas.nomeApresentador);
        }

        filtrarProgramasPorPeriodicidade(raiz->dir, p);
    }
}
