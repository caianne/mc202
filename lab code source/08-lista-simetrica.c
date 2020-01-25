/*
Nome: Anne Feng Cai
RA: 261026

Cada linha da entrada contém um comando como descrito a seguir.

-Inserir:
i posição valor
Inserir um novo nó em uma posição específica. O double inserido passa a ocupar aquela posição na lista, contando da cabeça, que está na posição zero. Se não for possível inserir na posição específica, então a inserção deve ser feita no fim da lista. Essa situação acontece, por exemplo, quando a lista tem 5 elementos e pedimos para inserir 3.14 na posição 9. Nesse caso, 3.14 deve ser inserido na posição 5.

- Imprimir:
p
Imprimir os valores na lista a partir da cabeça em uma única linha. Cada elemento da lista deve ser seguido de um espaço. A lista vazia é impressa como uma linha em branco, sem espaços.

- Reverter:
v início término
Reverter o trecho delimitado pelas posições início e término, inclusive.

- Terminar:
t

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct elemento {
    double valor;
    struct elemento* antes;
    struct elemento* depois;
} elemento;

void inserir(elemento **beg, elemento **end, int *quantidade) {//funcao que insere elementos na posicao desejada da lista
    int posicao;
    double entrada;//a entrada tera precisao de 4 casas decimais
    elemento *novo, *aux = *beg;
    scanf("%d %le", &posicao, &entrada);
    novo = malloc(sizeof(elemento));//o novo elemento sera alocado dinamicamente
    novo->valor = entrada;
    if (*quantidade == 0) {//primeira insercao de todas
        *beg = novo;
        novo->antes = NULL;
        novo->depois = NULL;
        *end = novo;
    } else if (posicao >= *quantidade) {//insercao no final sempre que a posicao desejada for superior a existente
        novo->antes = *end;
        novo->depois = NULL;
        (*end)->depois = novo;
        *end = novo;
    } else if (posicao == 0) {//insercao no inicio da lista
        novo->antes = NULL;
        novo->depois = *beg;
        (*beg)->antes = novo;
        *beg = novo;
    } else {//insercao no meio da lista
        int cont = 0;
        while (cont < posicao) {//percorre ate achar a posicao que futuramente sera a que vem depois do elemento a ser inserido
            aux = aux->depois;
            cont++;
        }
        novo->antes = aux->antes;
        novo->depois = aux;
        aux->antes->depois = novo;
        aux->antes = novo;
    }
    *quantidade+=1;//quantidade de elementos na lista atualizada
}

void imprimir(elemento *beg) {
    while (beg) {//printa do inicio da lista ate o fim
        printf("%.4f ", beg->valor);//printa com uma precisao de 4 casas decimais
        beg = beg->depois;
    }
    printf("\n");
}

void reverter(elemento **beg, elemento **end, int *quantidade) {
    int inicio, fim, cont = 0;
    elemento *auxinicio = *beg, *auxfim, *tempinicio, *tempfim, *conseq1, *conseq2;
    scanf("%d %d\n", &inicio, &fim);
    if (inicio != fim) {//caso sejam iguais, nem entra
        if (inicio > fim) {//pro caso de vier ao contrario (em ordem decrescente)
            int aux = inicio;
            inicio = fim;
            fim = aux;            
        }
        while (cont < inicio) {//percorre do inicio da lista ate o inicio desejado
            auxinicio = auxinicio->depois;
            cont++;
        }
        if (fim >= *quantidade/2) {//percorre do fim ate o fim desejado (caso seja mais economico)
            auxfim = *end;
            cont = *quantidade - 1;
            while (cont > fim) {
                auxfim = auxfim->antes;
                cont--;
            }
        } else {//percorre do inicio desejado ate o fim desejado (caso seja mais economico)
            auxfim = auxinicio;
            while (cont < fim) {
                auxfim = auxfim->depois;
                cont++;
            }
        }
        //tempinicio e tempfim sao os apontadores para as posicoes antes e depois dos desejados
        tempinicio = auxinicio->antes;
        tempfim = auxfim->depois;
        if (tempinicio) {//caso nao seja a primeira posicao na lista (posicao 0)
            tempinicio->depois = auxfim;
        } else {//caso seja, o apontador para inicio deve mudar tambem
            *beg = auxfim;
        }
        cont = 0;
        //hora de mudar a direcao da lista no intervalo desejado
        conseq1 = auxfim;
        conseq2 = auxfim->antes;
        auxfim->antes = tempinicio;
        while (cont < (fim-inicio)) {//basicamente muda o antes e depois de cada elemento no intervalo
            conseq1->depois = conseq2;
            tempinicio = conseq2->antes;//um auxiliar sera necessario para nao perder conseq2->antes, como tempinicio ja nao sera mais usado...
            conseq2->antes = conseq1;
            conseq1 = conseq2;
            conseq2 = tempinicio;
            cont++;
        }
        if (tempfim) {//caso nao seja a ultima posicao da lista
            tempfim->antes = auxinicio;
        } else {//caso seja, o apontador para o fim deve mudar
            *end = auxinicio;                
        }
        auxinicio->depois = tempfim;
    }
}

int main() {
    char comando[1] = {};//comando i: insere elementos; comando p: imprime a lista toda; comando v: reverte posicoes na lista
    int quantidade = 0;
    elemento *beg = NULL, *end = NULL, *aux;
    scanf("%s", comando);
    while (*comando != 't') {//comando t: encerra a execucao
        if (*comando == 'i') {
            inserir(&beg, &end, &quantidade);
        } else if (*comando == 'p') {
            imprimir(beg);
        } else if (*comando == 'v') {
            reverter(&beg, &end, &quantidade);
        }
        scanf("%s", comando);
    }
    if (quantidade) {//parte para liberar a memoria alocada dinamicamente
        while (aux) {
            aux = beg->depois;
            free(beg);
            beg = aux;
        }
    }
    return 0;
}