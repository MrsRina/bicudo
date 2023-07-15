#include "bicudo/graphics/gpubuffer.hpp"
#include "bicudo/util/logger.hpp"

void bicudo::gpubuffer::set_mesh_descriptor(bicudo::meshdescriptor &mesh_descriptor) {
    if (mesh_descriptor.p_resources == nullptr) {
        bicudo::log() << "[bicudo::gpubuffer::set_mesh_descriptor] Invalid resources (p_resources is nullptr)";
        return;
    }

    this->invoke();

    if (mesh_descriptor.resource_size > 0) {
        this->bind(0, GL_ARRAY_BUFFER);
        this->send(mesh_descriptor.resource_size, mesh_descriptor.p_resources, true);
    }

    if (mesh_descriptor.attrib_pos.size > 0) {
        this->attach(mesh_descriptor.attrib_pos.location,
                     mesh_descriptor.attrib_pos.size,
                     mesh_descriptor.attrib_pos.type,
                    {static_cast<int32_t>(mesh_descriptor.attrib_pos.stride),
                     static_cast<int32_t>(mesh_descriptor.attrib_pos.offset)});
    }

    if (mesh_descriptor.attrib_normal.size > 0) {
        this->attach(mesh_descriptor.attrib_normal.location,
                     mesh_descriptor.attrib_normal.size,
                     mesh_descriptor.attrib_normal.type,
                    {static_cast<int32_t>(mesh_descriptor.attrib_normal.stride),
                     static_cast<int32_t>(mesh_descriptor.attrib_normal.offset)});
    }

    if (mesh_descriptor.attrib_texcoord.size > 0) {
        this->attach(mesh_descriptor.attrib_texcoord.location,
                     mesh_descriptor.attrib_texcoord.size,
                     mesh_descriptor.attrib_texcoord.type,
                    {static_cast<int32_t>(mesh_descriptor.attrib_texcoord.stride),
                     static_cast<int32_t>(mesh_descriptor.attrib_texcoord.offset)});
    }

    if (mesh_descriptor.indice_size > 0 && mesh_descriptor.p_indices != nullptr) {
        this->bind(1, GL_ELEMENT_ARRAY_BUFFER);
        this->send(mesh_descriptor.indice_size, mesh_descriptor.p_indices, true);
        this->set_index_primitive(mesh_descriptor.indice_type);
    }

    this->revoke();
}

void bicudo::gpubuffer::set_primitive(uint32_t _primitive) {
    this->primitive = _primitive;
}

void bicudo::gpubuffer::set_index_primitive(uint32_t _primitive) {
    this->index_primitive = _primitive;
}

void bicudo::gpubuffer::bind(uint32_t key, uint32_t _working_buffer) {
    uint32_t &buffer {this->buffer_map[key]};
    if (!buffer) {
        glGenBuffers(1, &buffer);
    }

    switch (_working_buffer) {
    case GL_ELEMENT_ARRAY_BUFFER:
        this->element_buffer_key = key;
        this->indexing_rendering_enabled = true;
        break;
    default:
        break;
    }

    glBindBuffer(_working_buffer, buffer);
    this->buffer_bind = _working_buffer;
    this->bind_on = true;
}

void bicudo::gpubuffer::send(int64_t data_size, void *p_data, bool immutable_draw) {
    glBufferData(this->buffer_bind, data_size, p_data, immutable_draw ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
}

void bicudo::gpubuffer::edit(void *p_data, const bicudo::ivec2 &stride) {
    glBufferSubData(this->buffer_bind, static_cast<int64_t>(stride.x), static_cast<int64_t>(stride.y), p_data);
}

void bicudo::gpubuffer::attach(uint32_t layout_location_slot, int32_t size, uint32_t type, const bicudo::ivec2 &stride) {
    glEnableVertexAttribArray(layout_location_slot);
    glVertexAttribPointer(layout_location_slot, size, type, false,
                          static_cast<int64_t>(stride.x), (void*) (static_cast<int64_t>(stride.y)));
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