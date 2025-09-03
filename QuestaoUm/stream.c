#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "stream.h"

Stream *CriarStream()
{
    return NULL;
}

// alocacao do no da arvore
Stream *alocarNoStream(InfoStream stream)
{
    Stream *no = (Stream*) malloc(sizeof(Stream));
    if (no == NULL)
    {
        printf("Erro ao alocar memoria\n");
    }
    else
    {
        no->dir = NULL;
        no->esq = NULL;
        no->info = stream;
    }
    return no;
}

// Preenche o no da arvore
InfoStream preencherDadosStream()
{
    InfoStream dados;
    printf("Digite o nome da Stream:\n");
    scanf("%s", dados.nomeStream);
    printf("Digite o nome do site:\n");
    scanf("%s", dados.nomeSite);
    return dados;
}

//Insere o no da arvore
int InserirStream(Stream **raiz, Stream *no) 
{
    int inseriu = 0;
    if (!(*raiz)) 
    {
        *raiz = no; 
        inseriu = 1;
    }
    else
    {
        int compara = strcmp(no->info.nomeStream, (*raiz)->info.nomeStream);

        if (compara < 0)
            inseriu = InserirStream(&(*raiz)->esq, no);
        else if (compara > 0)
            inseriu = InserirStream(&(*raiz)->dir, no);
    }
    return inseriu;
}

int ehFolha(Stream *raiz) {
    return (raiz->esq == NULL && raiz->dir == NULL);
}

Stream *soUmFilho(Stream *no) {
    if (no->esq == NULL && no->dir != NULL) {
        return no->dir;
    } else if (no->esq != NULL && no->dir == NULL) {
        return no->esq;
    } else {
        return NULL;
    }
}

Stream* maiorValor(Stream* no) {
    Stream* aux = no;
    while (aux->dir != NULL) {
        aux = aux->dir;
    }
    return aux;
}

int remover(struct Stream **raiz, char *stream_remove) {
    if (*raiz) {
        if (strcmp(stream_remove, (*raiz)->info.nomeStream) < 0) {
            remover(&(*raiz)->esq, stream_remove);
        } else if (strcmp(stream_remove, (*raiz)->info.nomeStream) > 0) {
            remover(&(*raiz)->dir, stream_remove);
        } else {
            Stream *aux;
            if (ehFolha(*raiz)) {
                aux = *raiz;
                *raiz = NULL;
                free(aux);
            } else {
                Stream *filho;
                if ((filho = soUmFilho(*raiz)) != NULL) {
                    aux = *raiz;
                    *raiz = filho;
                    free(aux);
                } 
                else {
                    Stream *Mesq = maiorValor((*raiz)->esq);
                    strcpy((*raiz)->info.nomeStream, Mesq->info.nomeStream);
                    strcpy((*raiz)->info.nomeSite, Mesq->info.nomeSite);
                    remover(&(*raiz)->esq, Mesq->info.nomeStream);
                }
            }

        }
    }
    return 0;
}

// v) Mostrar todas as streams cadastradas.
void mostrarStreams(Stream *raiz)
{
    if (raiz)
    {
        mostrarStreams(raiz->esq);
        printf("Stream: %s\n", raiz->info.nomeStream);
        mostrarStreams(raiz->dir);
    }
}

Stream *buscarStream(Stream *raiz, char *nomedastream)
{
    Stream *resultado = NULL;

    if (raiz != NULL) {
        int comparastream = strcmp(nomedastream, raiz->info.nomeStream);

        if (comparastream == 0) {
            resultado = raiz;
        } else if (comparastream < 0) {
            resultado = buscarStream(raiz->esq, nomedastream);
        } else {
            resultado = buscarStream(raiz->dir, nomedastream);
        }
    }
    return resultado;
}


// vi) Mostrar todas as categorias cadastradas para uma determinada stream.
void mostrarCategoriasStream(Stream *raiz, char *nomeStream)
{
    if (raiz)
    {
        int compara = strcmp(raiz->info.nomeStream, nomeStream);

        if (compara == 0)
        {
            mostrarCategorias(raiz->info.categoria);
        }
        else if (compara < 0)
        {
            mostrarCategoriasStream(raiz->esq, nomeStream);
        }
        else
        {
            mostrarCategoriasStream(raiz->dir, nomeStream);
        }
    }    
}


// vii) Mostrar todos os programas de uma determinada categoria de uma determinada stream.
void mostrarProgDeCatDeStream(Categorias *categoria, Stream *stream, char *nomeCategoria, char *nomeStream, Programas *programas)
{
    if (stream)
    {
        Stream *streamBuscada = buscarStream(stream, nomeStream);
        
        if (streamBuscada->info.categoria)
        {
            Categorias *categoriaBuscada = buscarCategoria(categoria, nomeCategoria);

            if (categoriaBuscada->programas)
            {
                mostrarProgramas(programas);
            }   
        }
    }
}

