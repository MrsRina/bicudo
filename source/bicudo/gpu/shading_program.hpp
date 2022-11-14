#ifndef BICUDO_GPU_SHADING_PROGRAM_H
#define BICUDO_GPU_SHADING_PROGRAM_H

#include "bicudo/api/util/file.hpp"

namespace bicudo {
    extern const char* gl_version;

    /*
     * Compile shader source using OpenGL.
     */
    bool compile_shader_stage(uint32_t&, int32_t, const char*);

    /*
     * Create shading program, you can replace resources
     * 'path' with glsl shader code, but remember to enable
     * last argument to false.
     */
    bool create_shading_program(uint32_t&, const std::vector<bicudo::resource>&, bool = true);
}

#endif