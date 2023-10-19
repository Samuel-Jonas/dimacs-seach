#include "File.h"

FILE* open_file(char* path) {
    FILE* file = fopen(path, "r");

    if (file == NULL)
        fprintf(stderr, "It can't open the file: %s\n", path);

    return file;
}

uint32_t read_coordinates_file_header(FILE* file) {
    uint32_t vertexes_quantity;

    if (fscanf(file, "p aux sp co %d\n", &vertexes_quantity) != 1)
        vertexes_quantity = 0;

    return vertexes_quantity;
}

uint32_t read_distances_file_header(FILE* file) {
    uint32_t vertexes_quantity, edges_quantity;

    if (fscanf(file, "p sp %d %d\n", &vertexes_quantity, &edges_quantity) != 2)
        edges_quantity = 0;

    return edges_quantity;
}