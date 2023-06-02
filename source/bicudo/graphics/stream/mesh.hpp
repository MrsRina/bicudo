#ifndef BICUDO_GRAPHICS_STREAM_MESH_H
#define BICUDO_GRAPHICS_STREAM_MESH_H

#include <iostream>
#include <vector>
#include "../../util/math.hpp"

namespace bicudo {
    enum class layout {
        position, texcoord, normal 
    };

    class mesh {
    protected:
        std::vector<float> v {};
        std::vector<float> t {};
        std::vector<float> n {};
        std::vector<uint32_t> i {};
    public:
        void append_float(bicudo::layout layout, const bicudo::vec2 &vec);
        void append_float(bicudo::layout layout, float value);
        void append_uint(uint32_t value);

        std::vector<float> &get_float_vector(bicudo::layout layout);
        std::vector<uint32_t> &get_uint_vector();
    };
}

#endif