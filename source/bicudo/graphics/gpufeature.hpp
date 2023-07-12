#ifndef BICUDO_GRAPHICS_GPU_FEATURE_H
#define BICUDO_GRAPHICS_GPU_FEATURE_H

#include "GL/glew.h"
#include "gpudirecttask.hpp"
#include "gpustructures.hpp"

namespace bicudo {
    class gpufeature {
    public:
        explicit gpufeature() = default;
        ~gpufeature() { this->free_all_memory(); };
    public:
        virtual void set_mesh_descriptor(bicudo::meshdescriptor&) {};
        virtual void set_primitive(uint32_t) {};
        virtual void set_index_primitive(uint32_t) {};
        virtual void set_draw_stride(int64_t, int64_t, int64_t = -1) {};
        virtual void bind(uint32_t, uint32_t) {};
        virtual void edit(void*, const bicudo::vec2&) {};
        virtual void send(int64_t, void*, bool = false) {};
        virtual void attach(uint32_t, uint32_t, uint32_t, const bicudo::vec2&) {};
        virtual void unbind() {};
        virtual void free_memory(uint32_t) {};
        virtual void free_all_memory() {};
        virtual void draw() {};
        virtual void invoke() {};
        virtual void revoke() {};
        virtual uint32_t get_gpu_reference(uint32_t) { return 0; };
        virtual uint32_t get_main_gpu_reference() { return 0; };
        virtual void set_pipeline_property(bicudo::pipelineproperty&) {};
        virtual bicudo::pipelineproperty *edit_pipeline_property() { return nullptr; };
    };
}

#endif