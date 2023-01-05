#ifndef BICUDO_GPU_BUFFERING_H
#define BICUDO_GPU_BUFFERING_H

#include <iostream>
#include <vector>
#include "GL/glew.h"
#include "bicudo/api/geometry/mesh.hpp"
#include "bicudo/api/util/math.hpp"

namespace bicudo {
    class buffering {
    protected:
        static uint32_t current_buffer_preset[2];

        std::vector<uint32_t> buffer_list {};
        uint32_t buffer_vao {};
        uint32_t buffer_ebo {};

        bool instanced {};
        uint32_t buffer_list_size {};
    public:
        int32_t stride[3] {};
        int32_t primitive {GL_TRIANGLES};

        void invoke();
        void bind(const vec2 &buffer_type);
        void send(int32_t size, void *p_data, int32_t gl_driver_read_mode);
        void attach(uint32_t location, int32_t vec, const vec2 &shader_stride);
        void revoke();
        void draw();

        void compile_mesh(bicudo::mesh &mesh);
    };
}

#endif