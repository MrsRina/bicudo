#include "bicudo/graphics/stream/mesh.hpp"

void bicudo::mesh::append_float(bicudo::layout layout, const bicudo::vec2 &vec) {
    switch (layout) {
    case bicudo::layout::position:
        this->v.push_back(vec.x);
        this->v.push_back(vec.y);
        this->v_key = this->current_key;
        break;
    case bicudo::layout::texcoord:
        this->t.push_back(vec.x);
        this->t.push_back(vec.y);
        this->t_key = this->current_key;
        break;
    case bicudo::layout::normal:
        this->n.push_back(vec.x);
        this->n.push_back(vec.y);
        this->n_key = this->current_key;
        break;
    }
}

void bicudo::mesh::append_float(bicudo::layout layout, float value) {
    switch (layout) {
    case bicudo::layout::position:
        this->v.push_back(value);
        this->v_key = this->current_key;
        break;
    case bicudo::layout::texcoord:
        this->t.push_back(value);
        this->t_key = this->current_key;
        break;
    case bicudo::layout::normal:
        this->n.push_back(value);
        this->n_key = this->current_key;
        break;
    }
}

void bicudo::mesh::append_uint(uint32_t value) {
    this->i.push_back(value);
}

void bicudo::mesh::begin(uint32_t key) {
    this->current_key = key;
}

std::vector<float> &bicudo::mesh::get_float_vector(bicudo::layout layout) {
    switch (layout) {
    case bicudo::layout::position:
        return this->v;
    case bicudo::layout::texcoord:
        return this->t;
    default:
        break;
    }
    return this->n;
}

std::vector<uint32_t> &bicudo::mesh::get_uint_vector() {
    return this->i;
}

uint32_t bicudo::mesh::get_float_key(bicudo::layout layout) {
    switch (layout) {
    case bicudo::layout::position:
        return this->v_key;
    case bicudo::layout::texcoord:
        return this->t_key;
    default:
        break;
    }
    return this->n_key;
}

uint32_t bicudo::mesh::get_uint_key() {
    return this->i_key;
}