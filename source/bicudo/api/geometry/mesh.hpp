#ifndef BICUDO_API_GEOMETRY_MESH_H
#define BICUDO_API_GEOMETRY_MESH_H

#include <iostream>
#include <vector>

namespace bicudo {
    enum class meshing {
        vertex, texture, normal, ivertex, itexture, inormal
    };

    struct mesh {
    protected:
        std::vector<float> v {},
                           t {},
                           vn {};

        std::vector<uint32_t> iv {},
                              it {},
                              ivn {};

        int32_t v_vec_len {2},
                t_vec_len {2},
                vn_vec_len {2};
    public:
        void append(const std::vector<float>&, bicudo::meshing);
        void append(const std::vector<uint32_t>&, bicudo::meshing);
        void set_vec_len(int32_t, bicudo::meshing);

        std::vector<float> &get_float_list(bicudo::meshing);
        std::vector<uint32_t> &get_uint_list(bicudo::meshing);
        int32_t get_vec_len(bicudo::meshing);
    };
}

#endif