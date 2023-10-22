#include "Heuristic.h"

uint32_t calc_euclidean_distance(struct Vertex v1, struct Vertex v2) {
    int64_t x_difference = powl((int64_t)v2.x_coordinate - v1.x_coordinate, 2);
    int64_t y_difference = powl((int64_t)v2.y_coordinate - v1.y_coordinate, 2);

    return sqrtl(x_difference + y_difference);
}