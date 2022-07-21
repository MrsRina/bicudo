#include "physic_util.h"

float geometry::collision_info::depth;
math::vec2 geometry::collision_info::normal;
math::vec2 geometry::collision_info::start;
math::vec2 geometry::collision_info::end;

math::vec2 geometry::support_info::point;
float geometry::support_info::projection;
float geometry::support_info::dist;
bool geometry::support_info::flag;

float rigidutil::interval_dist(float min_a, float max_a, float min_b, float max_b) {
    if (min_a < min_b) {
        return min_b - max_a;
    } else {
        return min_a - max_b;
    }

    return 0;
}

void geometry::collision_info::set(float val_depth, math::vec2 vec_normal, math::vec2 vec_start) {
    depth = val_depth;
    normal = vec_normal;
    start = vec_start;
    end = vec_start + vec_normal * val_depth;
}

void geometry::collision_info::change_dir() {
    normal *= -1;
    math::vec2 n = start;
    start = end;
    end = n;
}

void geometry::concurrent_collision_info::change_dir() {
    this->normal *= -1;
    math::vec2 n = this->start;
    this->start = this->end;
    this->end = n;
}

void geometry::concurrent_collision_info::set(float val_depth, math::vec2 vec_normal, math::vec2 vec_start) {
    this->depth = val_depth;
    this->normal = vec_normal;
    this->start = vec_start;
    this->end = vec_start + vec_normal * val_depth;
}
