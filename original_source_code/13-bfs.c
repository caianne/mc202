// Anne Feng Cai 261026
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {//Nó para armazenar a vizinhança de alguém na lista de adjacência
    int value;
    struct Node* next;
} Node;

typedef struct GraphList {//Lista de adjacência com o vetor da referência e contadores de vértice e aresta
    int vertex_size, edge_size;
    Node** adj_vector;
} GraphList;

typedef struct GraphVector {
    int* vertex, * edge, vertex_size, edge_size;
} GraphVector;

typedef struct vertex_distance {
    int vertice, distancia;
} vertex_distance;

GraphList* create_graphlist() {//Cria e inicializa uma lista de adjacência desconsiderando o 0
    int vertex_size;
    GraphList* pgraph;
    scanf("%d", &vertex_size);//O tamanho deve ser informado nesse formato
    pgraph = malloc(sizeof(GraphList));
    pgraph->adj_vector = malloc((vertex_size+1)*sizeof(Node*));
    pgraph->vertex_size = vertex_size;
    pgraph->edge_size = 0;
    for (int i = 0; i <= vertex_size; i++)
        pgraph->adj_vector[i] = NULL;
    return pgraph;
}

Node* insert_node(Node* list_first, int x) {//Insere e arruma os nós da lista ligada da lista de adjacência
    Node* new = malloc(sizeof(Node));
    new->value = x;
    new->next = list_first;//Coloca cada nó no início deixando os mais antigos para o final
    return new;
}

void insert_edge(GraphList* pgraph, int x1, int x2) {//Insere arestas novas setando dos dois lados (é bidirecional)
    pgraph->adj_vector[x1] = insert_node(pgraph->adj_vector[x1], x2);
    pgraph->adj_vector[x2] = insert_node(pgraph->adj_vector[x2], x1);
    return;
}

void clear_vector(Node* list) {//Desaloca a memória alocada para cada nó de forma recursiva
    if (list != NULL) {
        clear_vector(list->next);
        free(list);
    }
    return;
}

void clear_graphlist(GraphList* pgraph) {//Desaloca a memória para cada nó, depois o vetor e a estrutura do grafo
    for (int i = 0; i <= pgraph->vertex_size; i++)
        clear_vector(pgraph->adj_vector[i]);
    free(pgraph->adj_vector);
    free(pgraph);
    return;
}

void print_graphlist(GraphList* pgraph) {//Mostra todas as arestas da lista de adjacência
    Node* address;
    for (int i = 0; i <= pgraph->vertex_size; i++) {
        address = pgraph->adj_vector[i];
        while (address != NULL) {
            printf("%d %d\n", i, address->value);
            address = address->next;//para o caso da referência ter mais de um vizinho
        }
    }
    return;
}

GraphVector* create_graphVector(GraphList* pgraph) {//Transforma a lista de adjacência em vetor de adjacência
    GraphVector* pgraphvector;
    pgraphvector = malloc(sizeof(GraphVector));
    pgraphvector->vertex = malloc((pgraph->vertex_size+1)*sizeof(int));//para não deixar nada no 0
    pgraphvector->edge = malloc((pgraph->edge_size)*sizeof(int));
    pgraphvector->vertex_size = pgraph->vertex_size;
    pgraphvector->edge_size = pgraph->edge_size;
    for (int i = 0; i <= pgraph->vertex_size; i++)
        pgraphvector->vertex[i] = -1;
    int position = 0;//nas arestas não tem problema começar a escrever no 0
    Node* address;//um auxiliar para percorrer a lista ligada
    for (int i = 1; i <= pgraph->vertex_size; i++) {
        address = pgraph->adj_vector[i];
        if (address != NULL)
            pgraphvector->vertex[i] = position;//Troca o -1 pelo índice do primeiro vizinho de i guardado em edge
        while (address != NULL) {//Preenche o edge com todos os vizinhos de i
            pgraphvector->edge[position] = address->value;
            position++;
            address = address->next;
        }
    }
    return pgraphvector;
}

