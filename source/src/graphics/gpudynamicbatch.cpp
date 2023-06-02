#include "bicudo/graphics/gpudynamicbatch.hpp"

void bicudo::gpudynamicbatch::set_draw_stride(int64_t size, int64_t offset, int64_t instances) {
    this->stride[0] = size;
    this->stride[1] = offset;
}

void bicudo::gpudynamicbatch::draw() {
    if (this->vertex_arrays_object) {
        glDrawElements(static_cast<uint32_t>(this->primitive), this->stride[0], static_cast<uint32_t>(this->index_primitive), (void*) this->stride[1]);
    } else {
        glDrawArrays(static_cast<uint32_t>(this->primitive), this->stride[0], this->stride[1]);
    }
}

void bicudo::gpudynamicbatch::free_all_memory() {
    bicudo::gpubuffer::free_all_memory();
    if (this->vertex_arrays_object) glDeleteVertexArrays(1, &this->vertex_arrays_object);
}