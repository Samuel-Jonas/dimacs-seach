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