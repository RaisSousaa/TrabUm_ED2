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
// Preenche os dados do programa
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
    int ret = 0; // valor de retorno: 0 = não inseriu, 1 = inseriu

    if (inicio && novo && novo->info.nome[0] != '\0') {
        novo->ant = NULL;
        novo->prox = NULL;

        Apresentadores *atual = *inicio;
        Apresentadores *anterior = NULL;

        while (atual != NULL && strcmp(atual->info.nome, novo->info.nome) < 0) {
            anterior = atual;
            atual = atual->prox;
        }

        if (atual != NULL && strcmp(atual->info.nome, novo->info.nome) == 0) {
            ret = 0; // duplicado → não insere
        } else {
            novo->ant = anterior;
            novo->prox = atual;

            if (anterior) anterior->prox = novo;
            else          *inicio = novo;

            if (atual)   atual->ant = novo;

            ret = 1; // inserção OK
        }
    }

    return ret; 
}


//buscar
Apresentadores* buscarApresentadores(Apresentadores *inicio, const char *nome_busca, int *flag)
{
    Apresentadores *resultado = NULL; 
    int achou = 0;

    if (flag) *flag = 0;

    if (nome_busca != NULL) {
        Apresentadores *atual = inicio;

        while (atual != NULL && !achou) {
            if (strcmp(atual->info.nome, nome_busca) == 0) {
                resultado = atual;
                achou = 1;
                if (flag) *flag = 1;
            } else {
                atual = atual->prox;
            }
        }
    }

    return resultado; 
}



//mostrar
void imprimirApresentadores(Apresentadores *inicio) 
{
    Apresentadores *atual = inicio;
    while (atual) {
        printf("Nome Apresentador: %s | Stream Atual: %s | Categoria que Trabalha: %d\n",
               atual->info.nome,
               atual->info.streamAtual,
               atual->info.ondeTrabalha);

        atual = atual->prox;
    }
}

//liberar memoria


/* ==================== LISTA DO HISTÓRICO (streams passadas) ==================== */


/* cria nó já pronto para uso */
Historico* alocarHistorico(const InfoHistorico *dado)
{
    Historico *no = NULL;

    no = (Historico*) malloc(sizeof(Historico));
    if (no != NULL) {
        no->info = *dado;   /* copia todos os campos */
        no->prox = NULL;    /* já inicializa */
    } else {
        printf("Erro ao alocar memoria de Historico.\n");
    }

    return no; /* único return */
}



int inserirHistoricoOrdenado(Historico **inicio, const InfoHistorico *dado)
{
    int ret = 0; /* 0 = não inseriu (duplicata ou erro), 1 = inseriu */
    int ehDuplicata = 0;
    Historico *novo = NULL;

    if (inicio != NULL && dado != NULL) {
        Historico *atual = *inicio;
        Historico *anterior = NULL;

        /* Avança até encontrar ponto de inserção (ordem por nome) */
        while (atual != NULL && strcmp(atual->info.nomeStream, dado->nomeStream) < 0) {
            anterior = atual;
            atual = atual->prox;
        }

        /* Dentro do bloco de mesmo nome, checa duplicata */
        while (atual != NULL &&
               strcmp(atual->info.nomeStream, dado->nomeStream) == 0 &&
               ehDuplicata == 0) {

            if (atual->info.dataInicio  == dado->dataInicio &&
                atual->info.dataTermino == dado->dataTermino) {
                ehDuplicata = 1;
            } else {
                anterior = atual;
                atual = atual->prox;
            }
        }

        if (ehDuplicata == 0) {
            novo = alocarHistorico((InfoHistorico *)dado);
            if (novo != NULL) {
                /* Insere entre 'anterior' e 'atual' */
                novo->prox = atual;
                if (anterior != NULL) {
                    anterior->prox = novo;
                } else {
                    *inicio = novo;
                }
                ret = 1; /* inserção bem sucedida */
            } else {
                /* falha malloc → ret fica 0 */
            }
        }
        /* se duplicata, ret continua 0 */
    }

    return ret; /* único return */
}



/* imprime a lista do histórico — sem returns (void) */
void imprimirHistorico(const Historico *inicio)
{
    const Historico *p = inicio;

    if (p == NULL) {
        printf("  (sem historico)\n");
    } else {
        while (p != NULL) {
            /* datas são int (AAAAMMDD). Ajuste o formato se mudar o tipo. */
            printf("  - %s | inicio: %d | fim: %d\n",
                   p->info.nomeStream, p->info.dataInicio, p->info.dataTermino);
            p = p->prox;
        }
    }
    /* sem return */
}

/* libera TODA a lista do histórico — sem returns (void) */
void liberarHistorico(Historico **inicio)
{
    Historico *p = NULL;
    Historico *prox = NULL;

    if (inicio != NULL) {
        p = *inicio;
        while (p != NULL) {
            prox = p->prox;
            free(p);
            p = prox;
        }
        *inicio = NULL;
    }
    /* sem return */
}
