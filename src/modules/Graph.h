#ifndef GRAPH_H
#define GRAPH_H

#include <stdint.h>

struct Edge {
    uint32_t distance;
    uint32_t vertex;
};

struct Vertex {
    int32_t x_coordinate;
    int32_t y_coordinate;
    uint32_t neighbourhood_size;
    struct Edge* neighbourhood;
};

struct Graph {
    uint32_t vertexes_size;
    struct Vertex* vertexes;
};

#endif
