#ifndef BICUDO_GPU_BUFFERING_H
#define BICUDO_GPU_BUFFERING_H

#include <iostream>
#include <vector>
#include <GL/GLEW.h>
#include "bicudo/api/geometry/mesh.hpp"

namespace bicudo {
    enum datatype {
        immutable = GL_STATIC_DRAW, dynamic = GL_DYNAMIC_DRAW, stream = GL_STREAM_DRAW
    };

    class buffering {
    protected:
        std::vector<uint32_t> buffer_list {};
        uint32_t gpu_buffer_group {}, buffer_index {};
    public:
        int32_t stride_begin {}, stride_end {}, draw_mode {};

        void invoke();
        void revoke();
        void bind_buffer();

        void compile_mesh(bicudo::mesh&);
        void set_shader_location(uint32_t, int32_t, int32_t, uint32_t);
        void send_data(uint32_t, void*, bicudo::datatype = bicudo::datatype::dynamic);
        void draw();
    };
}

#endif