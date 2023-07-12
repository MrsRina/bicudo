#ifndef BICUDO_GRAPHICS_GPU_PIPELINE_H
#define BICUDO_GRAPHICS_GPU_PIPELINE_H

#include "gpufeature.hpp"

namespace bicudo {
    class gpupipeline : public gpufeature {
    protected:
        bicudo::pipelineproperty pipeline_property {};
    public:
        void set_pipeline_property(bicudo::pipelineproperty &_pipeline_property) override;
        bicudo::pipelineproperty *edit_pipeline_property() override;
    };
}

#endif