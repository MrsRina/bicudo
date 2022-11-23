#include "bicudo/api/rigid/rigid.hpp"
#include "bicudo/bicudo.hpp"

void bicudo::rigid::on_update() {
    this->velocity += this->acceleration * bicudo::unsafe_dt;

    auto vel {this->velocity * bicudo::unsafe_dt};
    this->pos += vel;

    this->angular_velocity += this->angular_acceleration * bicudo::unsafe_dt;
    auto vel_angular {this->angular_velocity * bicudo::unsafe_dt};
    this->angle += vel_angular;

    this->max.x = -10000.0f;
    this->max.y = -10000.0f;
    this->min.x = 10000.0f;
    this->min.y = 10000.0f;

    for (auto &vertex : this->vertices) {
        vertex += vel;
        vertex = bicudo::rotate(vertex, this->pos, vel_angular);

        this->min.x = std::min(this->min.x, vertex.x);
        this->min.y = std::min(this->min.y, vertex.y);
        this->max.x = std::max(this->max.x, vertex.x);
        this->max.y = std::max(this->max.y, vertex.y);

    }

    this->update_normals();
}

void bicudo::rigid::set_size(float w, float h) {
    this->size.x = w;
    this->size.y = h;

    float dw {w / 2};
    float dh {h / 2};

    this->vertices[0].x = this->pos.x - dw;
    this->vertices[0].y = this->pos.y - dh;

    this->vertices[1].x = this->pos.x + dw;
    this->vertices[1].y = this->pos.y - dh;

    this->vertices[2].x = this->pos.x + dw;
    this->vertices[2].y = this->pos.y + dh;

    this->vertices[3].x = this->pos.x - dw;
    this->vertices[3].y = this->pos.y + dh;

    this->update_normals();
}

void bicudo::rigid::set_rotation(float amount) {
    this->angle += amount;

    this->vertices[0] = bicudo::rotate(this->vertices[0], this->pos, amount);
    this->vertices[1] = bicudo::rotate(this->vertices[1], this->pos, amount);
    this->vertices[2] = bicudo::rotate(this->vertices[2], this->pos, amount);
    this->vertices[3] = bicudo::rotate(this->vertices[3], this->pos, amount);
    this->update_normals();
}

void bicudo::rigid::update_normals() {
    this->normals[0] = bicudo::normalize(this->vertices[1] - this->vertices[2]);
    this->normals[1] = bicudo::normalize(this->vertices[2] - this->vertices[3]);
    this->normals[2] = bicudo::normalize(this->vertices[3] - this->vertices[0]);
    this->normals[3] = bicudo::normalize(this->vertices[0] - this->vertices[1]);
}

void bicudo::rigid::on_create() {
    feature::on_create();
    this->set_size(this->size.x, this->size.y);
}

void bicudo::rigid::on_destroy() {
    feature::on_destroy();
}

void bicudo::rigid::update_inertia() {
    if (this->mass == 0) {
        this->inertia = 0;
    } else {
        this->inertia = (1.0f / this->mass) * (this->size.x * this->size.x + this->size.y * this->size.y) / 12;
    }
}

void bicudo::rigid::update_mass(float delta) {
    float m {};
    if (this->mass != 0) {
        m = 1.0f / this->mass;
    }

    m += delta;
    if (m <= 0) {
        this->mass = 0;
    } else {
        this->mass = 1 / m;
    }
}

bicudo::rigid::~rigid() {

}

bicudo::rigid::rigid(const bicudo::vec2 &position, const bicudo::vec2 &dimension, float the_mass, float the_friction, float the_restitution) {
    this->pos = position - (dimension / 2);
    this->size = dimension;
    this->set_size(this->size.x, this->size.y);
    this->friction = the_friction;
    this->restitution = the_restitution;

    if (the_mass != 0) {
        this->mass = 1 / the_mass;
        this->acceleration.y = 10;
    }

    this->update_inertia();
    bicudo::core->get_physic()->append(this);
}

bicudo::vec2 *bicudo::rigid::vdata() {
    return this->vertices;
}

bicudo::vec2 *bicudo::rigid::ndata() {
    return this->normals;
}

void bicudo::rigid::update_position(bicudo::vec2 vel) {
    this->max.x = -10000.0f;
    this->max.y = -10000.0f;
    this->min.x = 10000.0f;
    this->min.y = 10000.0f;

    for (auto &vertex : this->vertices) {
        vertex += vel;

        this->min.x = std::min(this->min.x, vertex.x);
        this->min.y = std::min(this->min.y, vertex.y);
        this->max.x = std::max(this->max.x, vertex.x);
        this->max.y = std::max(this->max.y, vertex.y);
    }

    this->pos += vel;
    this->update_normals();
}
