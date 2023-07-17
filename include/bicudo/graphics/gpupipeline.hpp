#ifndef BICUDO_GRAPHICS_GPU_PIPELINE_H
#define BICUDO_GRAPHICS_GPU_PIPELINE_H

#include "gpufeature.hpp"

namespace bicudo {
    class gpupipeline : public gpufeature {
    protected:
        std::vector<uint32_t> render_layer_list {};
    public:
        void set_pipeline_property(bicudo::pipelineproperty &pipeline_property) override;
        void invoke() override;
        void revoke() override;
    };
}

#endif