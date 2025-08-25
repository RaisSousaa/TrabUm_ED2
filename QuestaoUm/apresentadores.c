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

    //novo->data = valor;
    novo->ant = NULL;
    novo->prox = NULL;
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
