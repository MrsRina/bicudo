#include "bicudo/physic/rigid.hpp"
#include "bicudo/bicudo.hpp"

void bicudo::rigid::move(float x, float y) {
    float w {this->size.x / 2};
    float h {this->size.y / 2};

    /* Align the center position with size dimension of rigid rectangle. */
    this->vertices[0].x = x - w;
    this->vertices[0].y = y - h;
    this->vertices[1].x = x + w;
    this->vertices[1].y = y - h;
    this->vertices[2].x = x + w;
    this->vertices[2].y = y + h;
    this->vertices[3].x = x - w;
    this->vertices[3].y = y + h;

    /* Calculate the normals direction of all faces. */
    this->normals[0] = bicudo::normalize(this->vertices[0] - this->vertices[1]);
    this->normals[1] = bicudo::normalize(this->vertices[1] - this->vertices[2]);
    this->normals[2] = bicudo::normalize(this->vertices[2] - this->vertices[3]);
    this->normals[3] = bicudo::normalize(this->vertices[3] - this->vertices[0]);
}

void bicudo::rigid::rotate(float angle) {
    this->angular_angle += angle;

    this->vertices[0] = bicudo::rotate(this->vertices[0], this->angular_angle, this->position);
    this->vertices[1] = bicudo::rotate(this->vertices[1], this->angular_angle, this->position);
    this->vertices[2] = bicudo::rotate(this->vertices[2], this->angular_angle, this->position);
    this->vertices[3] = bicudo::rotate(this->vertices[3], this->angular_angle, this->position);

    this->normals[0] = bicudo::normalize(this->vertices[0] - this->vertices[1]);
    this->normals[1] = bicudo::normalize(this->vertices[1] - this->vertices[2]);
    this->normals[2] = bicudo::normalize(this->vertices[2] - this->vertices[3]);
    this->normals[3] = bicudo::normalize(this->vertices[3] - this->vertices[0]);
}

void bicudo::rigid::on_update() {
    float dt {bicudo::kernel::p_core->delta};

    this->velocity += this->acceleration * dt;
    bicudo::vec2 motion {this->position + this->velocity * dt};
    this->move(motion.x, motion.y);

    this->angular_velocity += this->angular_acceleration * dt;
    float angular_motion {this->angular_angle + this->angular_velocity * dt};
    this->rotate(angular_motion);
}
