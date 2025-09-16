#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "programas.h"


// Função para alocar memória para um novo programa
Programas* alocarProgramas(infoProgramas dados) 
{
    Programas *no = NULL;

    no = (Programas*) malloc (sizeof(Programas));
    if (no == NULL) 
    {
        printf("Erro ao alocar memoria para Programas.\n");
        
    }
    no->esq = NULL;
    no->dir = NULL;
    no->infoProgramas = dados;
    return no;
}

infoProgramas preencherDadosPrograma(void)
{
    infoProgramas dados;
    printf("Digite o nome do programa: "); scanf("%s", dados.nomePrograma); 
    printf("Digite a duracao do programa (em horas): "); scanf("%f", &dados.duracao); 
    printf("Digite o tempo de inicio do programa (em horas): "); scanf("%f", &dados.tempoInicio); 
    printf("Digite o nome do apresentador: "); scanf("%s", dados.nomeApresentador); 

    int periocidade;
    printf("Escolha a periocidade do programa:\n1. Diario\n2. Semanal\n3. Mensal\n");
    scanf("%d", &periocidade);
    switch(periocidade)
    {
        case 1:
            dados.periocidade = Diario;
            break;
        case 2:
            dados.periocidade = Semanal;
            break;
        case 3:
            dados.periocidade = Mensal;
            break;
        default:
            printf("Opcao invalida. Definindo periocidade como Diario.\n");
            dados.periocidade = Diario;
            break;
    }

    int gravacao;
    printf("Escolha o tipo de gravacao do programa:\n1. Ao Vivo\n2. Sob Demanda\n");
    scanf("%d", &gravacao);
    switch(gravacao){
        case 1:
            dados.gravacao = AoVivo;
            break;
        case 2:
            dados.gravacao = SobDemanda;
            break;
        default:
            printf("Opcao invalida. Definindo gravacao como Ao Vivo.\n");
            dados.gravacao = AoVivo;
            break;
    }

    return dados; 
}

int inserirProgramas(Programas **raizProgramas, Programas *no)
{
    int cadastrado = 1;

    if (*raizProgramas == NULL)
    {
        *raizProgramas = no; 
    }
    else
    {
        int cmp = strcmp(no->infoProgramas.nomePrograma, (*raizProgramas)->infoProgramas.nomePrograma);

        if (cmp < 0)
        {
            cadastrado = inserirProgramas(&(*raizProgramas)->esq, no);
        }
        else if (cmp > 0)
        {
            cadastrado = inserirProgramas(&(*raizProgramas)->dir, no);
        }
        else
        {
            // DUPLICADO: mesmo nomePrograma
            cadastrado = 0;
            free(no);              // evita vazamento

        }
    }
    return cadastrado;
}

// Procura programa por nome
Programas *buscarProgramas(Programas *raiz, const char *nomeProgramas)
{
    Programas *encontrado;
    encontrado = NULL; 
    if (raiz != NULL)
    {
        if(strcmp(raiz->infoProgramas.nomePrograma, nomeProgramas) == 0)
        {
            encontrado = raiz; // encontra o Programas
        }
        else if(strcmp(raiz->infoProgramas.nomePrograma, nomeProgramas) > 0)
        {
            encontrado = buscarProgramas(raiz->esq, nomeProgramas); // busca na subarvore esquerda
        } 
        else
        {
            encontrado = buscarProgramas(raiz->dir, nomeProgramas); // busca na subarvore direita
        }     
    }
    return(encontrado); // retorna o Programas encontrado ou NULL se não encontrado
}

void mostrarProgramas(Programas *raiz)
{
    if (raiz != NULL)
    {
        mostrarProgramas(raiz->esq);

        printf("--------------------------------------------------\n");
        printf("Nome do programa : %s\n", raiz->infoProgramas.nomePrograma);
        printf("Duração          : %.2fh\n", raiz->infoProgramas.duracao);
        printf("Horário de início: %.2fh\n", raiz->infoProgramas.tempoInicio);
        printf("Apresentador     : %s\n", raiz->infoProgramas.nomeApresentador);
        printf("Periodicidade    : %d\n", raiz->infoProgramas.periocidade);
        printf("Tipo de gravação : %d\n", raiz->infoProgramas.gravacao);

        mostrarProgramas(raiz->dir);
    }
}

