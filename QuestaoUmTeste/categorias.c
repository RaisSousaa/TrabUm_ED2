#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "categorias.h"

char *tipos_char[] = {"Esporte", "Noticia", "Entreterimento", "Cultura"};


Categorias* alocarCategorias(void)
{
    Categorias* novo = NULL; // variável de retorno

    novo = (Categorias*) malloc(sizeof(Categorias));
    if (novo == NULL) {
        printf("Erro ao alocar memoria para Categorias.\n");
        // não altera 'novo', ele continua NULL (sinal de falha)
    } else {
        novo->prox = NULL;
        novo->programas = NULL;
    }

    return novo; 
}


Categorias preencherDadosCategoria(void)
{
    int escolha;

    Categorias no;
    no.programas = NULL; // no programas inicializa aqui, é aqui msm ?
    no.prox = NULL;    

    printf("Digite o nome da Categoria: "); scanf("%s", no.nomeCategoria);

    printf("Escolha o tipo da categoria: \n");
    printf("1 - Esporte \n");
    printf("2 - Noticia \n");
    printf("3 - Entreterimento \n");
    printf("4 - Cultura \n");
    printf("Sua escolha ");
    scanf("%d", &escolha);

    switch (escolha)
    {
    case 1:
        no.tipo = Esporte;
        break;
    case 2:
        no.tipo = Noticia;
        break;
    case 3:
        no.tipo = Entreterimento;
        break;
    case 4:
        no.tipo = Cultura;
        break;
    default:
        printf("Opção inválida.\n");
        break;
    }

    return no;

}

int inserirCategoria(Categorias **inicio, Categorias *novo)
{
    int resultado = 1; // 0 = não inseriu, 1 = inseriu
    int parar = 0; //controle do flag
    

    if (*inicio == NULL)
    {
        novo->prox = novo;
        *inicio = novo;
    }
    else
    {
        Categorias *noAtual = *inicio;
        Categorias *ant = NULL;

        //entra em um loop para buscar a posição correta de inserção
        do {
            int cmp = strcmp(novo->nomeCategoria, noAtual->nomeCategoria);

            if (cmp == 0)
            {
                //caso 1
                //não insere pois nome repetido
                resultado = 0;
                parar = 1;
            }else if (cmp < 0){
                //caso 2
                //encontrou posição de inserção (novo vem antes de atual)
                parar = 1;

            }else{
                //continua no loop ate encontrar posição
                ant = noAtual;
                noAtual = noAtual->prox;
            }
            
        } while (!parar && noAtual != *inicio);

        if (resultado == 1)
        {   //só insere se não for duplicato 
            if (ant == NULL)
            {
                // Inserção antes do início: precisa atualizar último->prox
                Categorias *ultimo = *inicio;
                while (ultimo->prox != *inicio)
                {
                    ultimo = ultimo->prox;
                }
                novo->prox = *inicio;
                ultimo->prox = novo;
                *inicio = novo; //novo passa a ser inicio
            }else {
                //inserção entre o anterior e o atual
                ant->prox = novo;
                novo->prox = noAtual;
            }
        }   
    }

    return resultado;
}

void mostrarCategorias(const Categorias *inicio)
{
    if (inicio == NULL) {
        printf("(lista vazia)\n");
        return;
    }
    const Categorias *aux = inicio;
    do {
        printf("Nome Categoria: %s | Tipo Categoria: %s \n", aux->nomeCategoria, tipos_char[aux->tipo - 1]); //arrumar o tipo
        aux = aux->prox;
    } while (aux != inicio);
}



Categorias *buscarCategoria(Categorias *categoria, char *buscarCat)
{
    Categorias *aux = NULL;

    if (categoria != NULL)
    {
        aux = categoria;
        int achou = 0;

        do {
            if (strcmp(aux->nomeCategoria, buscarCat) == 0)
                achou = 1;
            else
                aux = aux->prox;
        } while (aux != categoria && achou == 0);

        if (achou == 0)
            aux = NULL;
    }

    return aux;
}

void removerCategoria(Categorias **categoria, char *nomeCategoria)
{
    if (*categoria == NULL)
        return;

    Categorias *atual = *categoria;
    Categorias *anterior = NULL;
    int achou = 0;

    do {
        if (strcmp(atual->nomeCategoria, nomeCategoria) == 0) {
            achou = 1;
            break;
        }
        anterior = atual;
        atual = atual->prox;
    } while (atual != *categoria);

    if (achou) {
        if (atual == *categoria) { // removendo cabeça
            Categorias *ultimo = *categoria;
            while (ultimo->prox != *categoria)
                ultimo = ultimo->prox;

            if (ultimo == *categoria) { // único elemento
                *categoria = NULL;
            } else {
                *categoria = atual->prox;
                ultimo->prox = *categoria;
            }
        } else { // removendo nó do meio ou final
            anterior->prox = atual->prox;
        }
        free(atual);
    }
}

