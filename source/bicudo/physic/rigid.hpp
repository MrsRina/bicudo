#ifndef BICUDO_PHYSIC_RIGID_H
#define BICUDO_PHYSIC_RIGID_H

#include "../util/math.hpp"

namespace bicudo {
    class rigid {
    public:
        bicudo::vec2 position {};
        bicudo::vec2 velocity {};
        bicudo::vec2 acceleration {};
        bicudo::vec2 size {};

        float angular_angle {};
        float angular_velocity {};
        float angular_acceleration {};

        bicudo::vec2 vertices[4];
        bicudo::vec2 normals[4];

        void move(float x, float y);
        void rotate(float angle);
        void on_update();
    };
}

#endif