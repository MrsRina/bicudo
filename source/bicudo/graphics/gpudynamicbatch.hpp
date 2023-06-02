#ifndef BICUDO_GRAPHICS_GPU_DYNAMIC_BATCH_H
#define BICUDO_GRAPHICS_GPU_DYNAMIC_BATCH_H

#include "gpubuffer.hpp"

namespace bicudo {
    class gpudynamicbatch : public bicudo::gpubuffer {
    protected:
        uint32_t vertex_arrays_object {};
        int64_t stride[2] {};
    public:
        void set_draw_stride(int64_t size, int64_t offset, int64_t instances) override;
        void draw() override;
        void free_all_memory() override;
    };
}

#endif