#include "rigid2d.h"
#include "api/client/instance.h"

rigid2d::rigid2d(math::vec2 center_vec, float val_mass, float val_friction, float val_restitution, float w, float h) {
    this->set_type(rigid::type::RIGID2D);
    this->set_visibility_flag(util::visibility::LOW_PRIORITY);

    this->center = center_vec;
    this->mass = val_mass;
    this->inertia = 0;
    this->friction = val_friction;
    this->restituion = val_restitution;
    this->width = w;
    this->height = h;

    this->velocity = math::vec2(0, 0);
    this->acceleration = math::vec2(0, 0);

    if (this->mass != 0.0f) {
        this->mass = 1.0f / this->mass;
        this->acceleration = rigid::GRAVITY;
    }

    this->angle = 0.0f;
    this->angular_velocity = 0.0f;
    this->angular_acceleration = 0.0f;
    this->bound_radius = 0.0f;

    this->vertex[0] = math::vec2(this->center.x - this->width / 2.0f, this->center.y - this->height / 2.0f);
    this->vertex[1] = math::vec2(this->center.x + this->width / 2.0f, this->center.y - this->height / 2.0f);
    this->vertex[2] = math::vec2(this->center.x + this->width / 2.0f, this->center.y + this->height / 2.0f);
    this->vertex[3] = math::vec2(this->center.x - this->width / 2.0f, this->center.y + this->height / 2.0f);

    this->face_normalized[0] = (this->vertex[1] - this->vertex[2]).normalize();
    this->face_normalized[1] = (this->vertex[2] - this->vertex[3]).normalize();
    this->face_normalized[2] = (this->vertex[3] - this->vertex[0]).normalize();
    this->face_normalized[3] = (this->vertex[0] - this->vertex[1]).normalize();

    this->update_inertia();
    bicudo::service_physic().add((ifeature*) this);
}

void rigid2d::on_update_gravity() {
    abstract_rigid::on_update_gravity();
}

void rigid2d::on_update_position() {
    abstract_rigid::on_update_position();

    this->velocity += this->acceleration * util::timing->locked_delta_time;
    this->move(this->velocity * util::timing->locked_delta_time);

    this->angular_velocity += this->angular_acceleration * util::timing->locked_delta_time;
    this->rotate(this->angular_velocity * util::timing->locked_delta_time);
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

    this->vertex[0] = math::vec2(this->center.x - this->width / 2.0f, this->center.y - this->height / 2.0f);
    this->vertex[1] = math::vec2(this->center.x + this->width / 2.0f, this->center.y - this->height / 2.0f);
    this->vertex[2] = math::vec2(this->center.x + this->width / 2.0f, this->center.y + this->height / 2.0f);
    this->vertex[3] = math::vec2(this->center.x - this->width / 2.0f, this->center.y + this->height / 2.0f);

    this->face_normalized[0] = (this->vertex[1] - this->vertex[2]).normalize();
    this->face_normalized[1] = (this->vertex[2] - this->vertex[3]).normalize();
    this->face_normalized[2] = (this->vertex[3] - this->vertex[0]).normalize();
    this->face_normalized[3] = (this->vertex[0] - this->vertex[1]).normalize();
}

math::vec2 &rigid2d::get_pos() {
    return this->center;
}

void rigid2d::update_mass(float delta) {
    float val_mass = 0.0f;

    if (this->mass != 0) {
        val_mass = 1.0f / this->mass;
    }

    val_mass += delta;

    if (val_mass <= 0) {
        this->mass = 0;
        this->velocity = math::vec2(0, 0);
        this->acceleration = math::vec2(0, 0);
        this->angular_velocity = 0.0f;
        this->angular_acceleration = 0.0f;
    } else {
        this->mass = 1.0f / val_mass;
        this->acceleration = rigid::GRAVITY;
    }

    this->update_inertia();
}

void rigid2d::update_inertia() {
    if (this->mass == 0) {
        this->inertia = 0.0f;
    } else {
        this->inertia = (1.0F / this->mass) * (this->width * this->width + this->height * this->height) / rigid::INERTIA;
        this->inertia = 1.0f / this->inertia;
    }
}

void rigid2d::move(math::vec2 vec) {
    for (uint8_t i = 0; i < 4; i++) {
        this->vertex[i] = this->vertex[i] + vec;
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
    float best_dist = 99999;
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