int removerProgramas(Programas **raizProgramas, const char *nomePrograma)
{
    int removido = 0;

    if (raizProgramas != NULL && *raizProgramas != NULL && nomePrograma != NULL)
    {
        Programas *no = *raizProgramas;
        int cmp = strcmp(nomePrograma, no->infoProgramas.nomePrograma);

        if (cmp < 0)
        {
            /* busca na subárvore esquerda */
            removido = removerProgramas(&no->esq, nomePrograma);
        }
        else if (cmp > 0)
        {
            /* busca na subárvore direita */
            removido = removerProgramas(&no->dir, nomePrograma);
        }
        else
        {
            /* achou o nó a remover */
            if (no->esq == NULL && no->dir == NULL)
            {
                /* caso 1: folha */
                free(no);
                *raizProgramas = NULL;
                removido = 1;
            }
            else if (no->esq == NULL || no->dir == NULL)
            {
                /* caso 2: só 1 filho */
                Programas *filho = (no->esq != NULL) ? no->esq : no->dir;
                free(no);
                *raizProgramas = filho;
                removido = 1;
            }
            else
            {
                /* caso 3: dois filhos -> usar sucessor em-ordem (menor da direita) */
                Programas *paiSucc = no;
                Programas *succ = no->dir;

                while (succ->esq != NULL)
                {
                    paiSucc = succ;
                    succ = succ->esq;
                }

                /* copia os dados do sucessor para o nó atual */
                no->infoProgramas = succ->infoProgramas;

                /* retira o sucessor da árvore (ele tem no máx. 1 filho à direita) */
                if (paiSucc == no)
                {
                    paiSucc->dir = succ->dir;   /* sucessor era o filho direito direto */
                }
                else
                {
                    paiSucc->esq = succ->dir;   /* “puxa” o filho direito do sucessor */
                }

                free(succ);
                removido = 1;
            }
        }
    }

    return removido; 
}

int programasContemApresentador(Programas *raiz, const char *nomeApresentador)
{
    int achou = 0;

    if (raiz) {
        if (strcmp(raiz->infoProgramas.nomeApresentador, nomeApresentador) == 0) {
            achou = 1;
        } else {
            if (programasContemApresentador(raiz->esq, nomeApresentador)) {
                achou = 1;
            } else if (programasContemApresentador(raiz->dir, nomeApresentador)) {
                achou = 1;
            }
        }
    }

    return achou; 
}

void filtrarProgramasPorPeriodicidadeEHorario(Programas *raiz, Periocidade periodicidade, float horario)
{
    if (raiz != NULL)
    {
        filtrarProgramasPorPeriodicidadeEHorario(raiz->esq, periodicidade, horario);

        if (raiz->infoProgramas.periocidade == periodicidade &&
            raiz->infoProgramas.tempoInicio   == horario)
        {
            printf("Programa: %s | Inicio: %.2fh | Duracao: %.2fh | Apresentador: %s\n",
                   raiz->infoProgramas.nomePrograma,
                   raiz->infoProgramas.tempoInicio,
                   raiz->infoProgramas.duracao,
                   raiz->infoProgramas.nomeApresentador);
        }

        filtrarProgramasPorPeriodicidadeEHorario(raiz->dir, periodicidade, horario);
    }
}

void filtrarProgramasPorPeriodicidade(Programas *raiz, Periocidade periodicidade)
{
    if (raiz != NULL)
    {
        filtrarProgramasPorPeriodicidade(raiz->esq, periodicidade);

        if (raiz->infoProgramas.periocidade == periodicidade)
        {
            printf("Programa: %s | Inicio: %.2fh | Duracao: %.2fh | Apresentador: %s\n",
                   raiz->infoProgramas.nomePrograma,
                   raiz->infoProgramas.tempoInicio,
                   raiz->infoProgramas.duracao,
                   raiz->infoProgramas.nomeApresentador);
        }

        filtrarProgramasPorPeriodicidade(raiz->dir, periodicidade);
    }
}
