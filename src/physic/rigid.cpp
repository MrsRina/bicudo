#include "bicudo/physic/rigid.hpp"
#include "bicudo/bicudo.hpp"

void bicudo::rigid::resize(float w, float h) {
    this->size.x = w;
    this->size.y = h;

    bicudo::vec2 const div = this->size / 2;
    this->vertices[0].x = this->position.x - div.x;
    this->vertices[0].y = this->position.y - div.y;
    this->vertices[1].x = this->position.x + div.x;
    this->vertices[1].y = this->position.y - div.y;
    this->vertices[2].x = this->position.x + div.x;
    this->vertices[2].y = this->position.y + div.y;
    this->vertices[3].x = this->position.x - div.x;
    this->vertices[3].y = this->position.y + div.y;

    float const previous_angle {this->angular_angle};
    this->angular_angle = 0.0f;
    this->rotate(previous_angle);
    this->update_inertia();
}

void bicudo::rigid::move(float x, float y) {
    this->vertices[0].x += x ;
    this->vertices[0].y += y ;
    this->vertices[1].x += x ;
    this->vertices[1].y += y ;
    this->vertices[2].x += x ;
    this->vertices[2].y += y ;
    this->vertices[3].x += x ;
    this->vertices[3].y += y ;

    /* Calculate the normals direction of all faces. */
    this->normals[0] = bicudo::normalize(this->vertices[0] - this->vertices[1]);
    this->normals[1] = bicudo::normalize(this->vertices[1] - this->vertices[2]);
    this->normals[2] = bicudo::normalize(this->vertices[2] - this->vertices[3]);
    this->normals[3] = bicudo::normalize(this->vertices[3] - this->vertices[0]);

    this->position.x += x;
    this->position.y += y;
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

void bicudo::rigid::update_inertia() {
    if (this->mass == 0.0f) {
        this->inertia = 0.0f;
    } else {
        this->inertia = (1.0f / this->mass) * (bicudo::magnitude(this->size)) / 12;
        this->inertia = 1.0f / this->inertia;
    }
}

void bicudo::rigid::on_update() {
    float  const  dt {bicudo::kernel::p_core->delta};

    this->velocity += this->acceleration * dt;
    const bicudo::vec2 motion {this->velocity * dt};
    this->move(motion.x, motion.y);

    this->angular_velocity += this->angular_acceleration * dt;
    const float angular_motion {this->angular_angle + this->angular_velocity * dt};
    this->rotate(angular_motion);
}
