/* 
-----------------------------------------------------------------------------------------------------
| Nome: Anne Feng Cai                                                                               |
|                                                                                                   |
| Entrada: Nenhuma.                                                                                 |
|                                                                                                   |
| Saida: A parte imprimivel da tabela ASCII.                                                        |
-----------------------------------------------------------------------------------------------------
*/

#include <stdio.h>

int main() {
    int i, c;
    printf("      +0");
    for (i = 1; i < 8; i++) {
        printf(" +%d", i);
    }
    printf(" ");
    printf("\n    +------------------------ \n");
    for ((c = 32); c < (97); c+=8) {
        printf(" %d |", c);
        for ((i = c); i < (c+8); i++) {
            printf("  %c", i);
        }
        printf(" \n");
    }
    for ((c = 104); c < (113); c+=8) {
        printf("%d |", c);
        for ((i = c); i < (c+8); i++) {
            printf("  %c", i);
        }
        printf(" \n");
    }
    printf("120 |");
    for ((i = 120); i < 127; i++) {
        printf("  %c", i);
    }
    printf("    \n");
}

