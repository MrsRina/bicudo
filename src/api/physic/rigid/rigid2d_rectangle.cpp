#include "api/client/instance.h"

rigid2d_rectangle::rigid2d_rectangle(math::vec2 vec_center, float val_mass, float val_friction, float val_restitution, float width, float height) {
    this->type = rigidutil::type::RIGID2D_RECTANGLE;
    this->physic = rigidutil::physic::FULL;

    this->center = vec_center;
    this->friction = val_friction;
    this->restitution = val_restitution;
    this->w = width < 0.1f ? 1.0f : width;
    this->h = height < 0.1f ? 1.0f : height;
    this->mass = val_mass;
    this->inertia = 0.0f;
    this->acceleration = math::vec2(0, 0);
    this->velocity = math::vec2(0, 0);
    this->angle = 0;
    this->angular_velocity = 0.0f;
    this->angular_acceleration = 0.0f;

    if (this->mass != 0.0f) {
        this->mass = 1.0f / this->mass;
        this->acceleration = GLOBAL_WORLD_2D_GRAVITY;
    }

    this->vertices[0] = math::vec2(this->center.x - this->w / 2.0f, this->center.y - this->h / 2.0f);
    this->vertices[1] = math::vec2(this->center.x + this->w / 2.0f, this->center.y - this->h / 2.0f);
    this->vertices[2] = math::vec2(this->center.x + this->w / 2.0f, this->center.y + this->h / 2.0f);
    this->vertices[3] = math::vec2(this->center.x - this->w / 2.0f, this->center.y + this->h / 2.0f);

    this->edges_normalised[0] = (this->vertices[1] - this->vertices[2]).normalize();
    this->edges_normalised[1] = (this->vertices[2] - this->vertices[3]).normalize();
    this->edges_normalised[2] = (this->vertices[3] - this->vertices[0]).normalize();
    this->edges_normalised[3] = (this->vertices[0] - this->vertices[1]).normalize();

    this->update_inertia();
    bicudo::service_physic().add_rigid2d(this);
}

void rigid2d_rectangle::on_update_position() {
    rigid2d::on_update_position();

    this->acceleration = this->mass <= 0 ? math::zero2f : GLOBAL_WORLD_2D_GRAVITY;

    // [x, y] p = p + v + acc * dt * dt
    this->velocity += this->acceleration * util::timing::locked_delta_time;
    this->move(this->velocity * util::timing::locked_delta_time);

    // val_angle = val_angle + angular_v + angular_acc * dt * dt
    this->angular_velocity += this->angular_acceleration * util::timing::locked_delta_time;
    this->rotate(this->angular_velocity * util::timing::locked_delta_time);
}

void rigid2d_rectangle::move(math::vec2 vec_vel) {
    rigid2d::move(vec_vel);

    this->minx = 10000.0f;
    this->miny = 10000.0f;
    this->maxx = -10000.0f;
    this->maxy = -10000.0f;

    for (auto &vertex : this->vertices) {
        vertex += vec_vel;

        this->minx = std::min(this->minx, vertex.x);
        this->miny = std::min(this->miny, vertex.y);
        this->maxx = std::max(this->maxx, vertex.x);
        this->maxy = std::max(this->maxy, vertex.y);
    }

    this->center += vec_vel;
}

void rigid2d_rectangle::rotate(float val_angle) {
    this->angle += val_angle;

    for (auto &vertex : this->vertices) {
        vertex = vertex.rotate(this->center, val_angle);
    }

    this->edges_normalised[0] = (this->vertices[1] - this->vertices[2]).normalize();
    this->edges_normalised[1] = (this->vertices[2] - this->vertices[3]).normalize();
    this->edges_normalised[2] = (this->vertices[3] - this->vertices[0]).normalize();
    this->edges_normalised[3] = (this->vertices[0] - this->vertices[1]).normalize();
}

void rigid2d_rectangle::find_support_point(math::vec2 dir, math::vec2 vert) {
    math::vec2 to_edge;
    float projection;

    geometry::support_info::dist = -99999.0f;
    geometry::support_info::point = math::vec2(0, 0);
    geometry::support_info::flag = false;

    for (auto &vertex : this->vertices) {
        to_edge = vertex - vert;
        projection = to_edge.dot(dir);

        if (projection > 0 && projection > geometry::support_info::dist) {
            geometry::support_info::point = vertex;
            geometry::support_info::dist = projection;
            geometry::support_info::flag = true;
        }
    }
}

bool rigid2d_rectangle::find_axis_least_penetration(rigid2d_rectangle *&r, geometry::concurrent_collision_info &collision_info) {
    math::vec2 n, support_point;
    uint8_t best_index = 0;
    float best_dist = 99999;
    bool flag_has_support = true;

    math::vec2 dir;
    math::vec2 vert;

    uint8_t i = 0;

    while (flag_has_support && i < 4) {
        n = this->edges_normalised[i];
        dir = n * -1.0f;
        vert = this->vertices[i];

        r->find_support_point(dir, vert);
        flag_has_support = geometry::support_info::flag;

        if (flag_has_support && geometry::support_info::dist < best_dist) {
            best_dist = geometry::support_info::dist;
            best_index = i;
            support_point = geometry::support_info::point;
        }

        i++;
    }

    if (flag_has_support) {
        math::vec2 best_edge = this->edges_normalised[best_index] * best_dist;
        collision_info.set(best_dist, this->edges_normalised[best_index], support_point + best_edge);
    }

    return flag_has_support;
}

math::vec2* rigid2d_rectangle::get_vertices() {
    return this->vertices;
}

math::vec2 *rigid2d_rectangle::get_edges_normalised() {
    return this->edges_normalised;
}

void rigid2d_rectangle::update_mass(float delta) {
    float val_mass = 0.0f;

    if (this->mass != 0) {
        val_mass = 1.0f / this->mass;
    }

    val_mass += delta;

    if (val_mass <= 0) {
        this->mass = 0.0f;
        this->velocity = math::vec2(0.0f, 0.0f);
        this->acceleration = math::vec2(0.0f, 0.0f);
        this->angular_velocity = 0.0f;
        this->angular_acceleration = 0.0f;
    } else {
        this->mass = 1 / val_mass;
        this->acceleration = GLOBAL_WORLD_2D_GRAVITY;
    }

    this->update_inertia();
}

void rigid2d_rectangle::update_inertia() {
    if (this->mass == 0) {
        this->inertia = 0.0f;
    } else {
        this->inertia = (1.0f / this->mass) * (this->w * this->w + this->h * this->h) / rigidutil::INERTIA;
        this->inertia = 1.0f / this->inertia;
    }
}
