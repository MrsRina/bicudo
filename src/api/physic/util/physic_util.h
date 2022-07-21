#pragma once
#include "api/util/util.h"

#ifndef PHYSIC_UTIL_H
#define PHYSIC_UTIL_H

namespace geometry {
    struct concurrent_collision_info {
        float depth {};
        math::vec2 normal = math::vec2(0, 0);
        math::vec2 start = math::vec2(0, 0);
        math::vec2 end = math::vec2(0, 0);

        void change_dir();
        void set(float val_depth, math::vec2 vec_normal, math::vec2 vec_start);
    };

    struct collision_info {
        static float depth;
        static math::vec2 normal;
        static math::vec2 start;
        static math::vec2 end;

        static void change_dir();
        static void set(float val_depth, math::vec2 vec_normal, math::vec2 vec_start);
    };

    struct support_info {
        static math::vec2 point;
        static float projection;
        static float dist;
        static bool flag;
    };
}

namespace rigidutil {
    const static float INERTIA = 12;

    enum type {
        RIGID2D_RECTANGLE, RIGID3D, CIRCLE, BODY
    };

    /**
     * FULL = POS ACCELERATION AND ANGULAR ACCELERATION
     * POS  = POS ACCELERATION
     **/
    enum physic {
        FULL, POS
    };

    float interval_dist(float min_a, float max_a, float min_b, float max_b);
}

#endif