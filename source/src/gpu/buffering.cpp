#include "bicudo/gpu/buffering.hpp"
#include "bicudo/api/util/log.hpp"

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
    glVertexAttribPointer(location, offset, GL_FLOAT, GL_FALSE, begin, (void*) end);
}

void bicudo::buffering::send_data(uint32_t size, void *data, bicudo::datatype data_gl_reader) {
    glBufferData(GL_ARRAY_BUFFER, size, data, data_gl_reader);
}

void bicudo::buffering::draw() {
    glBindVertexArray(this->gpu_buffer_group);
    // todo: add element buffer object (indexing rendering)
    glDrawArrays(this->draw_mode, this->stride_begin, this->stride_end);
    glBindVertexArray(0);
}

void bicudo::buffering::bind_buffer() {
    if (this->buffer_list.size() >= this->buffer_index) {
        this->buffer_list.emplace_back();
        glGenBuffers(1, &this->buffer_list[this->buffer_index]);
    }

    glBindBuffer(GL_ARRAY_BUFFER, this->buffer_list[this->buffer_index++]);
}

void bicudo::buffering::compile_mesh(bicudo::mesh &mesh) {
    this->stride_begin = 0;
    this->stride_end = static_cast<int32_t>(mesh.vertices.size()) / mesh.per_vertices_length;

    if (!mesh.vertices.empty()) {
        this->bind_buffer();
        this->send_data(sizeof(float) * mesh.vertices.size(), mesh.vertices.data(), bicudo::datatype::immutable);
        this->set_shader_location(0, mesh.per_vertices_length, 0, 0);
    }

    if (!mesh.uvs.empty()) {
        this->bind_buffer();
        this->send_data(sizeof(float) * mesh.uvs.size(), mesh.uvs.data(), bicudo::datatype::immutable);
        this->set_shader_location(1, mesh.per_uvs_length, 0, 0);
    }

    if (!mesh.normals.empty()) {
        this->bind_buffer();
        this->send_data(sizeof(float) * mesh.normals.size(), mesh.normals.data(), bicudo::datatype::immutable);
        this->set_shader_location(2, mesh.per_normals_length, 0, 0);
    }
}
