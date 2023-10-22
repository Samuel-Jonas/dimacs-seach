#ifndef SEARCH_H
#define SEARCH_H

#include <stdint.h>

#include "Graph.h"
#include "Heuristic.h"
#include "Queue.h"
#include "Stack.h"

struct Stack a_star(struct Graph graph, uint32_t initial, uint32_t end);

#endif
