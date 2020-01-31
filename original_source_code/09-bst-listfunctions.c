#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "09_bst.h"

void inserir(bst* tree) {//insere os inteiros nas posicoes de uma arvore binaria com informacoes de valor e próximos filhos
    int x;
    scanf("%d", &x);
    no* aux = tree->raiz;
    no* auxant = NULL;//precisa guardar o no anterior para poder usar depois
    while (aux) {//procura ate o fim da arvore, a posicao onde o x se encaixa, sendo maior que os da esquerda e menor que da direita
        auxant = aux;//guarda a posicao anterior
        if (x < aux->valor) {
            aux = aux->menor;//atualiza para esquerda (menor)
        } else if (x > aux->valor) {
            aux = aux->maior;//atualiza para direita (maior)
        } else {
            return;//caso seja igual, nem faz nada
        }
    } aux = malloc(sizeof(no));//assim que encontra, faz com que aux (que agora é NULL) seja apontador da nova posicao
    aux->valor = x;
    aux->maior = NULL;
    aux->menor = NULL;
    if (tree->raiz == NULL) {//caso a árvore ainda não exista, essa é a inserção da raiz
        tree->raiz = aux;
    } else {//caso já exista, tem que saber pra que lado da folha adicionar (se é menor ou maior)
        if (x < auxant->valor) {
            auxant->menor = aux;
        } else if (x > auxant->valor) {
            auxant->maior = aux;
        }
    }
    tree->ocupado++;//atualiza o contador
}

void buscar(bst* tree) {//função simples para buscar um elemento na árvore binária
    int x;
    scanf("%d", &x);
    no* aux = tree->raiz;
    while (aux) {//basicamente vai descendo a árvore até achar o mais próximo ou o elemento
        if (x < aux->valor) {
            aux = aux->menor;
        } else if (x > aux->valor) {
            aux = aux->maior;
        } else {//caso encontre, avisa e sai da função
            printf("%d pertence\n", x);
            return;
        }
    } printf("%d nao pertence\n", x);//caso tenha chegado no NULL, quer dizer que não existe o elemento buscado
    return;
}

void pos_ordem(no* node) {
    if (node) {
        pos_ordem(node->menor);
        pos_ordem(node->maior);
        printf("%d ", node->valor);
    }
}

void em_ordem(no* node) {
    if (node) {
        em_ordem(node->menor);
        printf("%d ", node->valor);
        em_ordem(node->maior);
    }
}

void pre_ordem(no* node) {
    if (node) {
        printf("%d ", node->valor);
        pre_ordem(node->menor);
        pre_ordem(node->maior);
    }

}

void inlining (fila* fila, no* no) {//enfileira um novo nó na fila com informação do endereço dos nós da árvore
    nofila* novo;
    novo = malloc(sizeof(nofila));
    novo->endereco = no;
    novo->prox = NULL;
    if (fila->ini == NULL) {//caso a fila não exista, este é o início da fila sendo adicionado
        fila->ini = novo;
    }
    else {//caso a fila já exista, estamos inserindo um elemento no fim dela
        fila->fim->prox = novo;
    }
    fila->fim = novo;//em qualquer caso, o apontador para o fim da fila agora é para o nó inserido
}

void largura(no* raiz) {
    fila* fila;//setando a estrutura da fila, com inicio e fim nulos
    fila = malloc(sizeof(struct fila));
    fila->ini = NULL;
    fila->fim = NULL;
    inlining(fila, raiz);//colocando o endereco da raiz na fila
    while(fila->ini!= NULL && fila->fim != NULL) {//enquanto ainda temos elementos na fila
        nofila* libera = fila->ini;//criando um endereço de nó auxiliar para guardar o elemento visitado
        raiz = fila->ini->endereco;//pega o endereco do nó da arvore
        fila->ini = fila->ini->prox;//atualiza o início da fila pulando o visitado
        if (fila->ini == NULL) {//caso o início não exista mais, o fim também não
            fila->fim = NULL;
        }
        if (!raiz) {//caso a raiz atualizada seja nula, quebrar o loop imediatamente
            break;
        }
        if (raiz->menor) {//caso o filho menor do nó não seja nulo, deve-se colocá-lo na fila
            inlining(fila, raiz->menor);            
        }
        if (raiz->maior) {//caso o filho maior do nó não seja nulo, deve-se colocá-lo na fila
            inlining(fila, raiz->maior);
        }
        printf("%d ", raiz->valor);//printa o valor do nó na árvore
        free(libera);//e libera o nó que acabou de ser visitado da fila
    }
    free(fila);//quando o looping se encerra, libera a fila
}

void clean(no* node) {//função que libera a memória alocada para uma árvore recursivamente a partir da raiz
    if (node) {
        clean(node->menor);
        clean(node->maior);
        free(node);
    }
}
