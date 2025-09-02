#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"apresentadores.h"
#include"categorias.h"
#include"historico.h"
#include"programas.h"
#include"stream.h"




/*
ix) Mostrar todos os programas de uma determinada stream que acontecem em um determinado dia e horário. ok

xi) Mostrar todos os programas de um determinado dia da semana de uma determinada categoria de uma stream.

xii) Mostrar todos os apresentadores de uma determinada stream. ok

xiii)Mostrar todos os apresentadores de um determinada categoria independente da stream que o mesmo trabalha. ok

xv) Permita remover um program de uma determinada categoria de uma stream.

xvi) Permita remover uma categoria de uma stream, só pode ser removida se não tiver nenhum programa cadastrado nela.

xvii)Permita alterar a stream que um apresentador trabalha atualmente. Lembre-se que não pode haver programa naquela stream apresentado pelo apresentador ( programa removido ou alterado o
apresentador).

*/

 //sugestão chat para não deixar com printf dentro de uma função só
void imprimirApresentadorLinha(const Apresentadores *apresentador) {
    printf("Nome: %s | Stream: %s | Categoria (id): %d\n",
           apresentador->info.nome,
           apresentador->info.streamAtual,
           apresentador->info.ondeTrabalha);
}

/* 
   xii) Mostrar todos os apresentadores de uma determinada stream.
*/
void mostrarApresentadoresPorStream(Apresentadores *listaApresentadores, const char *nomeStream) {
    int encontrou = 0;

    if (listaApresentadores && nomeStream) {
        Apresentadores *atual = listaApresentadores;

        do {
            if (atual->info.streamAtual && strcmp(atual->info.streamAtual, nomeStream) == 0) {
                imprimirApresentadorLinha(atual);
                encontrou = 1;
            }
            atual = atual->prox;
        } while (atual && atual != listaApresentadores);
    }

    if (!encontrou) {
        printf("Nenhum apresentador encontrado para a stream '%s'.\n", nomeStream);
    }
}

/* 
   xiii) Mostrar todos os apresentadores de uma determinada categoria 
   (independente da stream).
*/
void mostrarApresentadoresPorCategoria(Apresentadores *listaApresentadores, int categoriaId) {
    int encontrou = 0;

    if (listaApresentadores) {
        Apresentadores *atual = listaApresentadores;

        do {
            if (atual->info.ondeTrabalha == categoriaId) {
                imprimirApresentadorLinha(atual);
                encontrou = 1;
            }
            atual = atual->prox;
        } while (atual && atual != listaApresentadores);
    }

    if (!encontrou) {
        printf("Nenhum apresentador encontrado para a categoria id=%d.\n", categoriaId);
    }
}



// int main()
// {
//     Stream *raizStream = NULL;
//     InfoStream dados;
//     Stream *stream;



//     int opcao;

//     do
//     {
//         printf("0 - Sair\n");
//         printf("1 - Cadastrar Stream\n");
//         printf("2 - Mostrar Stream\n");
//         printf("3 - Buscar Stream\n");
//         printf("Escolha uma opcao: ");
//         scanf("%d", &opcao);

//         switch (opcao)
//         {
//         case 0:
//             printf("Finalizando...\n");
//             break;
//         case 1:
        
//             dados = preencherDadosStream();
//             stream = alocarNoStream(dados);

//             //chamaria a função alocar apresentador e já passava o nome do apresentador

//             int res = InserirStream(&raizStream, stream);

//             if (res == 1)
//                 printf("Stream cadastrada com sucesso.\n");
//             else printf("Stram já cadastrada!.\n");

//             break;
            

        
//         default:
//             break;
//         }


//     } while (opcao != 0);
    


//     return 0;
// }