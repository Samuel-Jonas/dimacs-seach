#ifndef GRAPH_H
#define GRAPH_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "File.h"

struct Edge {
    uint32_t distance;
    uint32_t vertex;
};

struct Vertex {
    int32_t x_coordinate;
    int32_t y_coordinate;
    uint64_t distance;
    uint32_t parent;
    uint32_t neighbourhood_size;
    struct Edge* neighbourhood;
};

struct Graph {
    uint32_t vertexes_size;
    struct Vertex* vertexes;
    bool* visited;
};

void read_coordinates_file(FILE* file, struct Graph* graph);
void read_distances_file(FILE* file, struct Graph* graph);
struct Graph create_graph(char* coordinates_filepath, char* distances_filepath);

#endif
