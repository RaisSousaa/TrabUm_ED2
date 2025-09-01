#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"categorias.h"


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