void print_graphvector(GraphVector* pgraph) {//Mostra todas as arestas do vetor de adjacência
    int limit;
    for (int i = 1; i <= pgraph->vertex_size; i++) {//Começa em 1 porque o vértice 0 faz parte do código de parada
        if (pgraph->vertex[i] != -1) {//Somente imprime aqueles que possuem vizinhos
            limit = i+1;//limite final em edge
            while ((limit <= pgraph->vertex_size) && (pgraph->vertex[limit] == -1)) {//Limite final é dado pelo próximo que não -1
                limit++;
            }
            if (limit > pgraph->vertex_size) {//Caso ultrapasse o tamanho do vértice, tal i possui o restante de edge como vizinho
                for (int j = pgraph->vertex[i]; j < pgraph->edge_size; j++) {
                    printf("%d %d\n", i, pgraph->edge[j]);
                }
                break;//Como é todo o restante, depois deste i os próximos (se houverem) não podem possuir vizinhos
            }
            //Como tem um break, é para todos os vizinhos que não estão no fim do vetor edges
            limit = pgraph->vertex[limit];
            for (int j = pgraph->vertex[i]; j < limit; j++) {//j irá percorrer edges com limites inferior e superior
                printf("%d %d\n", i, pgraph->edge[j]);
            }
        }
    }
    return;
}

void clear_graphvector(GraphVector* pgraph) {//Desaloca a memória do vetor de adjacência
    free(pgraph->vertex);
    free(pgraph->edge);
    free(pgraph);
    return;
}

void bfs(GraphVector* pgraph) {
    int value, limit, inicio = 0, fim = 0, quant_fila = 0;
    scanf("%d", &value);
    int visitado[pgraph->vertex_size + 1];
    vertex_distance* bfs_result;
    bfs_result = malloc(pgraph->vertex_size*sizeof(vertex_distance));
    for (int i = 0; i <= pgraph->vertex_size; i++) {
        visitado[i] = 0;
    }
    (bfs_result+inicio)->vertice = value;
    (bfs_result+inicio)->distancia = 0;
    visitado[value] = 1;
    quant_fila = 1;
    printf("Origem da busca: %d\nVertices alcancados e distancias:\n", value);
    while (quant_fila != 0) {
        printf("%d %d\n", (bfs_result+inicio)->vertice, (bfs_result+inicio)->distancia);
        quant_fila--;
        if (pgraph->vertex[(bfs_result+inicio)->vertice] != -1) {//Somente adiciona na fila aqueles que possuem vizinhos
            limit = (bfs_result+inicio)->vertice + 1;//limite final do vértice
            while ((limit <= pgraph->vertex_size) && (pgraph->vertex[limit] == -1)) {//Limite final é dado pelo próximo que não -1
                limit++;
            }
            if (limit > pgraph->vertex_size) {//Caso ultrapasse o tamanho do vértice, tal i possui o restante de edge como vizinho
                for (int j = pgraph->vertex[(bfs_result+inicio)->vertice]; j < pgraph->edge_size; j++) {
                    if (!visitado[pgraph->edge[j]]) {
                        fim++;//fim determina o final da fila
                        (bfs_result+fim)->vertice = pgraph->edge[j];
                        (bfs_result+fim)->distancia = (bfs_result+inicio)->distancia + 1;
                        visitado[pgraph->edge[j]] = 1;
                        quant_fila++;
                    }
                }
            }
            else {//Caso não ultrapasse, o limite é dado pelo que vem no vetor dos vértices
                limit = pgraph->vertex[limit];
                for (int j = pgraph->vertex[(bfs_result+inicio)->vertice]; j < limit; j++) {
                    if (!visitado[pgraph->edge[j]]) {
                        fim++;
                        (bfs_result+fim)->vertice = pgraph->edge[j];
                        (bfs_result+fim)->distancia = (bfs_result+inicio)->distancia + 1;
                        visitado[pgraph->edge[j]] = 1;
                        quant_fila++;
                    }
                }
            }
        }
        inicio++;//inicio determina o inicio da fila
    }
    free(bfs_result);
    return;
}

int main() {
    GraphList* pgraphlist;
    pgraphlist = create_graphlist();
    int x1, x2;
    scanf("%d,%d", &x1, &x2);
    while (x1 != 0 && x2 != 0) {//0,0 é nosso código de parada
        insert_edge(pgraphlist, x1, x2);
        pgraphlist->edge_size+=2;//o contador de aresta aumenta em 2 já que é bidirecional
        scanf("%d,%d", &x1, &x2);
    }
    GraphVector* pgraphvector = create_graphVector(pgraphlist);
    clear_graphlist(pgraphlist);
    bfs(pgraphvector);
    clear_graphvector(pgraphvector);
    return 0;
}