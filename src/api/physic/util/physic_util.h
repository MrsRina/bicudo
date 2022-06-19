#pragma once
#include "api/util/util.h"

#ifndef PHYSIC_RIGID_H
#define PHYSIC_RIGID_H

namespace geometry {
    struct vertex {
        vertex();

        math::vec2 position, previous_position, acceleration;
        float original_length {};
    };

    struct edge {
        edge() {};

        vertex* v1;
        vertex* v2;

        float original_length;
    };

    struct {
        float depth;
        math::vec2 normal;

        edge* e;
        vertex* v;
    } collision_info;
}

namespace rigid {
    const static math::vec2 gravity = {0.0f, 1000.0f};

    enum type {
        RIGID2D, RIGID3D, CIRCLE, BODY
    };

    float interval_dist(float min_a, float max_a, float min_b, float max_b);
}

#endif