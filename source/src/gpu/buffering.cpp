#include "bicudo/gpu/buffering.hpp"
#include "bicudo/api/util/log.hpp"
#include "bicudo/api/util/flag.hpp"

void bicudo::buffering::invoke() {
    if (this->gpu_buffer_group == 0) {
        glGenVertexArrays(1, &this->gpu_buffer_group);
    }

    glBindVertexArray(this->gpu_buffer_group);
}

void bicudo::buffering::revoke() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void bicudo::buffering::set_shader_location(uint32_t location, int32_t offset, int32_t begin, size_t end) {
    glEnableVertexAttribArray(location);
    glVertexAttribPointer(location, offset, this->shader_array_type, GL_FALSE, begin, (void*) end);
}

void bicudo::buffering::send_data(uint32_t size, void *data, uint16_t bflags) {
    auto buffer_type {bicudo::bitwise::contains(bflags, bicudo::buffer::vbo) ? GL_ARRAY_BUFFER : GL_ELEMENT_ARRAY_BUFFER};
    auto data_gl_reader {bicudo::bitwise::contains(bflags, bicudo::buffer::immutable) ? GL_STATIC_DRAW : (bicudo::bitwise::contains(bflags, bicudo::buffer::dynamic) ? GL_DYNAMIC_DRAW : GL_STREAM_DRAW)};
    this->shader_array_type = bicudo::bitwise::contains(bflags, bicudo::buffer::typefloat) ? GL_FLOAT : GL_UNSIGNED_INT;

    glBufferData(buffer_type, size, data, data_gl_reader);
}

void bicudo::buffering::draw() {
    glBindVertexArray(this->gpu_buffer_group);

    if (this->buffer_ebo != 0) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->buffer_ebo);
        glDrawElements(this->draw_mode, this->stride_end, GL_UNSIGNED_INT, (void*) 0);
    } else {
        glDrawArrays(this->draw_mode, this->stride_begin, this->stride_end);
    }

    glBindVertexArray(0);
}

void bicudo::buffering::bind_buffer(uint16_t bflags) {
    if (this->buffer_list.size() >= this->buffer_index) {
        this->buffer_list.emplace_back();
        glGenBuffers(1, &this->buffer_list[this->buffer_index]);
    }

    if (bicudo::bitwise::contains(bflags, bicudo::buffer::ebo)) {
        this->buffer_ebo = this->buffer_list[this->buffer_index++];
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->buffer_ebo);
    } else {
        glBindBuffer(GL_ARRAY_BUFFER, this->buffer_list[this->buffer_index++]);
    }
}

void bicudo::buffering::compile_mesh(bicudo::mesh &mesh) {
    auto &v {mesh.get_position_mesh(bicudo::meshing::vertex)};
    auto &t {mesh.get_position_mesh(bicudo::meshing::texture)};
    auto &vn {mesh.get_position_mesh(bicudo::meshing::normal)};
    auto &iv {mesh.get_index_mesh(bicudo::meshing::ivertex)};

    this->stride_begin = 0;
    this->stride_end = static_cast<int32_t>(v.size()) / mesh.get_vec_len(bicudo::meshing::vertex);

    if (!v.empty()) {
        this->bind_buffer();
        this->send_data(sizeof(float) * v.size(), v.data(), bicudo::buffer::immutable | bicudo::buffer::typefloat);
        this->set_shader_location(0, mesh.get_vec_len(bicudo::meshing::vertex), 0, 0);
    }

    if (!t.empty()) {
        this->bind_buffer();
        this->send_data(sizeof(float) * t.size(), t.data(), bicudo::buffer::immutable | bicudo::buffer::typefloat);
        this->set_shader_location(1, mesh.get_vec_len(bicudo::meshing::texture), 0, 0);
    }

    if (!vn.empty()) {
        this->bind_buffer();
        this->send_data(sizeof(float) * vn.size(), vn.data(), bicudo::buffer::immutable | bicudo::buffer::typefloat);
        this->set_shader_location(2, mesh.get_vec_len(bicudo::meshing::normal), 0, 0);
    }

    if (!iv.empty()) {
        this->indexing_rendering_size = iv.size();
        this->stride_end = this->indexing_rendering_size;
        this->bind_buffer(bicudo::buffer::ebo);
        this->send_data(sizeof(uint32_t) * this->indexing_rendering_size, iv.data(), bicudo::buffer::immutable | bicudo::buffer::typeuint);
    }
}
