#include <stdio.h>
#include <stdlib.h>

struct Node {
    int identifier;
    struct Node* prox;
};

struct Graph {
    int num_edges;
    struct Node** adj_lists;
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

    for (int i = 0; i < num_edges; i++) {
        graph -> adj_lists[i] = NULL;
    }

    return graph;
}

void add_edge(struct Graph* graph, int init, int fin) {
    struct Node* node = create_node(fin);

    node -> prox = graph -> adj_lists[init];
    graph -> adj_lists[init] = node;
}

void show_graph(struct Graph* graph) {
    for (int i = 0; i < graph -> num_edges; i++) {
        struct Node* node = graph -> adj_lists[i];

        printf("%d:\n", i);

        while (node) {
            printf(" -> %d", node -> identifier);
            node = node -> prox;
        }
        printf("\n");
    }
}

int main() {
    int num_edges = 5;
    struct Graph* graph = create_graph(num_edges);

    add_edge(graph, 0, 1);
    add_edge(graph, 0, 2);
    add_edge(graph, 1, 2);
    add_edge(graph, 2, 3);
    add_edge(graph, 3, 4);

    show_graph(graph);

    return 0;
}
