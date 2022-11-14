#ifndef BICUDO_API_RIGID_H
#define BICUDO_API_RIGID_H

#include "bicudo/api/feature/feature.hpp"
#include "bicudo/api/util/math.hpp"

namespace bicudo {
    class rigid : public bicudo::feature {
    protected:
        bicudo::vec2 vertexes[4] {}, normals[4] {};
    public:
        bicudo::vec2 pos {}, size {}, acceleration {}, velocity {};
        float angular_acceleration {};

        void on_update();
    };
}

#endif