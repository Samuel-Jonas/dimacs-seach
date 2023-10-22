#ifndef HEURISTIC_H
#define HEURISTIC_H

#include <math.h>
#include <stdint.h>

enum Heuristic {
    NONE,
    EUCLIDEAN,
    HAVERSINE
};

uint32_t calc_heuristic(enum Heuristic heuristic, int32_t x1, int32_t y1, int32_t x2, int32_t y2);

#endif
