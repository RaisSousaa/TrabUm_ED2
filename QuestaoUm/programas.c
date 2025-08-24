#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "programas.h"


/* Helpers: enum -> string*/
const char* getPeriocidadeStr(Periocidade p) 
{
    const char *res;
    if (p == Diario)          res = "Diário";
    else if (p == Semanal)    res = "Semanal";
    else if (p == Mensal)     res = "Mensal";
    else                      res = "Desconhecida";
    return res;
}

const char* getGravacaoStr(Gravacao g) 
{
    const char *res;
    if (g == AoVivo)          res = "Ao Vivo";
    else if (g == SobDemanda) res = "Sob Demanda";
    else                      res = "Desconhecida";
    return res;
}

// Função para alocar memória para um novo programa
Programas* alocarProgramas(infoProgramas dados) 
{
    Programas *no;
    no = (Programas*) malloc (sizeof(Programas));
    if (no == NULL) 
    {
        printf("Erro ao alocar memoria para Programas.\n");
        exit(1);
        // juliana não gosta, colocar flag
    }
    no->esq = NULL;
    no->dir = NULL;
    no->infoProgramas = dados;

    //posteiormente verificar se vai precisar alocar campos, como listas

    return no;
}


// Preenche os dados do programa
infoProgramas preencherDadosPrograma(void)
{
    infoProgramas dados;
    printf("Digite o nome do programa: "); scanf("%s", dados.nomePrograma); // recebe o nome do programa
    printf("Digite a duracao do programa (em horas): "); scanf("%f", &dados.duracao); // recebe a duração
    printf("Digite o tempo de inicio do programa (em horas): "); scanf("%f", &dados.tempoInicio); // recebe o tempo de início
    printf("Digite o nome do apresentador: "); scanf("%s", dados.nomeApresentador); // recebe o nome do apresentador

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

    return dados; // retorna os dados preenchidos
}

//inserção de dados na árvore organizado por nome do programa e sem permitir nome repetido
//pesquisei e vi que é mais eficaz fazer essa verificação na função
int inserirProgramas(Programas **raizProgramas, Programas *no)
{
    int cadastrado = 1;

    if (*raizProgramas == NULL)
    {
        *raizProgramas = no; // insere na raiz/folha
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
            // opcional: no = NULL; // não é necessário aqui
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
        printf("Periodicidade    : %s\n", getPeriocidadeStr(raiz->infoProgramas.periocidade));
        printf("Tipo de gravação : %s\n", getGravacaoStr(raiz->infoProgramas.gravacao));

        mostrarProgramas(raiz->dir);
    }
}


//abaixo serão as funções de mostrar