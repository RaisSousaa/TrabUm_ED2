#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "categorias.h"

char *tipos_char[] = {"Esporte", "Noticia", "Entreterimento", "Cultura"};


Categorias *criarCategoria()
{
    return NULL;
}

void prencherCategoria(Categorias *no){
    int escolha = 0;
    
    no->programas = NULL;

    printf("Escolha a categoria: \n");
    printf("1 - Esporte \n");
    printf("2 - Noticia \n");
    printf("3 - Entreterimento \n");
    printf("4 - Cultura \n");
    printf("Sua escolha -> ");
    scanf("%d", &escolha);

    switch (escolha)
    {
    case Esporte:
        no->tipo = Esporte;
        break;
    case Noticia:
        no->tipo = Noticia;
        break;
    case Entreterimento:
        no->tipo = Entreterimento;
        break;
    case Cultura:
        no->tipo = Cultura;
        break;
    default:
        break;
    }
}

void inserirCategoria(Categorias **lista, Categorias *no)
{
    if (*lista == NULL)
    {
        *lista = no;
        no->prox = no;
    }
    else
    {
        Categorias *aux = *lista;
        int duplicata = 0;

        do {
            if (strcmp(aux->nomeCategoria, no->nomeCategoria) == 0)
                duplicata = 1;
            aux = aux->prox;
        } while (aux != *lista && duplicata == 0);

        if (duplicata == 0)
        {
            aux = *lista;
            while (aux->prox != *lista)
                aux = aux->prox;

            aux->prox = no;
            no->prox = *lista;
        }
    }
}
Categorias *alocarMemoriaNo()
{
    Categorias *no = (Categorias *) malloc(sizeof(Categorias));
    if (no == NULL)
    {
        printf("Erro ao alocar\n");
    }
    else
    {
        no->prox = NULL;
        no->programas = NULL;
    }
    return no;
}

void mostrarCategorias(Categorias *lista)
{
    if (lista == NULL) {
        printf("Lista vazia!\n");
    } 
    else 
    {
        Categorias *aux = lista;
        do {
            printf("Categoria: %s\n", lista->nomeCategoria);
            aux = aux->prox;
        } while (aux != lista);
    }
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