// viii)Mostrar todas as streams que tem uma determinada categoria.
void mostrarStreamDeCategoria(Stream *stream, Categorias *categoria, char *nomeDaCategoria)
{
    if (stream)
    {
        int comparaStream = strcmp(stream->info.categoria->nomeCategoria, nomeDaCategoria);
        if (comparaStream == 0)
        {
            printf("Stream: %s\n", stream->info.nomeStream);
        }
        else if (comparaStream < 0)
        {
            mostrarStreamDeCategoria(stream->esq, categoria, nomeDaCategoria);
        }
        else 
        {
            mostrarStreamDeCategoria(stream->dir, categoria, nomeDaCategoria);
        }
    }
}

//x) Mostrar todas as streams que tem um determinado tipo de categoria.
void mostrarStreamDoTipoCategoria(Stream *stream, int nometipocategoria)
{
    if (stream) 
    {
        Categorias *aux = stream->info.categoria;
        int achou = 0;

        if (aux) 
        {
            Categorias *inicio = aux;
            do 
            {
                if (aux->tipo == nometipocategoria) 
                {
                    achou = 1;
                }
                aux = aux->prox;
            } while (aux != inicio && achou == 0);
        }

        if (achou) 
        {
            printf("Stream: %s\n", stream->info.nomeStream);
        }

        mostrarStreamDoTipoCategoria(stream->esq, nometipocategoria);
        mostrarStreamDoTipoCategoria(stream->dir, nometipocategoria);
    }
}


void imprimirInOrdem(Stream *raiz) {
    if (raiz != NULL) {
        imprimirInOrdem(raiz->esq);
        printf("Stream: %s | Site: %s\n", raiz->info.nomeStream, raiz->info.nomeSite);
        imprimirInOrdem(raiz->dir);
    }
}

// xvi) Permita remover uma categoria de uma stream, só pode ser removida se não tiver nenhum programa
//cadastrado nela.

int removerCategoriaDaStream(Stream **stream, char *categoriasremover)
{
    int removeu = 0;
    Categorias* categoriabuscada = buscarCategoria((*stream)->info.categoria, categoriasremover);

    if (categoriabuscada)
    {
        if (categoriabuscada->programas == NULL )
        {
            removerCategoriaDaStream(stream, categoriasremover);
            removeu = 1;
        }
    }
    return removeu;
}



int main()
{
    Stream *raiz = CriarStream();
    Categorias *lista;
    int opcao;
    
    do
    {
        printf("1. Cadastrar strem\n");
        printf("2. Mostrar Stream\n");
        printf("3. Remover Stream\n");
        printf("4. Mostrar streams que tem uma determinada categoria\n");
        printf("5. Mostrar as streams que tem uma determinada categoria\n");
        scanf("%d", &opcao);   
        
        switch (opcao)
        {
        //i) Cadastrar Stream: cadastrar dados de streams organizados em uma árvore binária pelo nome da stream, o usuário pode //cadastrar uma stream a qualquer momento, não permita cadastro repetido.
            case 1:
            {
                InfoStream dados = preencherDadosStream();
                Stream *novoNo = alocarNoStream(dados);
                if(InserirStream(&raiz, novoNo))
                    printf("Stream cadastrada!\n");
                else
                    printf("A stream nao foi cadastrada pois ja existe!\n");

                break;
            }

            // i) Cadastrar Stream: cadastrar dados de streams organizados em uma árvore binária pelo nome da stream, o usuário pode cadastrar uma stream a qualquer momento, não permita cadastro repetido.
            case 2:
            {
                if (raiz)
                    imprimirInOrdem(raiz);
                else
                    printf("Nenhuma stream cadastrada.\n");
                break;
            }
            //xvi) Permita remover uma categoria de uma stream, só pode ser removida se não tiver nenhum programa cadastrado nela.
            case 3:
            {
                char streamRemover[50];
                printf("Digite o nome da stream para remover:\n");
                setbuf(stdin, NULL); // limpar o buff
                scanf("%[^\n]", streamRemover);
                remover(&raiz, streamRemover);   
                break;    
            }

            //viii)Mostrar todas as streams que tem uma determinada categoria.
            case 4:
            {
                char nomecategoria[50];
                printf("Digite o nome da categoria:\n");
                scanf("%[^\n]", nomecategoria);
                mostrarStreamDeCategoria(raiz, lista, nomecategoria);
                break;
            }

            // x) Mostrar todas as streams que tem um determinado tipo de categoria.
            case 5:
            {
                char nomeTipoCat[50];
                printf("Digite o nome do tipo da categoria:\n");
                scanf("%[^\n]", nomeTipoCat);
                mostrarStreamDoTipoCategoria(raiz, nomeTipoCat);
                break;
            }

            case 0: break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
    
    return 0;
}



