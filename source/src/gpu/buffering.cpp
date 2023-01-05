#include "bicudo/gpu/buffering.hpp"

uint32_t bicudo::buffering::current_buffer_prese[2] {};

void bicudo::buffering::invoke() {
    if (this->buffer_vao == 0) {
        glGenBuffers(1, &this->buffer_vao);
    }

    glBindVertexArray(this->buffer_vao);
}

void bicudo::buffering::bind(const bicudo::vec2 &buffer_type) {
    int32_t v1 {static_cast<int32_t>(buffer_type.x)};
    int32_t v2 {static_cast<int32_t>(buffer_type.y)};
    uint32_t buffer {};

    if (v1 == GL_ELEMENT_ARRAY_BUFFER) {
        if (this->buffer_ebo == 0) glGenBuffers(1, &this->buffer_ebo);
        buffer = this->buffer_ebo;
    } else {
        if (this->buffer_list_size >= this->buffer_list.size()) glGenBuffers(1, &this->buffer_list.emplace_back());
        buffer = this->buffer_list.at(this->buffer_list_size);
    }

    glBindBuffer(v1, buffer);

    bicudo::buffering::current_buffer_preset[0] = v1;
    bicudo::buffering::current_buffer_preset[1] = v2;
}

void bicudo::buffering::send(int32_t size, void *p_data, int32_t gl_driver_read_mode) {
    glBufferData(bicudo::buffering::current_buffer_preset[0], size, p_data, gl_driver_read_mode);
}

void bicudo::buffering::attach(uint32_t location, int32_t vec, const bicudo::vec2 &shader_stride) {
    int32_t v1 {static_cast<int32_t>(shader_stride.x)};
    int32_t v2 {static_cast<int32_t>(shader_stride.y)};

    glEnableVertexAttribArray(location);
    glVertexAttribPointer(location, vec, bicudo::buffering::current_buffer_preset[1], GL_FALSE, v1, (void*) v2);
}

void bicudo::buffering::revoke() {
    glBindVertexArray(0);
}

void bicudo::buffering::draw() {
    // todo add instanced drawing func/feature

    if (this->buffer_ebo != 0) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->buffer_ebo);

        if (this->instanced) {
        } else {
            glDrawElements(this->primitive, this->stride[1], GL_UNSIGNED_INT, (void*) 0);
        }
    } else {
        if (this->instanced) {
        } else {
            glDrawArrays(this->primitive, this->stride[0], this->stride[1]);
        }
    }
}

void bicudo::buffering::compile_mesh(bicudo::mesh &mesh) {
    this->invoke();
    if (mesh.get_uint_list()) {};
    this->revoke();
}
