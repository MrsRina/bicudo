#include "bicudo/graphics/gpubuffer.hpp"

void bicudo::gpubuffer::set_mesh(bicudo::mesh &mesh) {
    std::vector<float> &v {mesh.get_float_vector(bicudo::layout::position)};
    std::vector<float> &t {mesh.get_float_vector(bicudo::layout::texcoord)};
    std::vector<float> &n {mesh.get_float_vector(bicudo::layout::position)};
    std::vector<uint32_t> &i {mesh.get_uint_vector()};
}

void bicudo::gpubuffer::set_primitive(bicudo::primitive _primitive) {
    this->primitive = _primitive;
}

void bicudo::gpubuffer::bind(uint32_t key, bicudo::buffer) {
    uint32_t &buffer {this->buffer_map[key]};
    if (!buffer) {
        glGenBuffers(1, &buffer);
    }

    switch (type) {
    case bicudo::buffer::array:
        break;
    }
}

void bicudo::gpubuffer::edit(void *pdata, const bicudo::vec2 &) {

}

void bicudo::gpubuffer::unbind(uint32_t) {

}