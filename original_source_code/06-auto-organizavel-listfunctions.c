#include "listfunctions.h"
#include <stdio.h>
#include <stdlib.h>

no* createlist(int N) {//cria e se movimenta na lista sem contador de acessos
    no *pno, *teste;
    pno = malloc(sizeof(no));//aloca memoria para o primeiro apontador de registro (o "0" da lista)
    teste = pno;
    pno->index = 0;
    pno->next = NULL;//vamos convencionar o primeiro struct como uma cabeca sem significado especifico
    for (int i = 1; i <= N; i++) {//cria a lista encadeada de tamanho N
        teste->next = malloc(sizeof(no));//aloca para cada elemento
        teste->next->index = i;//coloca o indice respectivo
        teste->next->next = NULL;//coloca como NULL ate que se prove o contrario (ter mais elementos de registro)
        teste = teste->next;
    }
    return pno;
}

noc* createlistc(int N) {//cria e se movimenta na lista com contador de acessos
    noc *pnoc, *teste;
    pnoc = malloc(sizeof(noc));//aloca memoria para o primeiro apontador de registro (o "0" da lista)
    teste = pnoc;
    pnoc->index = 0;
    pnoc->next = NULL;//vamos convencionar o primeiro struct como uma cabeca sem significado especifico
    pnoc->count = 0;
    for (int i = 1; i <= N; i++) {//cria a lista encadeada de tamanho N
        teste->next = malloc(sizeof(noc));//aloca para cada elemento
        teste->next->index = i;//coloca o indice respectivo
        teste->next->next = NULL;//coloca como NULL ate que se prove o contrario (ter mais elementos de registro)
        teste->next->count = 0;//seta como 0 os acessos no registro criado
        teste = teste->next;
    }
    return pnoc;
}

void freelist(no *pno) {//libera os espacos na memoria heap usando a estrategia dos dois apontadores
    no *teste = pno;
    while (teste->next) {//enquanto tiver registros posteriores
        teste = teste->next;//armazena o proximo do proximo
        free(pno);//libera o atual
        pno = teste;
    }
    free(pno);
}

void freelistc(noc *pnoc) {//libera os espacos na memoria heap usando a estrategia dos dois apontadores
    noc *teste = pnoc;
    while (teste->next) {//enquanto tiver registros posteriores
        teste = teste->next;//armazena o proximo do proximo
        free(pnoc);//libera o atual
        pnoc = teste;
    }
    free(pnoc);
}

void printlist(no *pno) {//printa a lista para ver seu estado
    while (pno->next) {//enquanto tiver registros posteriores
        printf("%d ", pno->next->index);//printa ele
        pno = pno->next;//vai para o proximo
    }
    printf("\n");
}

void printlistc(noc *pnoc) {//printa a lista para ver seu estado
    while (pnoc->next) {//enquanto tiver registros posteriores
        printf("%d ", pnoc->next->index);//printa ele
        pnoc = pnoc->next;//vai para o proximo
    }
    printf("\n");
}

int movetofront(int key, no *listdress) {//move o registro encontrado para o inicio da lista encadeada
    int count = 0;
    no *test = listdress, **inidress, **finaldress;
    while (test->index != key) {//ate achar, vai passando para o proximo registro da lista encadeada
        inidress = &(test->next);//guarda o endereco da variavel que aponta para o proximo potencial registro
        test = test->next;//passa para o proximo registro da lista encadeada
        finaldress = &(test->next);//guarda o endereco da variavel que aponta para depois do potencial registro
        count += 1;
    }
    *inidress = test->next;//aponta o registro que precede o encontrado para o proximo depois dele, pulando-o
    *finaldress = (listdress)->next;//aponta o "proximo" do registro encontrado para o inicio da lista
    listdress->next = test;//aponta a cabeca da lista para o encontrado
    return count;
}

int transpose(int key, no *listdress) {//troca o registro encontrado com o anterior
    int count = 0;
    no *test = listdress, *aux;
    while (test->index != key) {//ate achar, vai passando para o proximo registro da lista encadeada
        aux = test;//guarda o apontador "anterior"
        test = test->next;//passa para o proximo registro da lista encadeada
        count += 1;
    }
    if (aux->index) {//pode acontecer do apontador "anterior" ser do registro 0, entao, nao sendo...
        test->index = aux->index;//o valor do encontrado passa a ser igual ao do anterior
        aux->index = key;//o valor do anterior passa a ser o valor a ser encontrado
    }
    return count;
}

int counting(int key, noc *listdress) {//troca o registro encontrado com o anterior
    int count = 0;
    noc *test = listdress, *aux;
    noc **inidress, **finaldress;
    while (test->index != key) {//ate achar, vai passando para o proximo registro da lista encadeada
        inidress = &(test->next);//guarda o endereco da variavel que aponta para o proximo potencial registro
        test = test->next;//passa para o proximo registro da lista encadeada
        finaldress = &(test->next);//guarda o endereco da variavel que aponta para depois do potencial registro
        count += 1;
    }
    test->count += 1;
    *inidress = test->next;//aponta o registro que precede o encontrado para o proximo depois dele, pulando-o
    //parte de achar o primeiro contador menor ou igual ao do encontrado
    inidress = &(listdress->next);//"inicializa" o inidress para pegar o endereco do "dummie->next" (minha lista[0])
    aux = listdress->next;//"inicializa" o aux para apontar para o primeiro registro importante (o 1)
    if (aux) {//caso a lista encadeada so tenha 1 elemento, o registro 0 passa a apontar para NULL depois do while anterior
        while (test->count < aux->count) {//procura o primeiro elemento que tem contador menor que o encontrado
            inidress = &(aux->next);
            aux = aux->next;
        }
    }
    *inidress = test;//aponta o ultimo registro com contador maior que o encontrado para o encontrado
    *finaldress = aux;//faz o encontrado apontar para o proximo com contador menor ou igual a ele
    return count;
}
