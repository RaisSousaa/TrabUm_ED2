#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"apresentadores.h"
#include"historico.h"
#include"stream.h"


Apresentadores* alocarApresentador(void) 
{
    Apresentadores *novo = (Apresentadores*) malloc(sizeof(Apresentadores));
    if (novo == NULL) {
        printf("Erro ao alocar memória!\n");
        return NULL;
    }

    /* ligações da lista */
    novo->ant = NULL;
    novo->prox = NULL;

    /* zere/initialize os campos do InfoApresentador */
    novo->info.nome[0]      = '\0';
    novo->info.ondeTrabalha = 0;      /* opcional: enum inválido */
    novo->info.streamAtual  = NULL;   /* <<< ESSENCIAL */
    novo->info.historico    = NULL;
    novo->info.programas    = NULL;

    return novo;
}


// Preenche dados de apresentador
InfoApresentador preencherDadosApresentador(void)
{
    InfoApresentador dados;

    /* inicialize tudo manualmente */
    dados.nome[0]           = '\0';
    dados.ondeTrabalha      = 0;     /* ainda não escolhido */
    dados.streamAtual       = NULL;
    dados.historico         = NULL;
    dados.programas         = NULL;

    printf("Digite o nome do apresentador: ");
    scanf(" %49s", dados.nome);  

    printf("Escolha a categoria em que apresentador trabalha:\n");
    printf("1. Esportes\n2. Noticia\n3. Entreterimento\n4. Cultura\n");

    int tipoCategoria;
    scanf("%d", &tipoCategoria);

    switch (tipoCategoria)
    {
        case 1: 
            dados.ondeTrabalha = Esporte;        
            break;
        case 2: 
            dados.ondeTrabalha = Noticia;        
            break;
        case 3:
            dados.ondeTrabalha = Entreterimento; 
            break;
        case 4: 
            dados.ondeTrabalha = Cultura;
                break;
        default:
            printf("Opcao invalida. Definindo categoria como Entreterimento.\n");
            dados.ondeTrabalha = Entreterimento;
            break;
    }

    return dados;  /* único return */
}


// Lista ordenada dinamicamente duplamente encadeada
//Inserção ordenada por nome do apresentador
int inserirApresentador(Apresentadores **inicio, Apresentadores *novo)
{
    int inseriu   = 0;   /* 1 = inseriu, 0 = não inseriu */
    int duplicado = 0;

    if (inicio != NULL && novo != NULL && novo->info.nome[0] != '\0') {

        Apresentadores *atual     = *inicio;
        Apresentadores *anterior  = NULL;

        /* percorre até achar posição, duplicata, ou fim */
        while (atual != NULL && inseriu == 0 && duplicado == 0) {
            int cmp = strcmp(novo->info.nome, atual->info.nome);

            if (cmp == 0) {
                /* nome igual -> não insere */
                duplicado = 1;
            } else if (cmp < 0) {
                /* insere antes de 'atual' */
                novo->ant  = atual->ant;
                novo->prox = atual;
                atual->ant = novo;

                if (anterior == NULL) {
                    *inicio = novo;
                } else {
                    anterior->prox = novo;
                }
                inseriu = 1;
            } else {
                /* continua andando */
                anterior = atual;
                atual    = atual->prox;
            }
        }

        /* se não duplicou e não inseriu dentro do laço, insere no fim */
        if (duplicado == 0 && inseriu == 0) {
            novo->ant  = anterior;
            novo->prox = NULL;

            if (anterior == NULL) {
                *inicio = novo;      /* lista vazia */
            } else {
                anterior->prox = novo;
            }
            inseriu = 1;
        }
    }

    return inseriu;  /* único return */
}



//buscar
Apresentadores* buscarApresentadores(Apresentadores *inicio, const char *nome_busca, int *encontrou)
{
    Apresentadores *resultado = NULL;

    if (encontrou != NULL) {
        *encontrou = 0; // estado inicial: não encontrou
    }

    if (nome_busca != NULL) {
        if (inicio != NULL) {
            if (strcmp(inicio->info.nome, nome_busca) == 0) {
                resultado = inicio;
                if (encontrou != NULL) {
                    *encontrou = 1;
                }
            } else {
                // chama recursivamente no próximo nó
                resultado = buscarApresentadores(inicio->prox, nome_busca, encontrou);
            }
        }
    }

    return resultado; // único ponto de saída
}

void imprimirApresentadores(Apresentadores *inicio)
{
    Apresentadores *atual = inicio;
    static const char *NOME_CATEGORIA[4] = {"Esporte", "Noticia", "Entreterimento", "Cultura"};

    while (atual != NULL) {
        const char *nomeStreamAtual;

        if (atual->info.streamAtual != NULL &&
            atual->info.streamAtual->info.nomeStream[0] != '\0') {
            nomeStreamAtual = atual->info.streamAtual->info.nomeStream;
        } else {
            nomeStreamAtual = "(sem stream)";
        }

        printf("Nome Apresentador: %s | Stream Atual: %s | Categoria que Trabalha: %d\n",
               atual->info.nome,
               nomeStreamAtual,                       
               atual->info.ondeTrabalha);

        atual = atual->prox;
    }
}


void liberarApresentadores(Apresentadores **inicio)
{
    if (inicio != NULL && *inicio != NULL) {
        // libera primeiro o histórico do nó atual (se houver)
        if ((*inicio)->info.historico != NULL) {
            liberarHistorico(&(*inicio)->info.historico);
        }

        // libera recursivamente a cauda
        liberarApresentadores(&(*inicio)->prox);

        // libera o nó atual
        free(*inicio);
        *inicio = NULL; // garante que o ponteiro fique nulo ao voltar
    } else if (inicio != NULL) {
        *inicio = NULL; // normaliza se já vier NULL
    }
}
