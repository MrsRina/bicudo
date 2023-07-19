#ifndef BICUDO_GRAPHICS_GPU_RENDERABLE_H
#define BICUDO_GRAPHICS_GPU_RENDERABLE_H

#include "gpubuffer.hpp"

namespace bicudo {
    class gpurenderable : public bicudo::gpubuffer {
    protected:
        uint32_t primitive {};
        uint32_t vertex_arrays_object {};
        uint32_t indexed_rendering {};
        int64_t stride[2] {};
    public:
        void set_primitive(uint32_t _primitive) override;
        void set_draw_stride(int64_t size, int64_t offset, int64_t instances) override;
        void draw() override;
        void free_all_memory() override;
        uint32_t get_main_gpu_reference() override;
    };
}

#endif