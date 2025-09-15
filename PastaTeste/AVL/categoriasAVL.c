#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "categoriasAVL.h"
#include "streamAVL.h"

char *tipos_char[] = {"Esporte", "Noticia", "Entreterimento", "Cultura"};


Categorias *criarCategoria()
{
    return NULL;
}

void prencherCategoria(Categorias *no){
    int escolha = 0;
    
    no->programas = NULL;

    printf("Digite o nome da categoria:\n");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", no->nomeCategoria);

    printf("Escolha o tipo da categoria: \n");
    printf("1 - Esporte \n");
    printf("2 - Noticia \n");
    printf("3 - Entretenimento \n");
    printf("4 - Cultura \n");
    printf("Sua escolha -> ");
    scanf("%d", &escolha);

    if (escolha >= 1 && escolha <= 4) {
        no->tipo = (Tipo)escolha;
    } else {
        printf("Tipo inválido, setando como Cultura.\n");
        no->tipo = Cultura;
    }
}


int inserirCategoria(Categorias **lista, Categorias *no)
{
    int inseriu = 1;
    if (!(*lista))
    {
        *lista = no;
        no->prox = *lista;
    }
    else
    {
        Categorias *aux = (*lista);
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
        else
        {
            inseriu = 0;
        }
    }
    return inseriu;
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
    else
    {
        printf("Sem categorias!");
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

//Função que encontra a categoria de um determinado tipo em uma stream
//usada no main na opção 5 do menu apresentadores
Categorias* encontrarCategoriaPorTipoNaStream(Stream *stream, Tipo tipo)
{
    Categorias *resultado = NULL;

    if (stream) {
        Categorias *cat = stream->info.categoria;
        while (cat != NULL && resultado == NULL) {
            if (cat->tipo == tipo) {
                resultado = cat;        // guarda e continua condição encerra
            } else {
                cat = cat->prox;
            }
        }
    }

    return resultado; 
}