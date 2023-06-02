#ifndef BICUDO_GRAPHICS_GPU_BUFFER_H
#define BICUDO_GRAPHICS_GPU_BUFFER_H

#include "gpufeature.hpp"
#include "GL/glew.h"
#include <unordered_map>

namespace bicudo {
    class gpubuffer : public bicudo::gpufeature {
    protected:
        bicudo::primitive primitive {};
        std::unordered_map<uint32_t, uint32_t> buffer_map {};
    public:
        void set_mesh(bicudo::mesh &mesh) override;
        void set_primitive(bicudo::primitive _primitive) override;
        void bind(uint32_t, bicudo::buffer) override;
        void edit(void*, const bicudo::vec2&) override;
        void unbind(uint32_t) override;
    };
}

#endif