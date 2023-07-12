#ifndef BICUDO_GRAPHICS_GPU_STRUCTURES_H
#define BICUDO_GRAPHICS_GPU_STRUCTURES_H

#include "../

namespace bicudo {
    struct pipelineproperty {
    public:
        uint32_t viewport_count {};
        bicudo::vec4 *p_viewports {};
        uint32_t render_layer_count {};
        uint32_t *p_render_layes {};
    };

    struct meshdescriptor {
    public:
        uint32_t indice_type {};
        uint32_t indice_size {};
        void *p_indices {};

        uint32_t resource_size {};
        uint32_t p_resources {};
    };
};

#endif