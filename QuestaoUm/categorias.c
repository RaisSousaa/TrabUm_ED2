#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "categorias.h"

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
        (*lista)->prox = *lista;
    }

    else
    {
        Categorias *aux = *lista;
        while (aux->prox != *lista)
        {
            aux = aux->prox;
        }
        aux->prox = no;
        no->prox = *lista;
    }
}

Categorias *alocarMemoriaNo()
{
    Categorias *no = (Categorias *) malloc(sizeof(Categorias));
    if (no == NULL)
    {
        printf("Erro ao alocar\n");
    }
    return no;
}

void mostrarCategorias(Categorias *lista)
{
    if (lista == NULL) {
        printf("Lista vazia!\n");
        return;
    }

    Categorias *aux = lista;
    do {
        printf("Categoria: %d\n", aux->tipo);
        aux = aux->prox;
    } while (aux != lista);
}
