/*
---------------------------------------------------------------------------------------------------------------------------
| Nome: Anne Feng Cai                                                                                                     |
|                                                                                                                         |
| Descricao: Programa para gerenciar listas encadeadas usando estrategias: move-to-front, transpose e counter devidamente |
| explicadas ao longo dos comentarios nos programas.                                                                      |
---------------------------------------------------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include "listfunctions.h"

int main() {
    int N, R;//para receber os parametros do enunciado
    scanf("%d %d", &N, &R);
    int *access;//para receber as requisicoes da lista
    int answer[3], cont = 0;//para guardar as respostas da saida
    access = malloc(R*sizeof(int));
    no *pno = createlist(N);//move-to-front (funcao movetofront())
    for (int i = 0; i < R; i++) {//no primeiro "guardar" dos acessos ja ir fazendo as contas para o move-to-front para
        scanf("%d", (access+i));//aproveitar a iteracao
        cont += movetofront(*(access+i), pno);
    }
    answer[0] = cont;
    cont = 0;
    freelist(pno);
    pno = createlist(N);//transpose (funcao transpose())
    for (int i = 0; i < R; i++) {
        cont += transpose(*(access+i), pno);
    }
    answer[1] = cont;
    cont = 0;
    freelist(pno);
    noc *pnoc = createlistc(N);//count (funcao counting())
    for (int i = 0; i < R; i++) {
        cont += counting(*(access+i), pnoc);
    }
    answer[2] = cont;
    freelistc(pnoc);
    free(access);
    printf("%d %d %d\n", answer[0], answer[1], answer[2]);//printa a resposta no formato desejado
    return 0;
}