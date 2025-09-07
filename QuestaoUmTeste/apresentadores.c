#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"apresentadores.h"
#include"historico.h"

//alocar
Apresentadores* alocarApresentador(void) 
{
    int inseriu;
    Apresentadores *novo = NULL;

    novo = (Apresentadores*) malloc(sizeof(Apresentadores));
    if (novo == NULL) {
        printf("Erro ao alocar memória!\n");
    }
    novo->ant = NULL;
    novo->prox = NULL;
    novo->info.historico = NULL;   

    return novo;
}

// Preenche dados de apresentador
//colocar para preencher no main, aqui ta por enquanto para teste
InfoApresentador preencherDadosApresentador(void)
{
    InfoApresentador dados;
    printf("Digite o nome do apresentador: "); scanf("%s", dados.nome); // recebe o nome do apresentador
    printf("Digite Stream Atual: "); scanf("%s", dados.streamAtual); // recebe stream atual
    
    int tipoCategoria;
    printf("Escolha a categoria em que apresentador trabalha:\n1. Esportes\n2. Noticia\n3. Entreterimento\n4. Cultura\n");
    scanf("%d", &tipoCategoria);
    switch(tipoCategoria)
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


    return dados; // retorna os dados preenchidos
}

// Lista ordenada dinamicamente duplamente encadeada
//Inserção ordenada por nome do apresentador
int inserirApresentador(Apresentadores **inicio, Apresentadores *novo)
{
    int cadastro = 0; // 0 = não inseriu, 1 = inseriu

    if (inicio != NULL && novo != NULL && novo->info.nome[0] != '\0') {

        Apresentadores *atual = *inicio;
        Apresentadores *anterior = NULL;

        while (atual != NULL && cadastro == 0) {
            int cmp = strcmp(novo->info.nome, atual->info.nome);

            if (cmp == 0) {
                // duplicata → não insere
                cadastro = 0;
            } else if (cmp < 0) {
                // inserir antes de 'atual'
                novo->ant  = atual->ant;
                novo->prox = atual;
                atual->ant = novo;

                if (anterior == NULL) {
                    *inicio = novo; // inseriu no início
                } else {
                    anterior->prox = novo;
                }

                cadastro = 1;
            } else {
                anterior = atual;
                atual = atual->prox;
            }
        }

        if (cadastro == 0 && atual == NULL) {
            // chegou ao fim insere no final
            novo->ant  = anterior;
            novo->prox = NULL;

            if (anterior == NULL) {
                *inicio = novo; // lista estava vazia
            } else {
                anterior->prox = novo;
            }

            cadastro = 1;
        }
    }

    return cadastro; // único return no fim
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

//mostrar
void imprimirApresentadores(Apresentadores *inicio)
{
    Apresentadores *atual = inicio;

    while (atual != NULL) {
        printf("Nome Apresentador: %s | Stream Atual: %s | Categoria que Trabalha: %d\n",
               atual->info.nome,
               atual->info.streamAtual,
               atual->info.ondeTrabalha);

        atual = atual->prox;
    }

    return; // único return no fim
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
