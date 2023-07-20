#include "bicudo/graphics/gpupipeline.hpp"

void bicudo::gpupipeline::set_pipeline_property(bicudo::pipelineproperty &pipeline_property) {
    this->render_layer_list.resize(pipeline_property.render_layer_count);
    for (uint64_t it {}; it < this->render_layer_list.size(); it++) {
        this->render_layer_list.at(it) = pipeline_property.p_render_layers[it];
    }
}

void bicudo::gpupipeline::invoke() {
    glUseProgram(this->render_layer_list.at(0));
}

void bicudo::gpupipeline::revoke() {
    glUseProgram(0);
}

uint32_t bicudo::gpupipeline::get_gpu_reference(uint32_t index) {
    return this->render_layer_list.at(index);
}