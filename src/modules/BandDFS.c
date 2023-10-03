#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int identifier;
    struct Node* prox;
};

struct Graph {
    int num_edges;
    struct Node** adj_lists;
    bool* visited;
};

struct Node* create_node(int identifier) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node*));
    
    new_node -> identifier = identifier;
    new_node -> prox = NULL;
    
    return new_node;
}

struct Graph* create_graph(int num_edges) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    
    graph -> num_edges = num_edges;
    graph -> adj_lists = (struct Node**)malloc(num_edges * sizeof(struct Node*));
    graph -> visited = (bool*)malloc(num_edges * sizeof(bool));

    for (int i = 0; i < num_edges; i++) {
        graph -> adj_lists[i] = NULL;
        graph -> visited[i] = false;
    }

    return graph;
}

void add_edge(struct Graph* graph, long init, long fin) {
    struct Node* node = create_node(fin);

    node -> prox = graph -> adj_lists[init];
    graph -> adj_lists[init] = node;
}

int build_adj_list(struct Graph* graph) {
    FILE *file;
    char line[100];
    long init, fin, distance = 0;

    file = fopen("../base/USA-road-d.NY.gr.txt", "r");

    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    while (fgets(line, sizeof(line), file)) {

        if (line[0] == 'a') {
            if (sscanf(line, "a %ld %ld %ld", &init, &fin, &distance) == 3) {
                add_edge(graph, init, fin);
            }
        }
    }

    fclose(file);

    return 0;
}

/*int count_edges(char* path) {
    FILE *file;
    char line[100];
    int count_edges = 0;

    file = fopen(path, "r");

    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    while (fgets(line, sizeof(line), file)) {

        if (line[0] == 'a') {
            count_edges++;
        }
    }

    fclose(file);

    return count_edges;
}*/

void bfs(struct Graph* graph, int initial_node, int final_node) {
    int* queue = (int*)malloc(graph -> num_edges * sizeof(int));
    int front = 0, rear = 0;

    graph -> visited[initial_node] = true;
    queue[rear++] = initial_node;

    printf("[ ");

    while (front < rear) {
        int index = queue[front++];
        printf("%d", index);

        struct Node* aux = graph -> adj_lists[index];

        while (aux != NULL) {
            int adj_node = aux -> identifier;

            if (adj_node == final_node) {
                printf("]");
                front = rear;
                break;
            }


            if (!graph -> visited[adj_node]) {
                graph -> visited[adj_node] = true;
                queue[rear++] = adj_node;
            }

            aux = aux -> prox;
        }
    }
}

void dfs(struct Graph* graph, int initial_node, int final_node) {
    int* stack = (int*) malloc(graph -> num_edges * sizeof(int));
    int top = -1;

    graph -> visited[initial_node] = true;
    stack[++top] = initial_node;

    while (top != -1) {
        int node = stack[top--];
        printf("%d", node);

        struct Node* aux = graph -> adj_lists[node];
        while (aux != NULL) {
            int adj_node = aux -> identifier;

            if (!graph -> visited[adj_node]) {
                graph -> visited[adj_node] = true;
                stack[++top] = adj_node;
            }

            aux = aux -> prox;
        }
    }

    free(stack);
}

int main() {
    int num_edges = 733846;//count_edges("../base/USA-road-d.NY.gr.txt");
    struct Graph* graph = create_graph(num_edges);

    build_adj_list(graph);

    //bfs(graph, 6, 37);
    dfs(graph, 6, 37);

    free(graph);

    return 0;
}
