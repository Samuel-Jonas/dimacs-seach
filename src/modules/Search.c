#include "Search.h"

struct Stack create_result_path(struct Graph graph, uint32_t initial, uint32_t end) {
    struct Stack stack = create_stack();
    push_stack(&stack, end);

    while (end != initial) {
        end = graph.vertexes[end].parent;
        push_stack(&stack, end);
    }

    return stack;
}

struct Stack best_first_search(struct Graph graph, uint32_t initial, uint32_t end, enum Heuristic heuristic) {
    struct PriorityQueue queue = create_priority_queue();
    uint32_t aux = initial;

    while (aux != end) {
        for (uint32_t i = 0; i < graph.vertexes[aux].neighbourhood_size; i++) {
            struct Edge edge = graph.vertexes[aux].neighbourhood[i];

            if (edge.vertex == initial || graph.vertexes[edge.vertex].distance != 0)
                continue;

            graph.vertexes[edge.vertex].parent = aux;
            graph.vertexes[edge.vertex].distance = graph.vertexes[aux].distance + edge.distance;

            uint32_t heuristic_cost = calc_heuristic(heuristic,
                                                     graph.vertexes[edge.vertex].x_coordinate,
                                                     graph.vertexes[edge.vertex].y_coordinate,
                                                     graph.vertexes[end].x_coordinate,
                                                     graph.vertexes[end].y_coordinate);
            uint32_t cost = graph.vertexes[edge.vertex].distance + heuristic_cost;

            insert_into_queue(&queue, edge.vertex, cost);
        }

        if (queue.size == 0)
            return create_stack();

        aux = pop_queue(&queue);
    }

    free_queue(&queue);

    return create_result_path(graph, initial, end);
}