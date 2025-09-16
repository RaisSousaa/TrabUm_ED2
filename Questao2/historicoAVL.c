#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "apresentadoresAVL.h"

Historico* alocarHistorico(const InfoHistorico *dado)
{
    Historico *novo = NULL;

    if (dado != NULL) {
        novo = (Historico*) malloc(sizeof(Historico));
        if (novo != NULL) {
            novo->info = *dado;  
            novo->prox = NULL;
        } else {
            printf("Erro ao alocar Historico.\n");
        }
    }
    return novo; 
}

InfoHistorico preencherDadosHistorico(void)
{
    InfoHistorico dados;

    printf("Digite o nome da Stream: ");
    scanf("%49s", dados.nomeStream);

    printf("Digite a data de início (AAAAMMDD): ");
    scanf("%d", &dados.dataInicio);

    // Digite a data de término (AAAAMMDD ou 0 para em curso)
    dados.dataTermino = 0;

    // Validação simples: se término != 0 e menor que início, corrige para "em curso"
    if (dados.dataTermino != 0 && dados.dataTermino < dados.dataInicio) {
        printf("Data término anterior à início. Corrigindo para 0 (em curso).\n");
        dados.dataTermino = 0;
    }

    return dados;
}


int inserirHistorico(Historico **inicio, const InfoHistorico *dado)
{
    int inseriu = 0;

    if (inicio != NULL && dado != NULL) {
        Historico *novo = alocarHistorico(dado);

        if (novo != NULL) {
            // Ordenado por dataInicio DESC (mais recente primeiro)
            Historico *atual = *inicio;
            Historico *anterior = NULL;

            while (atual != NULL &&
                   atual->info.dataInicio > novo->info.dataInicio) {
                anterior = atual;
                atual = atual->prox;
            }

            if (anterior == NULL) {
                // insere no início
                novo->prox = *inicio;
                *inicio = novo;
            } else {
                // insere entre anterior e atual
                novo->prox = atual;
                anterior->prox = novo;
            }

            inseriu = 1;
        }
    }

    return inseriu;
}

Historico* buscar(Historico *inicio, const char *nome)
{
    Historico *achou = NULL;

    if (nome != NULL) {
        Historico *atual = inicio;
        while (atual != NULL && achou == NULL) {
            if (strcmp(atual->info.nomeStream, nome) == 0) {
                achou = atual;
            } else {
                atual = atual->prox;
            }
        }
    }

    return achou; 
}

void imprimirHistorico(const Historico *inicio)
{
    const Historico *atual = inicio;

    if (atual == NULL) {
        printf("(sem histórico)\n");
    } else {
        while (atual != NULL) {
            // Nome da stream
            printf(" - %s | ", atual->info.nomeStream);

            // Data início
            if (atual->info.dataInicio == 0) {

                printf("Indefinido");
            } else {
                int anoI = atual->info.dataInicio / 10000;
                int mesI = (atual->info.dataInicio / 100) % 100;
                int diaI = atual->info.dataInicio % 100;
                printf("%02d/%02d/%04d", diaI, mesI, anoI);
            }

            printf(" a ");

            // Data término
            if (atual->info.dataTermino == 0) {
                printf("Em curso");
            } else {
                int anoF = atual->info.dataTermino / 10000;
                int mesF = (atual->info.dataTermino / 100) % 100;
                int diaF = atual->info.dataTermino % 100;
                printf("%02d/%02d/%04d", diaF, mesF, anoF);
            }

            printf("\n");
            atual = atual->prox;
        }
    }
}

void liberarHistorico(Historico **inicio)
{
    if (inicio != NULL) {
        Historico *atual = *inicio;
        while (atual != NULL) {
            Historico *prox = atual->prox;
            free(atual);
            atual = prox;
        }
        *inicio = NULL;
    }
}

void finalizarUltimoHistoricoSeAberto(Historico *hist, int dataTermino)
{
    Historico *ultimo = hist;

    if (ultimo) {
        while (ultimo->prox) {
            ultimo = ultimo->prox;
        }
        if (ultimo->info.dataTermino == 0) {
            ultimo->info.dataTermino = dataTermino;
        }
    }
}
