#include "bicudo/direct/resource/shadergroupresource.hpp"
#include "bicudo/direct/resource/shadergroupresource.hpp"

bicudo::shadergroupresource::shadergroupresource(const std::vector<bicudo::shadermodule> &pipeline_shader_module_list) {

}

void bicudo::shadergroupresource::on_load() {

}

void bicudo::shadergroupresource::on_destroy() {

}

uint32_t bicudo::shadergroupresource::get_program() {
    return this->program;
}