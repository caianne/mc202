typedef struct no {
    struct no* menor;
    struct no* maior;
    int valor;
} no;

typedef struct bst {
    no* raiz;
    int ocupado;
} bst;

typedef struct nofila {
    no* endereco;
    struct nofila* prox;
} nofila;

typedef struct fila {
    nofila* ini, *fim;
} fila;

void inserir(bst*);

void buscar(bst*);

void pos_ordem(no*);

void em_ordem(no*);

void pre_ordem(no*);

void inlining (fila*, no*);

void largura(no*);

void clean(no*);