#ifndef SEARCH_H
#define SEARCH_H

#include <stdint.h>

#include "Graph.h"
#include "Heuristic.h"
#include "Queue.h"

void a_star(struct Graph graph, uint32_t initial, uint32_t end);

#endif
