#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"apresentadoresAVL.h"
#include"streamAVL.h"


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
    novo->info.streamAtual  = NULL;   
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

    return inseriu; 
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
    return resultado; 
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

/* Percorre a lista de apresentadores e mostra os que trabalham na 'stream' dada */
void mostrarApresentadoresPorStream(Apresentadores *lista, const Stream *stream)
{
    Apresentadores *atual = lista;
    int mostrou = 0;

    while (atual != NULL) {
        if (atual->info.streamAtual == stream) {
            const char *nomeStream = "(sem stream)";
            if (stream && stream->info.nomeStream[0] != '\0') {
                nomeStream = stream->info.nomeStream;
            }
            printf("- %s | Stream: %s | Categoria: %d\n",
                   atual->info.nome, nomeStream, atual->info.ondeTrabalha);
            mostrou = 1;
        }
        atual = atual->prox;
    }

    if (mostrou == 0) {
        if (stream && stream->info.nomeStream[0] != '\0') {
            printf("Nenhum apresentador encontrado para a stream '%s'.\n",
                   stream->info.nomeStream);
        } else {
            printf("Nenhum apresentador encontrado para a stream informada.\n");
        }
    }
}

/* Versão “com nome”: resolve a stream e delega para a função acima */
void mostrarApresentadoresPorNomeStream(Apresentadores *lista, Stream *raizStream, const char *nomeStream)
{
    Stream *stream = NULL;

    if (raizStream != NULL && nomeStream != NULL) {
        stream = buscarStream(raizStream, nomeStream); /* sua ABB de streams */
        if (stream == NULL) {
            printf("Stream '%s' nao encontrada.\n", nomeStream);
        } else {
            mostrarApresentadoresPorStream(lista, stream);
        }
    } else {
        printf("Parametros invalidos.\n");
    }
}

void mostrarApresentadoresPorCategoria(Apresentadores *lista, Tipo categoria)
{
    Apresentadores *atual = lista;
    int mostrou = 0;
    static const char *NOME_CATEGORIA[4] = {"Esporte", "Noticia", "Entreterimento", "Cultura"};

    while (atual != NULL) {
        if (atual->info.ondeTrabalha == categoria) {
            const char *nomeCat = "(desconhecida)";
            int idx = (int)categoria - 1; 
            if (idx >= 0 && idx < 4) {
                nomeCat = NOME_CATEGORIA[idx];
            }

            const char *nomeStream = "(sem stream)";
            if (atual->info.streamAtual && atual->info.streamAtual->info.nomeStream[0] != '\0') {
                nomeStream = atual->info.streamAtual->info.nomeStream;
            }

            printf("- %s | Categoria: %s | Stream Atual: %s\n",
                   atual->info.nome, nomeCat, nomeStream);
            mostrou = 1;
        }
        atual = atual->prox;
    }

    if (mostrou == 0) {
        const char *nomeCat = "(categoria)";
        int idx = (int)categoria - 1; 
        if (idx >= 0 && idx < 4) {
            nomeCat = NOME_CATEGORIA[idx];
        }
        printf("Nenhum apresentador encontrado para a categoria %s.\n", nomeCat);
    }
}

int alterarStreamApresentador(Apresentadores *ap,Stream *novaStream, int dataTerminoAntiga,int dataInicioNova)
{
    int ok = 0;

    if (ap != NULL && novaStream != NULL) {
        /* mesma stream -> nada a fazer */
        if (ap->info.streamAtual == novaStream) {
            printf("Apresentador ja esta na stream '%s'.\n", novaStream->info.nomeStream);
        } else {
            /* TRAVA 1: destino nao pode ter programa apresentado por ele */
            if (existeProgramaDoApresentadorNaStream(novaStream, ap->info.nome)) {
                printf("Nao e possivel transferir: ha programa(s) do apresentador na stream destino '%s'.\n",
                       novaStream->info.nomeStream);
            } else {
                /* (opcional recomendado) TRAVA 2: origem nao pode ter programa ativo do apresentador */
                if (ap->info.streamAtual != NULL &&
                    existeProgramaDoApresentadorNaStream(ap->info.streamAtual, ap->info.nome)) {
                    printf("Nao e possivel transferir: ha programa(s) do apresentador na stream atual '%s'. Remova/altere primeiro.\n",
                           ap->info.streamAtual->info.nomeStream);
                } else {
                    /* fecha histórico anterior (se houver) */
                    if (ap->info.streamAtual != NULL) {
                        finalizarUltimoHistoricoSeAberto(ap->info.historico, dataTerminoAntiga);
                    }
                    /* abre novo histórico na stream destino */
                    InfoHistorico h;
                    strncpy(h.nomeStream, novaStream->info.nomeStream, sizeof h.nomeStream);
                    h.nomeStream[sizeof h.nomeStream - 1] = '\0';
                    h.dataInicio  = dataInicioNova;
                    h.dataTermino = 0;
                    inserirHistorico(&ap->info.historico, &h);

                    /* efetiva a troca */
                    ap->info.streamAtual = novaStream;
                    ok = 1;
                    printf("Transferencia concluida para a stream '%s'.\n", novaStream->info.nomeStream);
                }
            }
        }
    }

    return ok;
}
