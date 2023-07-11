#include "bicudo/graphics/gpupipeline.hpp"

void bicudo::gpupipeline::set_pipeline_property(bicudo::pipelineproperty &_pipeline_property) {
    this->pipeline_property = _pipeline_property;
}

bicudo::pipelineproperty *bicudo::gpupipeline::edit_pipeline_property() {
    return &this->pipeline_property;
}