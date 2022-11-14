#ifndef BICUDO_API_GEOMETRY_MESH_H
#define BICUDO_API_GEOMETRY_MESH_H

#include <iostream>
#include <vector>

namespace bicudo {
    struct mesh {
        std::vector<float> vertices {}, uvs, normals {};
        std::vector<uint32_t> vertices_indexing {}, uvs_indexing {}, normals_indexing {};
        int32_t per_vertices_length {2}, per_uvs_length {2}, per_normals_length {2};
    };
}

#endif