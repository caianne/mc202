#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct parametros {
    int tamanho, ocupado, inicio, fim;
} parametros;


void print_seq(int *teste, int limite) {
    for (int i = 0; i < limite; i++) {
        printf("%d ", teste[i]);
    } printf("\n");
}

void copia(int *sequencia, int *aux, parametros *parametro) {
    int j = 0;
    if (parametro->inicio != parametro->tamanho -1) {
        for (int i = parametro->inicio + 1; i < parametro->tamanho; i++) {
            aux[j] = sequencia[i];
            j++;
        } if (j < parametro->ocupado) {
            for (int i = 0; i < parametro->fim; i++) {
                aux[j] = sequencia[i];
                j++;
            }
        }
    } else {
        for (int i = 0; i < parametro->tamanho; i++) {
            aux[j] = sequencia[i];
            j++;
        }
    }
    parametro->fim = j;
}

void copia2(int *sequencia, int *aux, parametros *parametro) {
    int j = 0;
    if (parametro->inicio != parametro->tamanho -1) {
        for (int i = parametro->inicio; i < parametro->tamanho; i++) {
            aux[j] = sequencia[i];
            j++;
        } if (j < parametro->ocupado) {
            for (int i = 0; i < parametro->fim; i++) {
                aux[j] = sequencia[i];
                j++;
            }
        }
    } else {
        for (int i = 0; i < parametro->tamanho; i++) {
            aux[j] = sequencia[i];
            j++;
        }
    }
    parametro->fim = j;
    parametro->tamanho *= 2;
    parametro->inicio = parametro->tamanho - 1;
}

void copia3(int *sequencia, int *aux, parametros *parametro) {
    int j = 0;
    if (parametro->inicio != parametro->tamanho -1) {
        for (int i = parametro->inicio + 1; i < parametro->tamanho*0.5; i++) {
            aux[j] = sequencia[i];
            j++;
        } if (j < parametro->ocupado) {
            for (int i = 0; i < parametro->fim; i++) {
                aux[j] = sequencia[i];
                j++;
            }
        }
    } else {
        for (int i = 0; i < parametro->tamanho*0.5; i++) {
            aux[j] = sequencia[i];
            j++;
        }
    }
    parametro->fim = j;
}

void verifica_aumento(parametros *par, int **sequ) {
    int *aux, *libera;
    if (par->ocupado == par->tamanho) {
        aux = malloc(par->tamanho*2*sizeof(int));
        copia(*sequ, aux, par);
        par->tamanho*=2;
        par->inicio = par->tamanho - 1;
        libera = *sequ;
        *sequ = aux;
        free(libera);
    }
}

void verifica_aumento2(parametros *par, int **sequ) {
    int *aux, *libera;
    if (par->ocupado == par->tamanho) {
        aux = malloc(par->tamanho*2*sizeof(int));
        copia2(*sequ, aux, par);
        libera = *sequ;
        *sequ = aux;
        free(libera);
    }
}

void verifica_diminuicao(parametros *par, int **sequ) {    
    int *aux, *libera;
    if ((par->ocupado < par->tamanho*0.25) && (par->tamanho != 2)) {
        aux = malloc(par->tamanho*0.5*sizeof(int));
        copia3(*sequ, aux, par);
        par->tamanho = par->tamanho*0.5;
        par->inicio = par->tamanho - 1;
        libera = *sequ;
        *sequ = aux;
        free(libera);
    }
}

void insert_first(parametros *par, int **sequ) {
    int valor;
    scanf("%d", &valor);
    verifica_aumento(par, sequ);
    if (par->inicio) {
        (*sequ)[par->inicio] = valor;
        par->inicio--;
    } else {
        (*sequ)[par->inicio] = valor;
        par->inicio = par->tamanho - 1;
        par->fim++;
    }
    par->ocupado += 1;
}

void insert_last(parametros *par, int **sequ) {
    int valor;
    scanf("%d", &valor);
    verifica_aumento2(par, sequ);
    if (par->fim != par->tamanho - 1) {
        (*sequ)[par->fim] = valor;
        par->fim++;
    } else if (par->inicio) {
        (*sequ)[par->fim] = valor;
        par->fim = 0;
    } else {
        (*sequ)[par->fim] = valor;
    }
    par->ocupado += 1;
}

void remove_first(parametros *par, int** sequ) {
    if (par->ocupado > 0) {
        if (par->inicio != par->tamanho -1) {
            (*sequ)[par->inicio+1] = 0;
            par->inicio++;
        } else {
            (*sequ)[0] = 0;
            par->inicio = 0;
        }
        par->ocupado--;
    }
    verifica_diminuicao(par, sequ);
    if (par->ocupado == 1) {
        par->fim = 1;
    } else if (par->ocupado == 0) {
        par->fim = 0;
    }
}

void remove_last(parametros *par, int** sequ) {
    if (par->ocupado > 0) {
        if (par->fim) {
            (*sequ)[par->fim-1] = 0;
            par->fim--;
        } else {
            (*sequ)[par->tamanho - 1] = 0;
            par->fim = par->tamanho -1;
        }
        par->ocupado--;
    }
    verifica_diminuicao(par, sequ);
    if (par->ocupado == 1) {
        par->fim = 1;
    } else if (par->ocupado == 0) {
        par->fim = 0;
        par->inicio = 0;
    }
}

void print_first(parametros *par, int *seq) {
    if (par->ocupado) {
        if (par->inicio != par->tamanho - 1) {
            printf("%d\n", seq[par->inicio + 1]);
        } else {
            printf("%d\n", seq[0]);
        }
    }
}

void print_last(parametros *par, int *seq) {
    if (par->ocupado) {
        if (par->fim) {
            printf("%d\n", seq[par->fim -1]);
        } else {
            printf("%d\n", seq[par->tamanho-1]);
        }
    }
}

void is_empty(parametros *par) {
    if (par->ocupado) {
        printf("no\n");
    } else {
        printf("yes\n");
    }
}

int main() {
    char comando[20];
    int *seq = NULL;
    seq = malloc(2*sizeof(int));
    parametros par;
    par.tamanho = 2;
    par.ocupado = 0;
    par.inicio = 0;
    par.fim = 0;
    scanf("%s", comando);
    while(strncmp(comando,"exit",4) != 0) {
        if (strncmp(comando,"insert-first",12) == 0) {
            insert_first(&par, &seq);
        } else if (strncmp(comando,"insert-last",11) == 0) {
            insert_last(&par, &seq);
        } else if (strncmp(comando,"remove-first",12) == 0) {
            remove_first(&par, &seq);
        } else if (strncmp(comando,"remove-last",11) == 0) {
            remove_last(&par, &seq);
        } else if (strncmp(comando,"print-first",11) == 0) {
            print_first(&par, seq);
        } else if (strncmp(comando,"print-last",10) == 0) {
            print_last(&par, seq);
        } else if (strncmp(comando,"is-empty",8) == 0) {
            is_empty(&par);
        }
        scanf("%s", comando);
    }
    free(seq);
    return 0;
}
