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

        uint32_t current_key {};
        uint32_t v_key {0}, t_key {1}, n_key {2}, i_key {3};
    public:
        void append_float(bicudo::layout layout, const bicudo::vec2 &vec);
        void append_float(bicudo::layout layout, float value);
        void append_uint(uint32_t value);
        void begin(uint32_t key);

        std::vector<float> &get_float_vector(bicudo::layout layout);
        std::vector<uint32_t> &get_uint_vector();

        uint32_t get_float_key(bicudo::layout layout);
        uint32_t get_uint_key();
    };
}

#endif