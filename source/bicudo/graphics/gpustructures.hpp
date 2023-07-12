#ifndef BICUDO_GRAPHICS_GPU_STRUCTURES_H
#define BICUDO_GRAPHICS_GPU_STRUCTURES_H

#include "bicudo/util/math.hpp"

namespace bicudo {
    struct pipelineproperty {
    public:
        uint32_t viewport_count {};
        bicudo::vec4 *p_viewports {};
        uint32_t render_layer_count {};
        uint32_t *p_render_layes {};
    };

    struct attriblayout {
        uint32_t location {};
        int32_t size {};
        uint32_t type {};
        uint32_t stride {};
        uint32_t offset {};
    };

    struct meshdescriptor {
    public:
        uint32_t indice_type {};
        int64_t indice_size {-1};
        void *p_indices {};

        int64_t resource_size {-1};
        void *p_resources {};

        bicudo::attriblayout attrib_pos {0, -1, 0, 0, 0};
        bicudo::attriblayout attrib_texcoord {0, -1, 0, 0, 0};
        bicudo::attriblayout attrib_normal {0, -1, 0, 0, 0};
    };
};

#endif