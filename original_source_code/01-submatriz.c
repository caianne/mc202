/* 
-----------------------------------------------------------------------------------------------------
| Nome: Anne Feng Cai                                                                               |
|                                                                                                   |
| Descricao: Esse programa encontra a maior soma de elementos de uma submatriz r por s de uma       |
| matriz original n por m. A estrategia adotada foi a da soma acumulada (prefix sum): ao inves de   |
| usar a matriz original A, representa-se cada valor aij como o valor da soma dos elementos da      |
| submatriz dos elementos desde a posicao 00 ate ij. Alem disso, aqui a linha 0 e coluna 0 e        |
| preenchida somente por 0's de forma a simplificar o codigo (menos if's e else if's).              |
|                                                                                                   | 
| Entrada: Uma linha contendo inteiros n, m, r e s. "n" linhas seguintes contendo, cada uma, m      |
| inteiros, representando ao todo uma matriz n por m.                                               |
|                                                                                                   |
| Saida: Um inteiro que representa a maior soma de elementos de submatriz r por s possivel          |
| a partir da matriz original n por m.                                                              |
-----------------------------------------------------------------------------------------------------
*/

#include <stdio.h>

int main() {

//  n, m, r e s representam as dimensoes da matriz e submatriz
//  i e j sao os contadores de iteracao nos indices da matriz
//  "temp" e uma variavel de armazenamento temporaria
//  "maior" armazena a maior soma ate entao
    
    int n, m, r, s, i, j, temp, maior = 0;
    scanf("%d %d %d %d", &n, &m, &r, &s);
    int matriz[n+1][m+1]; // a matriz possui linha e coluna adicionais para os 0's nos indices i = 0 e j = 0
    i = 0;

    while (i == 0) { // inicializando a linha i = 0 contendo m+1 zeros
        for (j = 0; j <= m; j++) {
            matriz[i][j] = 0;
        }
        i+=1;
    }

    j = 0;
    
    while (j == 0) { // inicializando a coluna j = 0 contendo n zeros
        for (i = 1; i <= n; i++) {
            matriz[i][j] = 0;
        }
        j+=1;
    }

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            if ((i >= r) || (i == r && j >= s)) { // elementos a partir dos quais a submatriz pode ser gerada
                if (i == r && j == s) { // caso especial do elemento rs para inicializar o valor de "maior"
                        scanf("%d", &temp);
                        matriz[r][s] = temp + matriz[r-1][s] + matriz[r][s-1] - matriz[r-1][s-1];
                        maior = matriz[r][s];
                } else { // casos "normais" para testar as somas de submatrizes e armazenar a maior delas
                    scanf("%d", &temp);
                    matriz[i][j] = temp + matriz[i-1][j] + matriz[i][j-1] - matriz[i-1][j-1];
                    temp = matriz[i][j] - matriz[i-r][j] - matriz[i][j-s] + matriz[i-r][j-s];
                    if (temp > maior){
                        maior = temp;
                    }
                }
            } else { // casos nos quais a submatriz rs ainda nao pode ser gerada mas a soma dos elementos sim
                scanf("%d", &temp);
                matriz[i][j] = temp + matriz[i-1][j] + matriz[i][j-1] - matriz[i-1][j-1];
            }
        }
    }
    printf("%d\n", maior);
}
