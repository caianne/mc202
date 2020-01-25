/* 
---------------------------------------------------------------------------------------------------------------------------------------------
| Nome: Anne Feng Cai                                                                                                                       |
|                                                                                                                                           |
| Descricao: Este trabalho consiste em fazer um programa que manipule uma colecao de contatos. Seu programa deve ser capaz de organizar     |
| ate 1.000 contatos. O programa deve ser capaz de inserir registros, remover registros, recuperar registros e imprimir todos os registros  |
| da colecao. A entrada consiste de um caractere que especifica a operacao, seguido de linhas de acordo com cada operacao, que pode ser:    |
|                                                                                                                                           |
| i para insercao. As quatro linhas seguintes conterao nome, endereco, telefone e data de aniversario. O nome tem ate 50 caracteres, o      |
| endereco ate 100, o telefone ate 12 digitos e a data de aniversario tem o formato dd/mm/aa.                                               |
|                                                                                                                                           |
| r para remocao. A linha seguinte tem uma cadeia de caracteres representando um nome. Seu programa deve remover todos os registros que     |
| tenham nome exatamente igual ao digitado. O programa deve imprimir o numero de registros removidos.                                       |
|                                                                                                                                           |
| b para busca. A linha seguinte tem uma cadeia de caracteres representando um nome. Seu programa deve imprimir todos os registros que      |
| tenham nome contendo alguma parte que e igual ao nome digitado, na ordem em que foram inseridos.                                          |
|                                                                                                                                           |
| p para impressao. Seu programa deve imprimir todos os registros na agenda, na ordem em que foram inseridos.                               |
|                                                                                                                                           |
| f para finalizar o programa.                                                                                                              |
---------------------------------------------------------------------------------------------------------------------------------------------
*/


#include <stdio.h>
#include <string.h>

typedef struct registro{
    char nome[51];
    char endereco[101];
    long telefone;
    char data[9];
} contato;

void inserir (contato* vet) {/*funcao de insercao, nao tem segredo: os dados sao armazenados em variaveis locais e depois copiadas para as 
respectivas instancias das structs*/
    char nome[51] = {}, endereco[101] = {}, data[9] = {};
    scanf(" %[^\n]", nome);//talvez aprimorar aqui com menos variaveis
    scanf(" %[^\n]", endereco);
    scanf("%ld ", &vet->telefone);
    scanf(" %[^\n]", data);
    strcpy(vet->nome, nome);
    strcpy(vet->endereco, endereco);
    strcpy(vet->data, data);
    printf("Contato para %s inserido.\n\n", vet->nome);
}

void remover (contato* vet, int* tam) {
    char nome[51] = {};
    int i, j, removidos = 0, flag = 0;
    scanf(" %[^\n]", nome);
    for (i = 0; i < *tam; ) {
        flag = strcmp(vet[i].nome, nome); //essa flag retorna 0 caso encontre uma ocorrencia exatamente igual
        if (!flag) {    
            removidos+=1;
            *tam = *tam -1; //e necessario mudar o valor do tam na main tambem porque a agenda de registros diminui quando alguem e removido
            for (j = i; j < *tam; j++) {
                vet[j] = vet[j+1]; //os apontadores de cada posicao depois da remocao devem ser transferidos em uma posicao para frente
            }
        } else {
            i++;
        }
    }
    printf("Contatos de %s removidos: %d.\n\n", nome, removidos);
}

void buscar (contato* vet, int tam) {
    char nome[51] = {};
    scanf(" %[^\n]", nome);
    int i, j, flag = 0, cont = 0;
    printf("Resultado da busca:\n");
    for (i = 0; i < tam; i++) {
        for (j = 0; j < (strlen(vet[i].nome)-strlen(nome)+1); j++) {
            flag = strncmp (&vet[i].nome[j], nome, strlen(nome));
            if (!flag) {
                printf("(%d) %s\t%s\t%ld\t%s\n\n", (i+1), vet[i].nome, vet[i].endereco, vet[i].telefone, vet[i].data);
                cont++;
                break;
            }
        }
    }
    if (!cont) {
        printf("Nenhum contato.\n\n");
    }
}


void imprimir (contato* vet, int tam) {
    if (tam) {
        int i;
        printf("Listagem:\n");
        for (i = 0; i < tam; i++) {
            printf("(%d) %s\t%s\t%ld\t%s\n", (i+1), vet[i].nome, vet[i].endereco, vet[i].telefone, vet[i].data);
        }
        printf("\n");
    } else {
        printf("Listagem:\n");
        printf("Nenhum contato.\n\n");
    }
}

int main () {
    char op[2] = {};//variavel para guardar a operacao a ser dada na entrada
    contato arr[1000] = {};//um array de 1000 structs porque esse e o limite de contatos a serem inseridos
    int cont = 0;//contador da quantidade de contatos inseridos
    scanf("%s", op);
    while (*op != 'f') {
        if (*op == 'i') {
                inserir(&arr[cont]);
                cont+=1;
            } else if (*op == 'r') {
                remover(arr, &cont);
            } else if (*op == 'b') {
                buscar(arr, cont);
            } else if (*op == 'p') {
                imprimir(arr, cont);
            }
        scanf("%s", op);
    }
    return 0;
}
