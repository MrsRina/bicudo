#ifndef BICUDO_GPU_BUFFERING_H
#define BICUDO_GPU_BUFFERING_H

#include <iostream>
#include <vector>
#include "GL/glew.h"
#include "bicudo/api/geometry/mesh.hpp"

namespace bicudo {
    enum buffer {
        immutable = 1,
        dynamic   = 2,
        stream    = 4,
        typefloat = 8,
        typeuint  = 16,
        ebo       = 32,
        vbo       = 64
    };

    class buffering {
    protected:
        std::vector<uint32_t> buffer_list {};
        uint32_t gpu_buffer_group {}, buffer_index {};
        GLenum shader_array_type {};
        int32_t buffer_ebo {}, indexing_rendering_size {};
    public:
        int32_t stride_begin {}, stride_end {}, draw_mode {GL_TRIANGLES};

        void invoke();
        void revoke();
        void bind_buffer(uint16_t = bicudo::buffer::vbo);

        void compile_mesh(bicudo::mesh&);
        void set_shader_location(uint32_t, int32_t, int32_t, size_t);
        void send_data(uint32_t, void*, uint16_t);
        void draw();
    };
}

#endif