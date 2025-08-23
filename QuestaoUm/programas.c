#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "programas.h"

// Função para alocar memória para um novo programa
Programas* alocarProgramas(infoProgramas dados) 
{
    Programas *no;
    no = (Programas*) malloc (sizeof(Programas));
    if (no) 
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
infoProgramas preencherDadosPrograma()
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

//inserir dados na árvore organizado por nome apresentador
int inserirProgramas(Programas **raizProgramas, Programas *no)
{
    int cadastrado = 1;

    if (*raizProgramas)
    {
        *raizProgramas = no; //Para inserir na Raiz
    }
    else
    {
        //verifica onde inserir pelo nome do programa
        if (strcmp((*raizProgramas)->infoProgramas.nomeApresentador, no->infoProgramas.nomeApresentador) > 0)
        {
            cadastrado = inserirProgramas(&(*raizProgramas)->esq, no);
        }
        else if (strcmp((*raizProgramas)->infoProgramas.nomeApresentador, no->infoProgramas.nomeApresentador) < 0)
        {
            cadastrado = inserirProgramas(&(*raizProgramas)->dir, no);
        }
        else
        {
            cadastrado = 0; 
        }
    }
    return(cadastrado);    
}

// Procura um album pelo titulo
Programas *buscarProgramas(Programas *raiz, char *nomeProgramas)
{
    Programas *encontrado;
    encontrado = NULL; 
    if (raiz != NULL)
    {
        if(strcmp(raiz->infoProgramas.nomeApresentador, nomeProgramas) == 0)
        {
            encontrado = raiz; // encontra o Programas
        }
        else if(strcmp(raiz->infoProgramas.nomeApresentador, nomeProgramas) > 0)
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
