//Anne Feng Cai 261026
#include <stdio.h>

void troca(int* a, int* b) {//faz a troca entre dois elementos
    int aux = *a;
    *a = *b;
    *b = aux;
    return;
}

void criar_heap(int* heap, int tamanho, int pai) {//cria um heap de maximo
    int esquerda = 2*pai+1, direita = 2*pai+2, maior;
    if (esquerda < tamanho) {//o filho da esquerda tem que pertencer ao vetor heap
        maior = esquerda;//supoe se que o filho da esquerda eh um candidato a maior elemento
        if (direita < tamanho && (heap[esquerda] < heap[direita]))//caso o da direita pertenca e seja maior que o da esquerda
            maior = direita;//entao o da direita passa a ser o candidato a maior elemento entre os fihlos
        if (heap[pai] < heap[maior]) {//caso o pai seja menor que o maior dos filhos
            troca(&heap[pai], &heap[maior]);//a gente faz uma troca
            criar_heap(heap, tamanho, maior);//e reordena a subarvore da posicao do maior filho (que agora eh pai)
        }
    }
}

void remover_max(int* heap, int tamanho) {//remove/ordena o heap jogando o maximo para o fim do vetor e reordenando em maximo de novo
    while (tamanho > 1) {
        troca(&heap[0], &heap[tamanho-1]);
        tamanho--;
        criar_heap(heap, tamanho, 0);
    }
}

int main() {
    //leitura de dados na entrada
    int tamanho;
    scanf("%d", &tamanho);
    int heap[tamanho];
    for (int i = 0; i < tamanho; i++) {
        scanf("%d", (heap+i));
    }
    //criando o heap
    for (int i = (tamanho-1)/2; i >= 0; i--) {
        criar_heap(heap, tamanho, i);
    }
    //ordenando o heap/ "removendo" o maximo
    remover_max(heap, tamanho);
    //imprimindo o heap ordenado
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", heap[i]);
    }
    printf("\n");
    return 0;
}