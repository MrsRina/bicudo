#include "bicudo/graphics/stream/mesh.hpp"

void bicudo::mesh::append_float(bicudo::layout layout, const bicudo::vec2 &vec) {
    switch (layout) {
    case bicudo::layout::position:
        this->v.push_back(vec.x);
        this->v.push_back(vec.y);
        break;
    case bicudo::layout::texcoord:
        this->t.push_back(vec.x);
        this->t.push_back(vec.y);
        break;
    case bicudo::layout::normal:
        this->n.push_back(vec.x);
        this->n.push_back(vec.y);
        break;
    }
}

void bicudo::mesh::append_float(bicudo::layout layout, float value) {
    switch (layout) {
    case bicudo::layout::position:
        this->v.push_back(value);
        break;
    case bicudo::layout::texcoord:
        this->t.push_back(value);
        break;
    case bicudo::layout::normal:
        this->n.push_back(value);
        break;
    }
}

void bicudo::mesh::append_uint(uint32_t value) {
    this->i.push_back(value);
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