#ifndef BICUDO_GRAPHICS_GPU_BUFFER_H
#define BICUDO_GRAPHICS_GPU_BUFFER_H

#include "gpufeature.hpp"
#include <unordered_map>

namespace bicudo {
    class gpubuffer : public bicudo::gpufeature {
    protected:
        bicudo::primitive primitive {};
        bicudo::buffer buffer_bind {};
        bicudo::primitive index_primitive {};

        uint32_t element_buffer_key {};
        uint32_t key_bind {};
        uint32_t vertex_arrays_object {};

        bool bind_on {};
        bool indexing_rendering_enabled {};
        std::unordered_map<uint32_t, uint32_t> buffer_map {};
    public:
        void set_mesh(bicudo::mesh &mesh) override;
        void set_primitive(bicudo::primitive _primitive) override;
        void set_index_primitive(bicudo::primitive _primitive) override;
        void bind(uint32_t key, bicudo::buffer buffer) override;
        void send(int64_t data_size, void *p_data, bool immutable_draw) override;
        void attach(uint32_t layout_binding_slot, uint32_t vec_size, bicudo::primitive _primitive, const bicudo::vec2 &stride) override;
        void edit(void *p_data, const bicudo::vec2 &stride) override;
        void unbind() override;
        void free_memory(uint32_t key) override;
        void free_all_memory() override;
        void invoke() override;
        void revoke() override;
    };
}

#endif