#ifndef BICUDO_API_SURFACE_H
#define BICUDO_API_SURFACE_H

#include "bicudo/api/feature/feature.hpp"
#include "bicudo/api/geometry/rect.hpp"

namespace bicudo {
    class surface : public bicudo::feature {
    public:
        bicudo::rect rect {};
    };
}

#endif