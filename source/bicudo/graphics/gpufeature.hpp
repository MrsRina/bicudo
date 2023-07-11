#ifndef BICUDO_GRAPHICS_GPU_FEATURE_H
#define BICUDO_GRAPHICS_GPU_FEATURE_H

#include "stream/mesh.hpp"
#include "GL/glew.h"
#include "gpudirecttask.hpp"

namespace bicudo {
    enum class primitive {
        lines     = GL_LINES,
        triangles = GL_TRIANGLES,
        points    = GL_POINTS,
        uint32    = GL_UNSIGNED_INT,
        int32     = GL_INT,
        uint16    = GL_UNSIGNED_SHORT,
        int16     = GL_SHORT,
        int8      = GL_BYTE,
        uint8     = GL_UNSIGNED_BYTE,
        float32   = GL_FLOAT,
        float16   = GL_HALF_FLOAT
    };

    enum class buffer {
        array = GL_ARRAY_BUFFER,
        index = GL_ELEMENT_ARRAY_BUFFER
    };

    struct pipelineproperty {
    public:
        uint64_t viewport_count {};
        bicudo::vec4 *p_viewports {};
        uint64_t render_layer_count {};
        uint32_t *p_render_layers {};
    };

    class gpufeature {
    public:
        explicit gpufeature() = default;
        ~gpufeature() { this->free_all_memory(); };
    public:
        virtual void set_mesh(bicudo::mesh&) {};
        virtual void set_primitive(bicudo::primitive) {};
        virtual void set_index_primitive(bicudo::primitive) {};
        virtual void set_draw_stride(int64_t, int64_t, int64_t = -1) {};
        virtual void bind(uint32_t, bicudo::buffer) {};
        virtual void edit(void*, const bicudo::vec2&) {};
        virtual void send(int64_t, void*, bool = false) {};
        virtual void attach(uint32_t, uint32_t, bicudo::primitive, const bicudo::vec2&) {};
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