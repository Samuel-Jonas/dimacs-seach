#include "Search.h"

struct Stack get_result_path(struct Graph graph, uint32_t initial, uint32_t end) {
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

    return get_result_path(graph, initial, end);
}

struct Stack depth_first_search(struct Graph graph, uint32_t initial, uint32_t end) {
    struct Stack stack = create_stack();

    graph.vertexes[initial].distance = 1;
    push_stack(&stack, initial);

    while (stack.size != 0) {
        uint32_t aux = pop_stack(&stack);

        if (aux == end)
            break;

        for (uint32_t i = 0; i < graph.vertexes[aux].neighbourhood_size; i++) {
            uint32_t v = graph.vertexes[aux].neighbourhood[i].vertex;

            if (graph.vertexes[v].distance == 0) {
                graph.vertexes[v].parent = aux;
                graph.vertexes[v].distance = 1;

                push_stack(&stack, v);
            }
        }
    }

    free_stack(&stack);

    return get_result_path(graph, initial, end);
}

struct SearchResult breadth_first_search(struct Graph graph, uint32_t initial, uint32_t end, uint32_t max_vertexes) {
    uint32_t vertexes_counter = 0, branching_factor = 0, extra_memory = 0;
    struct PriorityQueue queue = create_priority_queue();
    extra_memory += sizeof(struct PriorityQueue);

    double initial_time = clock();
    graph.vertexes[initial].distance = 1;
    insert_into_queue(&queue, initial, 0);
    extra_memory += sizeof(struct QueueNode);

    while (queue.size != 0 && vertexes_counter < max_vertexes) {
        uint32_t aux = pop_queue(&queue);

        if (aux == end)
            break;

        for (uint32_t i = 0; i < graph.vertexes[aux].neighbourhood_size; i++) {
            uint32_t v = graph.vertexes[aux].neighbourhood[i].vertex;

            if (graph.vertexes[v].distance == 0) {
                graph.vertexes[v].parent = aux;
                graph.vertexes[v].distance = 1;

                insert_into_queue(&queue, v, 0);
                extra_memory += sizeof(struct QueueNode);

                branching_factor++;
            }
        }

        vertexes_counter++;
    }
    double final_time = clock();

    free_queue(&queue);

    struct SearchResult result;

    result.is_found = graph.vertexes[end].parent != 0;
    result.extra_memory = extra_memory;
    result.expanded_nodes = vertexes_counter;
    result.branching_factor = (double)branching_factor / vertexes_counter;
    result.execution_time = (double)(final_time - initial_time) / CLOCKS_PER_SEC;

    if (result.is_found)
        result.path = get_result_path(graph, initial, end);

    return result;
}