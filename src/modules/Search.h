#ifndef SEARCH_H
#define SEARCH_H

#include <stdint.h>

#include "Graph.h"
#include "Heuristic.h"
#include "Queue.h"
#include "Stack.h"

struct Stack best_first_search(struct Graph graph, uint32_t initial, uint32_t end, enum Heuristic heuristic);
struct Stack depth_first_search(struct Graph graph, uint32_t initial, uint32_t end);
struct Stack breadth_first_search(struct Graph graph, uint32_t initial, uint32_t end);

#endif
