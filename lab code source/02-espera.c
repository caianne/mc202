/* 
-----------------------------------------------------------------------------------------------------
| Nome: Anne Feng Cai                                                                               |
|                                                                                                   |
| Descricao: Esse programa calcula o tempo de espera para receber atendimento em uma fila unica de  |
| clientes para um ou mais atendentes.                                                              |
|                                                                                                   |
| Entrada: Uma linha contendo inteiros c (numeros de atendentes) e n (numero de clientes), seguido  |
| de n linhas contendo inteiros t (horario de chegada) e d (tempo de atendimento) para cada cliente |
| de acordo com a ordem de chegada.                                                                 |
|                                                                                                   |
| Saida: "Espera media para n clientes: x minutos"                                                  |
|        "Numero de clientes que esperaram mais que 10 minutos: m"                                  |
-----------------------------------------------------------------------------------------------------
*/

#include <stdio.h>

int main() {
    int c, n, i, j, fila[10] = {0}, cliente[2], espera[2] = {0}, menor = 0, aux=0;
    /*c = numero de atendentes; n = numero de clientes; i = contador de clientes; j = contador de atendentes;
    fila = tempo de atendimento de cada atendente; cliente = horario de chegada e tempo de atendimento do cliente;
    espera = tempo de espera; menor = menor tempo de espera de atendente; aux = indice do atendente mais rapido*/

    scanf("%d %d", &c, &n);
    for (i = 0; i < n; i++) {

        for (j = 0; j < c; j++) {
            if (fila[j] <= menor){ //<= para nao bugar no primeiro caso
                menor = fila[j];
                aux = j;
            }
        }
        
        scanf("%d %d", &cliente[0], &cliente[1]);
        if (cliente[0] >= fila[aux]) {
            fila[aux] = cliente[0] + cliente[1]; /*Se o cliente nao precisa esperar, o tempo do atendente vira a 
            soma do horario de chegada do cliente com o seu tempo de atendimento*/
        }
        
        else {
            if (fila[aux] - cliente[0] > 10) {
                espera[1]+=1; //Contando a quantidade de clientes que esperam mais de 10 minutos
            }
            espera[0] += fila[aux] - cliente[0]; //Somando na conta da espera o tempo de espera do cliente
            fila[aux] = fila[aux] + cliente[1]; //Mudando a fila do atendente do cliente em questao
        }
        menor = fila[aux]; //Atualizando o valor do "menor" para seu valor atual (que aumenta por causa do cliente)
    }
    printf("Espera media para %d clientes: %.1f minutos\n", n, 1.0*espera[0]/n);
    //Multiplicando por 1.0 para ter casas decimais em x
    printf("Numero de clientes que esperaram mais que 10 minutos: %d\n", espera[1]);
}
