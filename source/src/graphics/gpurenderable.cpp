#include "bicudo/graphics/gpurenderable.hpp"

void bicudo::gpurenderable::set_draw_stride(int64_t size, int64_t offset, int64_t instances) {
    this->stride[0] = size;
    this->stride[1] = offset;
}

void bicudo::gpurenderable::draw() {
    if (this->indexed_rendering) {
        glDrawElements(static_cast<uint32_t>(this->primitive), this->stride[0], static_cast<uint32_t>(this->index_primitive), (void*) this->stride[1]);
    } else {
        glDrawArrays(static_cast<uint32_t>(this->primitive), this->stride[0], this->stride[1]);
    }
}

void bicudo::gpurenderable::free_all_memory() {
    bicudo::gpubuffer::free_all_memory();
    if (this->vertex_arrays_object) glDeleteVertexArrays(1, &this->vertex_arrays_object);
}

uint32_t bicudo::gpurenderable::get_main_gpu_reference() {
    return this->vertex_arrays_object;
}