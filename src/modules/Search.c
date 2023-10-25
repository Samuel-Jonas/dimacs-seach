#include "Search.h"

struct Stack a_star(struct Graph graph, uint32_t initial, uint32_t end) {
    struct PriorityQueue queue = create_priority_queue();
    initial--;
    end--;
    uint32_t aux = initial;

    while (aux != end) {
        for (uint32_t i = 0; i < graph.vertexes[aux].neighbourhood_size; i++) {
            struct Edge edge = graph.vertexes[aux].neighbourhood[i];

            if (edge.vertex == initial || graph.vertexes[edge.vertex].distance != 0)
                continue;

            graph.vertexes[edge.vertex].parent = aux;
            graph.vertexes[edge.vertex].distance = graph.vertexes[aux].distance + edge.distance;

            uint32_t heuristic = calc_euclidean_distance(graph.vertexes[edge.vertex], graph.vertexes[end]);
            uint32_t cost = graph.vertexes[edge.vertex].distance + heuristic;

            insert_into_queue(&queue, edge.vertex, cost);
        }

        struct QueueNode* node = pop_queue(&queue);
        aux = node->id;
        free(node);
    }

    free_queue(&queue);

    struct Stack stack = create_stack();
    push_stack(&stack, end);

    while (aux != initial) {
        aux = graph.vertexes[aux].parent;
        push_stack(&stack, aux);
    }

    return stack;
}

void bfs(struct Graph graph, uint32_t initial_node, uint32_t final_node) {
    struct PriorityQueue queue = create_priority_queue();
    int front = 0, rear = 0;

    graph.visited[initial_node] = true;
    struct Edge edge = graph.vertexes[initial_node].neighbourhood[rear++];

    //queue[rear++] = initial_node;
    insert_into_queue(&queue, edge.vertex, 1);
    
    while (front < rear) {
        //int index = queue[front++];
        struct QueueNode* node = pop_queue(&queue);
        uint32_t index = node->id;
        free(node);

        struct QueueNode* aux = graph -> adj_lists[index];

        while (aux != NULL) {
            int adj_node = aux -> identifier;

            if (adj_node == final_node) {
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
    struct Stack stack = create_stack();
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