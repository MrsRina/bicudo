#include "bicudo/api/util/math.hpp"
#include <cmath>

float bicudo::matrix::orthographic[16] {};

float bicudo::lerpf(float a, float b, float t) {
    if (t < 0 || b >= 1.0f) {
        return a;
    }

    return a + (b - a) * t;
}

double bicudo::lerpd(double a, double b, double t) {
    if (t < 0 || b >= 1.0f) {
        return a;
    }

    return a + (b - a) * t;
}

float bicudo::length(const bicudo::vec2 &vec) {
    return sqrtf(vec.x * vec.x + vec.y * vec.y);
}

bicudo::vec2 bicudo::normalize(const bicudo::vec2 &vec) {
    float l {bicudo::length(vec)};
    if (l != 0) {
        l = 1.0f / l;
    }

    return {vec.x * l, vec.y * l};
}

void bicudo::orthographic(float* m, float left, float right, float bottom, float top) {
    const float min_depth = -1.0f;
    const float max_depth = 1.0f;
    const float invz = 1.0f / (max_depth - min_depth);
    const float invy = 1.0f / (top - bottom);
    const float invx = 1.0f / (right - left);

    m[0] = 2.0f * invx;
    m[1] = 0.0f;
    m[2] = 0.0f;
    m[3] = 0.0f;

    m[4] = 0.0f;
    m[5] = 2.0f * invy;;
    m[6] = 0.0f;
    m[7] = 0.0f;

    m[8] = 0.0f;
    m[9] = 0.0f;
    m[10] = -2.0f * invz;
    m[11] = 0.0f;
    
    m[12] = -(right + left) * invx;
    m[13] = -(top + bottom) * invy;
    m[14] = -(max_depth + min_depth) * invz;
    m[15] = 1.0f;
}