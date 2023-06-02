#ifndef BICUDO_GRAPHICS_GPU_FEATURE_H
#define BICUDO_GRAPHICS_GPU_FEATURE_H

#include "../graphics/stream/mesh.hpp"

namespace bicudo {
    enum class primitive {
        lines   = GL_LINES,
        quads   = GL_TRIANGLES,
        points  = GL_POINTS,
        uint32  = GL_UNSGINED_INT,
        int32   = GL_INT,
        uint16  = GL_UNSGINED_SHORT,
        int16   = GL_SHORT
        int8    = GL_BYTE,
        uint8   = GL_UNSIGNED_BYTE,
        float32 = GL_FLOAT,
        float16 = GL_HALF_FLOAT
    };

    enum class buffer {
        array = GL_ARRAY_BUFFER
    };

    class gpufeature {
    public:
        virtual void set_mesh(bicudo::mesh&) {};
        virtual void set_primitive(bicudo::primitive) {};
        virtual void bind(uint32_t, bicudo::buffer) {};
        virtual void edit(void*, const bicudo::vec2&) {};
        virtual void send(void*, bool = false) {};
        virtual void active(uint32_t, bicudo::primitive const bicudo::&);
        virtual void unbind() {};

        virtual void draw() {};
        virtual void invoke() {};
        virtual void revoke() {};
    };
}

#endif