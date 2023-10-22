#include "Heuristic.h"

uint32_t calc_euclidean_distance(int64_t x1, int64_t y1, int64_t x2, int64_t y2) {
    int64_t x_difference = powl(x2 - x1, 2);
    int64_t y_difference = powl(y2 - y1, 2);

    return sqrtl(x_difference + y_difference);
}

uint32_t calc_haversine_distance(long double x1, long double y1, long double x2, long double y2) {
    const long double EARTH_RADIUS = 6371;
    const long double RADIANS = (3.1415926536 / 180);

    x1 -= x2;
    x1 *= RADIANS;
    y1 *= RADIANS;
    y2 *= RADIANS;

    long double dz = sinl(y1) - sinl(y2);
    long double dx = cosl(x1) * cosl(y1) - cosl(y2);
    long double dy = sinl(x1) * cosl(y1);

    return asinl(sqrtl(dx * dx + dy * dy + dz * dz) / 2) * 2 * EARTH_RADIUS;
}

uint32_t calc_heuristic(enum Heuristic heuristic, int32_t x1, int32_t y1, int32_t x2, int32_t y2) {
    switch (heuristic) {
        case EUCLIDEAN:
            return calc_euclidean_distance(x1, y1, x2, y2);
        case HAVERSINE:
            return calc_haversine_distance(x1, y1, x2, y2);
        default:
            return 0;
    }
}