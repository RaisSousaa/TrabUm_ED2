#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "categorias.h"

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
        return;
    }

    Categorias *aux = *lista;

    // percorre todos os nós para checar duplicata
    do {
        if (strcmp(aux->nomeCategoria, no->nomeCategoria) == 0)
            return; // categoria já existe, não insere
        aux = aux->prox;
    } while (aux != *lista);

    // se não encontrou duplicata, insere no final
    aux = *lista;
    while (aux->prox != *lista)
        aux = aux->prox;

    aux->prox = no;
    no->prox = *lista;
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
        printf("Categoria: %s\n", tipos_char[aux->tipo - 1]);
        aux = aux->prox;
    } while (aux != lista);
}

Categorias *buscarCategoria(Categorias *categoria, char *buscarCat)
{
    Categorias *aux = criarCategoria();

    if (categoria)
    {
        aux = categoria;

        do
        {
            if (strcmp(aux->nomeCategoria, buscarCat) == 0)
                break;
            aux = aux->prox;

        } while (aux != categoria);

        if (strcmp(aux->nomeCategoria, buscarCat) != 0)
            aux = NULL;
    }

    return aux;
}


