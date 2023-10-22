#include "Graph.h"

void read_coordinates_file(FILE* file, struct Graph* graph) {
    graph->vertexes_size = read_coordinates_file_header(file);
    graph->vertexes = malloc(graph->vertexes_size * sizeof(struct Vertex));

    for (int i = 0; i < graph->vertexes_size; i++) {
        uint32_t id;

        fscanf(file,
               "v %d %d %d\n",
               &id,
               &graph->vertexes[i].x_coordinate,
               &graph->vertexes[i].y_coordinate);

        graph->vertexes[i].distance = 0;
        graph->vertexes[i].parent = 0;
        graph->vertexes[i].neighbourhood_size = 0;
        graph->vertexes[i].neighbourhood = NULL;
    }
}

void read_distances_file(FILE* file, struct Graph* graph) {
    uint32_t edges_quantity = read_distances_file_header(file);

    for (int i = 0; i < edges_quantity; i++) {
        uint32_t v1, v2, distance;
        fscanf(file, "a %d %d %d\n", &v1, &v2, &distance);

        v1--;
        v2--;

        graph->vertexes[v1].neighbourhood_size++;
        graph->vertexes[v1].neighbourhood = realloc(
                graph->vertexes[v1].neighbourhood,
                graph->vertexes[v1].neighbourhood_size * sizeof(struct Edge));

        struct Edge edge = {
            .vertex = v2,
            .distance = distance
        };

        graph->vertexes[v1].neighbourhood[graph->vertexes[v1].neighbourhood_size - 1] = edge;
    }
}

struct Graph create_graph(char* coordinates_filepath, char* distances_filepath) {
    FILE* coordinates_file = open_file(coordinates_filepath);
    FILE* distances_file = open_file(distances_filepath);

    struct Graph graph = {
        .vertexes_size = 0,
        .vertexes = NULL
    };

    if (coordinates_file == NULL || distances_file == NULL)
        return graph;

    read_coordinates_file(coordinates_file, &graph);

    if (graph.vertexes_size != 0)
        read_distances_file(distances_file, &graph);

    return graph;
}
