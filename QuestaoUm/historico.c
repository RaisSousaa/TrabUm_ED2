#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"historico.h"



/* cria nó já pronto para uso */
Historico* alocarHistorico(const InfoHistorico *dado)
{
    Historico *no = NULL;

    no = (Historico*) malloc(sizeof(Historico));
    if (no == NULL) {
        printf("Erro ao alocar memoria de Historico.\n");
    }
    no->info = *dado;   /* copia todos os campos */
    no->prox = NULL;    /* já inicializa */

    return no; 
}

int inserirHistorico(Historico **inicio, const InfoHistorico *dado) {
    int cadastro = 0;  // 0 = não inseriu, 1 = inseriu

    if (inicio != NULL && dado != NULL) {

        if (*inicio == NULL) {
            // lista vazia → insere aqui
            Historico *novo = alocarHistorico((InfoHistorico *)dado);
            if (novo != NULL) {
                novo->prox = NULL;
                *inicio = novo;
                cadastro = 1;
            }
        }
        else {
            int cmp = strcmp((*inicio)->info.nomeStream, dado->nomeStream);

            if (cmp > 0) {
                // insere antes do nó atual
                Historico *novo = alocarHistorico((InfoHistorico *)dado);
                if (novo != NULL) {
                    novo->prox = *inicio;
                    *inicio = novo;
                    cadastro = 1;
                }
            }
            else if (cmp == 0 &&
                     (*inicio)->info.dataInicio  == dado->dataInicio &&
                     (*inicio)->info.dataTermino == dado->dataTermino) {
                // duplicata → não insere, cadastro continua 0
            }
            else {
                // chama recursivamente no próximo
                cadastro = inserirHistorico(&(*inicio)->prox, dado);
            }
        }
    }

    return cadastro; // único ponto de saída
}


Historico* buscar(Historico *inicio, const char *nome) {
    Historico *resultado = NULL;

    if (inicio != NULL) {
        if (strcmp(inicio->info.nomeStream, nome) == 0) {
            resultado = inicio;
        } else {
            resultado = buscar(inicio->prox, nome);
        }
    }

    return resultado;  // único return
}


//no imprimir historico ta entrando no primeiro printf
void imprimirHistorico(const Historico *inicio)
{
    if (inicio == NULL) {
        printf("  (sem historico)\n");
    } else {
        printf("  - %s | inicio: %d | fim: %d\n",
               inicio->info.nomeStream, inicio->info.dataInicio, inicio->info.dataTermino);
        imprimirHistorico(inicio->prox);
    }
}


/* libera TODA a lista do histórico */
void liberarHistorico(Historico **inicio) 
{
    if (*inicio != NULL) {
        liberarHistorico(&(*inicio)->prox);  // chama para o próximo
        free(*inicio);                       // libera o atual
        *inicio = NULL;                      // zera ponteiro
    }
}
