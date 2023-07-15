#ifndef BICUDO_GRAPHICS_GPU_BUFFER_H
#define BICUDO_GRAPHICS_GPU_BUFFER_H

#include "gpufeature.hpp"
#include <unordered_map>

namespace bicudo {
    class gpubuffer : public bicudo::gpufeature {
    protected:
        uint32_t primitive {};
        uint32_t buffer_bind {};
        uint32_t index_primitive {};

        uint32_t element_buffer_key {};
        uint32_t key_bind {};
        uint32_t vertex_arrays_object {};

        bool bind_on {};
        bool indexing_rendering_enabled {};
        std::unordered_map<uint32_t, uint32_t> buffer_map {};
    public:
        void set_mesh_descriptor(bicudo::meshdescriptor &mesh_descriptor) override;
        void set_primitive(uint32_t _primitive) override;
        void set_index_primitive(uint32_t _primitive) override;
        void bind(uint32_t key, uint32_t buffer) override;
        void send(int64_t data_size, void *p_data, bool immutable_draw) override;
        void attach(uint32_t layout_location_slot, int32_t size, uint32_t type, const bicudo::ivec2 &stride) override;
        void edit(void *p_data, const bicudo::ivec2 &stride) override;
        void unbind() override;
        void free_memory(uint32_t key) override;
        void free_all_memory() override;
        void invoke() override;
        void revoke() override;
        uint32_t get_gpu_reference(uint32_t key) override;
    };
}

#endif