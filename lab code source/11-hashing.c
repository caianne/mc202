//Anne Feng Cai 261026

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node {//estrutura para guardar os elementos na tabela de hash
    char key[250];
    int id;
} Node;

int Hash(char* chave) {//calculo do primeiro hash (o padrao para quando nao ha colisao ainda)
    int n = 0;
    for (unsigned int i = 0; i < strlen(chave); i++) {
        n = (256*n + chave[i])%6263;
    }
    return n;
}

int Hash2(char* chave) {//calculo do segundo hash para ser o "peso" que faz com que o indice varie ate nao colidir
    int n = 0;
    for (unsigned int i = 0; i < strlen(chave); i++) {
        n = (1+(256*n + chave[i]))%6261;
    }
    return n;
}

void inserir(Node** hash, char* chave, int* id) {
    int cont = 1, n = Hash(chave), copia = n, m = Hash2(chave);
    while (hash[n] != NULL) {//so entra em caso de colisao
        if (strcmp(hash[n]->key, chave) == 0)//em cada colisao, verifica se nao foi com o elemento a ser inserido
            return;//os elementos inseridos nao se repetem
        n = (copia + cont*m)%6261;
        cont++;
    }
    Node* novo;
    novo = malloc(sizeof(Node));
    strcpy(novo->key, chave);
    novo->id = *id;
    hash[n] = novo;//insere o endereco da struct do elemento na tabela de hash
    int temp = *id;
    *id = temp+1;
}

void buscar(Node** hash, char* chave) {
    int cont = 1, n = Hash(chave), copia = n, m = Hash2(chave);
    while (hash[n] != NULL) {//aqui a logica se assemelha muito ao da funcao de inserir
        if (strcmp(hash[n]->key, chave) == 0) {
            printf("%s encontrada, id %d\n", chave, hash[n]->id);
            return;
        }
        n = (copia + cont*m)%6261;
        cont++;
    }
    printf("%s nao encontrada\n", chave);
    return;
}

void remover(Node** hash, char* chave) {
    int cont = 1, n = Hash(chave), copia = n, m = Hash2(chave);
    while (hash[n] != NULL) {//na remocao eh obrigatorio que haja "colisao", ja que o elemento a ser removido deve estar na tabela
        if (strcmp(hash[n]->key, chave) == 0) {
            free(hash[n]);
            hash[n] = NULL;
            return;
        }
        n = (copia + cont*m)%6261;
        cont++;
    }
}

int main() {
    char comando[5] = {};
    char chave[250] = {};
    int id = 0;
    Node* hash[6263] = {NULL};//a tabela hash sera inicializada com todas as posicoes com NULL (nosso indicador de vazio na posicao x)
    scanf("%s", comando);
    while (strcmp(comando,"f")!= 0) {
        if (strcmp(comando,"i") == 0) {
            scanf("%s", chave);
            inserir(hash, chave, &id);
        } else if (strcmp(comando,"b") == 0) {
            scanf("%s", chave);
            buscar(hash, chave);
        } else if (strcmp(comando,"r") == 0) {
            scanf("%s", chave);
            remover(hash, chave);
        }
        scanf("%s", comando);
    }
    for (int i = 0; i < 6263; i++) {//por fim, sera necessario remover todos os elementos (que foram alocados dinamicamente)
        if (hash[i]!=NULL) {
            free(hash[i]);
        }
    }
    return 0;
}