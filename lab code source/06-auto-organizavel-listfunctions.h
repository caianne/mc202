typedef struct no {//struct da lista encadeada sem contador de acessos
    int index;
    struct no* next;
} no;

typedef struct noc {//struct da lista encadeada com contador de acessos
    int index;
    int count;
    struct noc* next;
} noc;

no* createlist(int);

noc* createlistc(int);

void freelist(no*);

void freelistc(noc*);

void printlist(no*);

void printlistc(noc*);

int movetofront(int, no*);

int transpose(int, no*);

int counting(int, noc*);