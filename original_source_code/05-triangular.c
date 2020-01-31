/* 
---------------------------------------------------------------------------------------------------------------------------------------------
| Nome: Anne Feng Cai                                                                                                                       |
|                                                                                                                                           |
| Entrada: Um numero que representa a quantidade de linhas e uma matriz triangular inferior.                                                |
|                                                                                                                                           |
| Saida: Uma nova matriz triangular inferior com valores = (original - media)/desvio padrao, seguido da media e do desvio padrao. Todos os  |
| valores possuem 12 casas decimais.                                                                                                        |
---------------------------------------------------------------------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int tam;//armazena o tamanho maximo de linhas da matriz
    double **p;//vai servir como um array de apontadores para as linhas da matriz triangular
    double soma, media, desvio;//vou usar soma para guardar tudo que for somatorio
    scanf("%d", &tam);
    p = malloc(tam*sizeof(double*));//alocando dinamicamente um array de apontadores de apontadores
    while (!p) {//pro caso da memoria nao ser alocada pelo malloc... vai tentar alocar infinitamente ate conseguir
        p = malloc(tam*sizeof(double*));
    }
    for (int i = 0; i < tam; i++) {//faz (principalmente) a leitura dos dados
        *(p+i) = malloc((i+1)*sizeof(double));//para cada posicao do array de apontadores, armazenar o endereco do apontador da linha
        while (!(p+1)) {//pro caso da memoria nao ser alocada pelo malloc... vai tentar alocar infinitamente ate conseguir
        *(p+i) = malloc((i+1)*sizeof(double));
        }
        for (int j = 0; j < (i+1); j++) {//aproveito para ler os dados e ja colocar no somatorio da media
            scanf("%lf", (*(p+i)+j));
            soma += *(*(p+i)+j);
        }
    }
    media = soma/((pow(tam, 2) + tam)/2);//calcula a media
    soma = 0;//limpa o somatorio
    for (int i = 0; i < tam; i++) {//itera para conseguir calcular o desvio padrao
        for (int j = 0; j < (i+1); j++) {
            soma += pow(*(*(p+i)+j) - media, 2);//calcula o somatorio na formula do desvio-padrao
        }
    }
    desvio = sqrt(soma/((pow(tam, 2) + tam)/2));
    for (int i = 0; i < tam; i++) {//printa no formato pedido
        for (int j = 0; j < (i+1); j++) {
            printf("%.12f ", ((*(*(p+i)+j) - media)/desvio));//cada elemento vale z = (e - m)/d, em que e vale o elemento, m a media e d o desvio padrao
        }
        printf("\n");
        free(*(p+i));//limpa a linha alocada pelo malloc
    }
    free(p);//limpa o array de apontadores para apontadores
    printf("\n");
    printf("%.12f %.12f \n", media, desvio);
    return 0;
}