#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"apresentadores.h"

//alocar
Apresentadores* alocarApresentador(void) 
{
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
    
    int categoria;
    printf("Escolha a categoria em que apresentador trabalha:\n1. Esportes\n2. Noticia\n3. Entreterimento\n4. Cultura\n");
    scanf("%d", &categoria);
    switch(categoria)
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

        if (*inicio == NULL) {
            /* Caso base: lista vazia → insere aqui */
            novo->ant = NULL;
            novo->prox = NULL;
            *inicio = novo;
            cadastro = 1;
        }
        else {
            int cmp = strcmp((*inicio)->info.nome, novo->info.nome);

            if (cmp > 0) {
                /* Inserir ANTES do nó atual (*inicio) */
                novo->ant  = (*inicio)->ant;  // pode ser NULL se era cabeça
                novo->prox = *inicio;
                (*inicio)->ant = novo;

                *inicio = novo; // conecta no lugar certo (início ou meio)
                cadastro = 1;
            }
            else if (cmp == 0) {
                /* Duplicata → não insere; cadastro continua 0 */
            }
            else { /* cmp < 0 → recursão no próximo */
                cadastro = inserirApresentador(&(*inicio)->prox, novo);
            }
        }
    }

    return cadastro; 
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
    if (inicio == NULL) {
        return; // lista vazia → nada a imprimir (mesmo comportamento da sua versão)
    }

    printf("Nome Apresentador: %s | Stream Atual: %s | Categoria que Trabalha: %d\n",
           inicio->info.nome,
           inicio->info.streamAtual,
           inicio->info.ondeTrabalha);

    imprimirApresentadores(inicio->prox); // imprime o resto
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
