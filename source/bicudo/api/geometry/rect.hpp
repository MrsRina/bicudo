#ifndef BICUDO_API_GEOMETRY_RECT_H
#define BICUDO_API_GEOMETRY_RECT_H

#include "bicudo/api/util/math.hpp"

namespace bicudo {
    struct rect {
        bicudo::vec2 top {}, bottom {}, left {}, right {};
    };
}

#endif