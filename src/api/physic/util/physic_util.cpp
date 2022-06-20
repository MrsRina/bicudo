#include "physic_util.h"
#include "api/client/instance.h"

float rigid::interval_dist(float min_a, float max_a, float min_b, float max_b) {
    if (min_a < min_b) {
        return min_b - max_a;
    } else {
        return min_a - max_b;
    }

    return 0;
}