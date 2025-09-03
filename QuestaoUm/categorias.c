#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "categorias.h"
#include "stream.h"

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

    no->tipo = escolha;
}

void inserirCategoria(Categorias **lista, Categorias *no)
{
    if (*lista)
    {
        *lista = no;
        no->prox = no;
    }
    else
    {
        Categorias *aux = *lista;
        int duplicata = 0;

        if(aux != NULL) {
            do {
                if(strcmp(aux->nomeCategoria, no->nomeCategoria) == 0){
                    duplicata = 1;
                    break; // já achou, sai do loop
                }
                aux = aux->prox;
            } while(aux != *lista);
        }

        if (duplicata == 0) { 
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
        exit(EXIT_FAILURE);
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
    if (*categoria != NULL) {
        Categorias *atual = *categoria;
        Categorias *anterior = NULL;
        Categorias *remover = NULL;

        do {
            if (strcmp(atual->nomeCategoria, nomeCategoria) == 0) {
                remover = atual;
            }
            anterior = atual;
            atual = atual->prox;
        } while (atual != *categoria && remover == NULL);

        if (remover != NULL) {
            if (remover == *categoria) { // removendo cabeça
                Categorias *ultimo = *categoria;
                while (ultimo->prox != *categoria)
                    ultimo = ultimo->prox;

                if (ultimo == *categoria) { // único elemento
                    *categoria = NULL;
                } else {
                    *categoria = remover->prox;
                    ultimo->prox = *categoria;
                }
            } else { // removendo nó do meio ou final
                anterior->prox = remover->prox;
            }
            free(remover);
        }
    }
    return;
}



int main()
{
    Stream *raiz;
    int opcao;
    char nomeStream[50];


    do
    {
        printf("1. Cadastrar Categorias\n");
        printf("2. Mostrar categorias de uma stream\n");
        printf("3. Mostrar programas de categoria\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        
        switch (opcao)
        {
            case 1:
                Stream *streamBuscada;
                printf("Digite o nome da stream para inserir a categoria:\n");
                scanf("%[^\n]", nomeStream);
                streamBuscada = buscarStream(raiz, nomeStream);

                break;
            
            default:
                break;
        }
    } while (opcao != 0);
    
    
   


}

