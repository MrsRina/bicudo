#ifndef BICUDO_API_GEOMETRY_RECT_H
#define BICUDO_API_GEOMETRY_RECT_H

#include "bicudo/utils/math.hpp"

namespace bicudo {
    struct rect {
        vec2 top {0, 0},
             bottom {0, 0},
             left {0, 0},
             right {0, 0};
    };
}

#endif