#include "rigid2d.h"
#include "api/client/instance.h"

rigid2d::rigid2d(math::vec2 center_vec, float w, float h) {
    this->set_type(rigid::type::RIGID2D);
    this->set_visibility_flag(util::visibility::LOW_PRIORITY);

    this->center = center_vec;
    this->width = w;
    this->height = h;

    this->reload();
    bicudo::service_physic().add((ifeature*) this);
}

void rigid2d::on_update_gravity() {
    abstract_rigid::on_update_gravity();
}

void rigid2d::on_update_position() {
    abstract_rigid::on_update_position();
}

uint8_t rigid2d::get_vertex_count() {
    return this->vertex_count;
}

uint8_t rigid2d::get_edge_count() {
    return this->edge_count;
}

void rigid2d::project_to_axis(math::vec2 &axis, float &min, float &max) {
}

void rigid2d::on_center_calc() {
    abstract_rigid::on_center_calc();
}

void rigid2d::set_pos(math::vec2 center_pos) {
    this->center = center_pos;
    this->reload();
}

math::vec2 &rigid2d::get_pos() {
    return this->center;
}

void rigid2d::reload() {
    this->vertex[0] = math::vec2(this->center.x - this->width / 2.0f, this->center.y - this->height / 2.0f);
    this->vertex[1] = math::vec2(this->center.x + this->width / 2.0f, this->center.y - this->height / 2.0f);
    this->vertex[2] = math::vec2(this->center.x + this->width / 2.0f, this->center.y + this->height / 2.0f);
    this->vertex[3] = math::vec2(this->center.x - this->width / 2.0f, this->center.y + this->height / 2.0f);

    this->face_normalized[0] = (this->vertex[1] - this->vertex[2]).normalize();
    this->face_normalized[1] = (this->vertex[2] - this->vertex[3]).normalize();
    this->face_normalized[2] = (this->vertex[3] - this->vertex[0]).normalize();
    this->face_normalized[3] = (this->vertex[0] - this->vertex[1]).normalize();
}

void rigid2d::set_mass(float val_mass) {

}

float rigid2d::get_mass() {
    return this->mass;
}

void rigid2d::move(math::vec2 vec) {
    for (uint8_t i = 0; i < 4; i++) {
        this->vertex[i] += vec;
    }

    this->center += vec;
}

void rigid2d::rotate(float val_angle) {
    this->angle += val_angle;

    for (uint8_t i = 0; i < 4; i++) {
        this->vertex[i] = this->vertex[i].rotate(this->center, angle);
    }

    this->face_normalized[0] = (this->vertex[1] - this->vertex[2]).normalize();
    this->face_normalized[1] = (this->vertex[2] - this->vertex[3]).normalize();
    this->face_normalized[2] = (this->vertex[3] - this->vertex[0]).normalize();
    this->face_normalized[3] = (this->vertex[0] - this->vertex[1]).normalize();
}

void rigid2d::find_support_point(math::vec2 dir, math::vec2 edge) {
    math::vec2 to_edge;
    float projection;

    geometry::support_info.dist = -99999;
    geometry::support_info.point = math::vec2(0, 0);
    geometry::support_info.flag = false;

    for (auto &v : this->vertex) {
        to_edge = v - edge;
        projection = to_edge.dot(dir);

        if (projection > 0 && projection > geometry::support_info.dist) {
            geometry::support_info.point = v;
            geometry::support_info.dist = projection;
            geometry::support_info.flag = true;
        }
    }
}

bool rigid2d::find_axis_least_penetration(rigid2d *&r, geometry::concurrent_collision_info &collision_info) {
    math::vec2 n, support_point;
    float best_dist;
    uint8_t best_index = 0;
    bool flag_has_support = true;

    uint8_t i = 0;

    while (flag_has_support && i < 4) {
        n = this->face_normalized[i];

        math::vec2 dir = n * -1;
        math::vec2 edge = this->vertex[i];

        r->find_support_point(dir, edge);
        flag_has_support = geometry::support_info.flag;

        if (flag_has_support && geometry::support_info.dist < best_dist) {
            best_dist = geometry::support_info.dist;
            best_index = i;
            support_point = geometry::support_info.point;
        }

        i += 1;
    }

    if (flag_has_support) {
        math::vec2 best_vec = this->face_normalized[best_index] * best_dist;
        collision_info.set(best_dist, this->face_normalized[best_index], support_point + best_vec);
    }

    return flag_has_support;
}