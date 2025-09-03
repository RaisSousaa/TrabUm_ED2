// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include "stream.h"
// #include "categorias.h"

// Stream *raiz = NULL;  // árvore de streams

// void menuStreams();
// void menuCategorias();

// int main() {
//     int opcao;

//     do {
//         printf("\n==============================\n");
//         printf("  SISTEMA DE STREAMS\n");
//         printf("==============================\n");
//         printf("1. Gerenciar Streams\n");
//         printf("2. Gerenciar Categorias\n");
//         printf("0. Sair\n");
//         printf("Escolha uma opcao: ");
//         scanf("%d", &opcao);

//         switch(opcao) {
//             case 1: menuStreams(); break;
//             case 2: menuCategorias(); break;
//             case 0: printf("Saindo...\n"); break;
//             default: printf("Opcao invalida!\n");
//         }
//     } while(opcao != 0);

//     return 0;
// }

// // ---------------- STREAMS ----------------
// void menuStreams() {
//     int opcao;
//     do {
//         printf("\n--- GERENCIAR STREAMS ---\n");
//         printf("1. Cadastrar nova Stream\n");
//         printf("2. Mostrar todas as Streams\n");
//         printf("3. Remover uma Stream\n");
//         printf("0. Voltar\n");
//         printf("Escolha: ");
//         scanf("%d", &opcao);

//         switch(opcao) {
//             case 1: {
//                 InfoStream dados = preencherDadosStream();
//                 Stream *novo = alocarNoStream(dados);
//                 if (InserirStream(&raiz, novo))
//                     printf("Stream cadastrada com sucesso!\n");
//                 else
//                     printf("Stream ja existe!\n");
//                 break;
//             }
//             case 2:
//                 if (raiz)
//                     imprimirInOrdem(raiz);
//                 else
//                     printf("Nenhuma stream cadastrada.\n");
//                 break;
//             case 3: {
//                 char nome[50];
//                 printf("Digite o nome da stream a remover: ");
//                 scanf("%s", nome);
//                 remover(&raiz, nome);
//                 break;
//             }
//             case 0: break;
//             default: printf("Opcao invalida!\n");
//         }
//     } while(opcao != 0);
// }

// // ---------------- CATEGORIAS ----------------
// void menuCategorias() {
//     if (!raiz) {
//         printf("Cadastre primeiro uma stream.\n");
//         return;
//     }

//     int opcao;
//     char nomeStream[50];

//     printf("Digite o nome da stream: ");
//     scanf("%s", nomeStream);
//     Stream *s = buscarStream(raiz, nomeStream);
//     if (!s) {
//         printf("Stream nao encontrada!\n");
//         return;
//     }

//     do {
//         printf("\n--- GERENCIAR CATEGORIAS DA STREAM %s ---\n", s->info.nomeStream);
//         printf("1. Cadastrar Categoria\n");
//         printf("2. Mostrar Categorias\n");
//         printf("3. Remover Categoria\n");
//         printf("0. Voltar\n");
//         printf("Escolha: ");
//         scanf("%d", &opcao);

//         switch(opcao) {
//             case 1: {
//                 Categorias *nova = alocarMemoriaNo();
//                 if (!nova) {
//                     printf("Erro ao alocar memória!\n");
//                     break;
//                 }
//                 printf("Digite o nome da categoria: ");
//                 scanf(" %[^\n]", nova->nomeCategoria); 
//                 prencherCategoria(nova); // CORRETO: passar ponteiro
//                 inserirCategoria(&(s->info.categoria), nova);
//                 break;
//             }
//             case 2:
//                 mostrarCategorias(s->info.categoria);
//                 break;
//             case 3: {
//                 char nomeCat[50];
//                 printf("Digite a categoria a remover: ");
//                 scanf("%s", nomeCat);
//                 removerCategoria(&s->info.categoria, nomeCat);
//                 break;
//             }
//             case 0: break;
//             default: printf("Opcao invalida!\n");
//         }
//     } while(opcao != 0);
// }
