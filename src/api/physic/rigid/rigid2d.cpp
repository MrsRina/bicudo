#include "rigid2d.h"
#include "api/client/instance.h"

rigid2d::rigid2d(math::vec2 center_vec, float w, float h) {
    this->set_type(rigid::type::RIGID2D);
    this->set_visibility_flag(util::visibility::LOW_PRIORITY);

    this->vertex_count = 4;
    this->edge_count = 4;

    this->center = center_vec;
    this->width = w;
    this->height = h;

    for (uint8_t i = 0; i < this->get_vertex_count(); i++) {
        this->vertices[i] = new geometry::vertex();
    }

    for (uint8_t i = 0; i < this->get_edge_count(); i++) {
        this->edges[i] = new geometry::edge();
    }

    this->reload();
    BICUDO->get_physic_manager().add((ifeature*)  this);
}

void rigid2d::on_update_gravity() {
    abstract_rigid::on_update_gravity();

    for (uint8_t i = 0; i < this->get_vertex_count(); i++) {
        this->vertices[i]->acceleration += rigid::gravity;
    }
}

void rigid2d::on_update_position() {
    abstract_rigid::on_update_position();

    for (uint8_t i = 0; i < this->get_vertex_count(); i++) {
        geometry::vertex* v = this->vertices[i];
        math::vec2 temp = v->position;

        v->position += v->position - v->previous_position + v->acceleration * util::timing->locked_delta_time * util::timing->locked_delta_time;
        v->previous_position = temp;
    }
}

uint8_t rigid2d::get_vertex_count() {
    return this->vertex_count;
}

uint8_t rigid2d::get_edge_count() {
    return this->edge_count;
}

geometry::vertex** rigid2d::get_vertices() {
    return this->vertices;
}

geometry::edge** rigid2d::get_edges() {
    return this->edges;
}

void rigid2d::project_to_axis(math::vec2 &axis, float &min, float &max) {
    float dot_p = axis * this->vertices[0]->position;
    min = max = dot_p;

    for (uint8_t i = 0; i < this->get_vertex_count(); i++) {
        dot_p = axis * vertices[i]->position;

        min = std::min(dot_p, min);
        max = std::max(dot_p, max);
    }
}

void rigid2d::set_pos(math::vec2 center_pos) {
    this->center = center_pos;
    this->reload();
}

math::vec2 &rigid2d::get_pos() {
    return this->center;
}

void rigid2d::reload() {
    this->vertices[0]->position = math::vec2(this->center.x - this->width / 2.0f, this->center.y - this->height / 2.0f);
    this->vertices[1]->position = math::vec2(this->center.x + this->width / 2.0f, this->center.y - this->height / 2.0f);
    this->vertices[2]->position = math::vec2(this->center.x + this->width / 2.0f, this->center.y + this->height / 2.0f);
    this->vertices[3]->position = math::vec2(this->center.x - this->width / 2.0f, this->center.y + this->height / 2.0f);

    this->edges[0]->v1 = this->vertices[0];
    this->edges[0]->v2 = this->vertices[1];
    this->edges[0]->original_length = (this->edges[0]->v2->position - this->edges[0]->v1->position).length();

    this->edges[1]->v1 = this->vertices[1];
    this->edges[1]->v2 = this->vertices[2];
    this->edges[1]->original_length = (this->edges[1]->v2->position - this->edges[1]->v1->position).length();

    this->edges[2]->v1 = this->vertices[2];
    this->edges[2]->v2 = this->vertices[3];
    this->edges[2]->original_length = (this->edges[2]->v2->position - this->edges[2]->v1->position).length();

    this->edges[3]->v1 = this->vertices[3];
    this->edges[3]->v2 = this->vertices[0];
    this->edges[3]->original_length = (this->edges[3]->v2->position - this->edges[3]->v1->position).length();
}