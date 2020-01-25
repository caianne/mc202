/* 
--------------------------------------------------------------------------------------------------------------------------------------
| Nome: Anne Feng Cai                                                                                                                |
|                                                                                                                                    |
| Descricao:                                                                                                                         |
| Este trabalho consiste em escrever um programa com funções para manipular uma árvore de busca binária para inteiros.               |
| O programa deve criar uma árvore vazia e em seguida deve processá-la de acordo com comandos da entrada-padrão, que podem ser da    |
| seguinte forma:                                                                                                                    |
|                                                                                                                                    |
| inserir x                                                                                                                          |
| Ao ler o comando inserir x, onde x é um inteiro, o programa deve inserir a chave x na árvore de busca binária. A árvore não deve   |
| ter elementos repetidos, então se x já pertence à árvore ele não deve ser inserido de novo.                                        |
|                                                                                                                                    |
| buscar x                                                                                                                           |
| Ao ler o comando buscar x, onde x é um inteiro, o programa deve buscar a chave x na árvore e imprimir "x pertence" ou "x nao       |
| pertence" em uma linha.                                                                                                            |
|                                                                                                                                    |
| pos-ordem                                                                                                                          |
| em-ordem                                                                                                                           |
| pre-ordem                                                                                                                          |
| largura                                                                                                                            |
| Ao ler um desses comandos o programa deve imprimir as chaves na ordem em que forem visitadas por um percurso em profundidade em    |
| pós-ordem, em-ordem, em pré-ordem ou por um percurso em largura. As chaves devem ser impressas seguidas por um espaço, em uma única|
| linha. Se a árvore estiver vazia então o programa deve imprimir "vazia" em uma linha.                                              |
|                                                                                                                                    |
| terminar                                                                                                                           |
| Ao ler esse comando o programa deve desalocar a árvore e terminar.                                                                 |
--------------------------------------------------------------------------------------------------------------------------------------
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "09_bst.h"

int main() {
    char comando[15] = {};
    bst* tree;//estrutura para armazenar a raiz e a quantidade de nós
    tree = malloc(sizeof(bst));
    tree->raiz = NULL;
    tree->ocupado = 0;
    scanf("%s", comando);
    while (strcmp(comando,"terminar") != 0) {
        if (strcmp(comando,"inserir") == 0) {
            inserir(tree);
        } else if (strcmp(comando,"buscar") == 0) {
            buscar(tree);
        } else if (strcmp(comando,"pos-ordem") == 0) {
            if (tree->ocupado != 0) {
                pos_ordem(tree->raiz);
                printf("\n");
            } else {
                printf("vazia\n");
            }
        } else if (strcmp(comando,"em-ordem") == 0) {
            if (tree->ocupado != 0) {
                em_ordem(tree->raiz);
                printf("\n");
            } else {
                printf("vazia\n");
            }
        } else if (strcmp(comando,"pre-ordem") == 0) {
            if (tree->ocupado != 0) {
                pre_ordem(tree->raiz);
                printf("\n");
            } else {
                printf("vazia\n");
            }
        } else if (strcmp(comando,"largura") == 0) {
            if (tree->ocupado != 0) {
                largura(tree->raiz);
                printf("\n");
            } else {
                printf("vazia\n");
            }
        }
        scanf("%s", comando);
    }
    clean(tree->raiz);//libera a memória usada para gerar a árvore
    free(tree);//libera a estrutura da árvore (raiz e contador)
}