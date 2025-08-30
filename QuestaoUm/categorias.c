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
    if (lista) 
    {
        Categorias *aux = lista;
        do {
            printf("Categoria: %s\n", aux->nomeCategoria);
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


int main() {
    Categorias *lista = criarCategoria();

    // Criar primeira categoria
    Categorias *c1 = alocarMemoriaNo();
    strcpy(c1->nomeCategoria, "Esporte");
    c1->tipo = Esporte;
    inserirCategoria(&lista, c1);

    // Criar segunda categoria
    Categorias *c2 = alocarMemoriaNo();
    strcpy(c2->nomeCategoria, "Noticia");
    c2->tipo = Noticia;
    inserirCategoria(&lista, c2);

    // Criar terceira categoria
    Categorias *c3 = alocarMemoriaNo();
    strcpy(c3->nomeCategoria, "Cultura");
    c3->tipo = Cultura;
    inserirCategoria(&lista, c3);

    printf("\n--- Categorias inseridas ---\n");
    mostrarCategorias(lista);

    // Buscar categoria
    char buscar[] = "Noticia";
    Categorias *achada = buscarCategoria(lista, buscar);
    if (achada != NULL) {
        printf("\nCategoria encontrada: %s\n", achada->nomeCategoria);
    } else {
        printf("\nCategoria '%s' não encontrada.\n", buscar);
    }

    // Remover categoria
    printf("\nRemovendo categoria 'Esporte'...\n");
    removerCategoria(&lista, "Esporte");

    printf("\n--- Lista após remoção ---\n");
    mostrarCategorias(lista);

    // Remover categoria inexistente
    printf("\nTentando remover 'Inexistente'...\n");
    removerCategoria(&lista, "Inexistente");

    printf("\n--- Lista final ---\n");
    mostrarCategorias(lista);

    return 0;
}
