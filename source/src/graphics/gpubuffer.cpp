#include "bicudo/graphics/gpubuffer.hpp"

void bicudo::gpubuffer::set_mesh(bicudo::mesh &mesh) {
    std::vector<float> &v {mesh.get_float_vector(bicudo::layout::position)};
    std::vector<float> &t {mesh.get_float_vector(bicudo::layout::texcoord)};
    std::vector<float> &n {mesh.get_float_vector(bicudo::layout::position)};
    std::vector<uint32_t> &i {mesh.get_uint_vector()};

    this->invoke();

    if (!v.empty()) {
        this->bind(0, bicudo::buffer::array);
        this->send(sizeof(float) * v.size(), v.data(), true);
        this->attach(mesh.get_float_key(bicudo::layout::position), 2, bicudo::primitive::float32, {0, 0});
    }

    this->revoke();
}

void bicudo::gpubuffer::set_primitive(bicudo::primitive _primitive) {
    this->primitive = _primitive;
}

void bicudo::gpubuffer::set_index_primitive(bicudo::primitive _primitive) {
    this->index_primitive = _primitive;
}

void bicudo::gpubuffer::bind(uint32_t key, bicudo::buffer _working_buffer) {
    uint32_t &buffer {this->buffer_map[key]};
    if (!buffer) {
        glGenBuffers(1, &buffer);
    }

    switch (_working_buffer) {
    case bicudo::buffer::index:
        this->element_buffer_key = key;
        this->indexing_rendering_enabled = true;
        break;
    default:
        break;
    }

    glBindBuffer(static_cast<uint32_t>(_working_buffer), key);
    this->buffer_bind = _working_buffer;
    this->bind_on = true;
}

void bicudo::gpubuffer::send(int64_t data_size, void *p_data, bool immutable_draw) {
    glBufferData(static_cast<uint32_t>(this->buffer_bind), data_size, p_data, immutable_draw ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
}

void bicudo::gpubuffer::edit(void *p_data, const bicudo::vec2 &stride) {
    glBufferSubData(static_cast<uint32_t>(this->buffer_bind), static_cast<int64_t>(stride.x), static_cast<int64_t>(stride.y), p_data);
}

void bicudo::gpubuffer::attach(uint32_t layout_binding_slot, uint32_t vec_size, bicudo::primitive _primitive, const bicudo::vec2 &stride) {
    glEnableVertexAttribArray(layout_binding_slot);
    glVertexAttribPointer(layout_binding_slot, (uint32_t) _primitive, vec_size, false, static_cast<int64_t>(stride.x), (void*) (static_cast<int64_t>(stride.y)));
}

void bicudo::gpubuffer::unbind() {
    glBindBuffer(static_cast<uint32_t>(this->buffer_bind), 0);
    this->bind_on = false;
}

void bicudo::gpubuffer::free_memory(uint32_t key) {
    if (!this->buffer_map.count(key)) return;
    if (this->buffer_map[key]) glDeleteBuffers(1, &this->buffer_map[key]);
    this->indexing_rendering_enabled = key == this->element_buffer_key ? false : this->indexing_rendering_enabled;
    this->buffer_map.erase(key);
}

void bicudo::gpubuffer::free_all_memory() {
    for (auto it = this->buffer_map.begin(); it != this->buffer_map.end(); it = it = std::next(it)) {
        if (it->second) glDeleteBuffers(1, &it->second);
    }
    
    this->indexing_rendering_enabled = false;
    this->buffer_map.clear();
}

void bicudo::gpubuffer::invoke() {
    if (!this->vertex_arrays_object) glGenVertexArrays(1, &this->vertex_arrays_object);
    glBindVertexArray(this->vertex_arrays_object);
}

void bicudo::gpubuffer::revoke() {
    glBindVertexArray(0);
}

uint32_t bicudo::gpubuffer::get_gpu_reference(uint32_t key) {
    return this->buffer_map[key];
}