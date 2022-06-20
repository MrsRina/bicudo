#pragma once
#include "api/util/util.h"

#ifndef PHYSIC_RIGID_H
#define PHYSIC_RIGID_H

namespace geometry {
    struct concurrent_collision_info {
        float depth;
        math::vec2 normal = math::vec2(0, 0);
        math::vec2 start = math::vec2(0, 0);
        math::vec2 end = math::vec2(0, 0);

        void change_dir() {
            this->normal *= -1;
            math::vec2 n = this->start;
            this->start = this->end;
            this->end = n;
        }

        void set(float val_depth, math::vec2 vec_normal, math::vec2 vec_start) {
            this->depth = val_depth;
            this->normal = vec_normal;
            this->start = vec_start;
            this->end = vec_start + vec_normal * val_depth;
        }
    };

    struct {
        float depth;
        math::vec2 normal = math::vec2(0, 0);
        math::vec2 start = math::vec2(0, 0);
        math::vec2 end = math::vec2(0, 0);

        void change_dir() {
            normal *= -1;
            math::vec2 n = start;
            start = end;
            end = n;
        }

        void set(float val_depth, math::vec2 vec_normal, math::vec2 vec_start) {
            depth = val_depth;
            normal = vec_normal;
            start = vec_start;
            end = vec_start + vec_normal * val_depth;
        }
    } collision_info;

    struct {
        math::vec2 point;
        float projection;
        float dist;
        bool flag;
    } support_info;
}

namespace rigid {
    const static math::vec2 GRAVITY = {0.0f, 5.0f};
    const static float INERTIA = 12;

    enum type {
        RIGID2D, RIGID3D, CIRCLE, BODY
    };

    float interval_dist(float min_a, float max_a, float min_b, float max_b);
}

#endif