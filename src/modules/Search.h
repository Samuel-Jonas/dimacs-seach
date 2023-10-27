#ifndef SEARCH_H
#define SEARCH_H

#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#include "Graph.h"
#include "Heuristic.h"
#include "Queue.h"
#include "Stack.h"

struct SearchResult {
    struct Stack path;
    bool is_found;
    uint32_t extra_memory;
    uint32_t expanded_nodes;
    double branching_factor;
    double execution_time;
};

struct Stack best_first_search(struct Graph graph, uint32_t initial, uint32_t end, enum Heuristic heuristic);
struct SearchResult depth_first_search(struct Graph graph, uint32_t initial, uint32_t end, uint32_t max_vertexes);
struct SearchResult breadth_first_search(struct Graph graph, uint32_t initial, uint32_t end, uint32_t max_vertexes);

#endif
