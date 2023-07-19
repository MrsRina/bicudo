#include "bicudo/direct/resource/shadergroupresource.hpp"
#include "bicudo/util/file.hpp"
#include "bicudo/util/logger.hpp"

bicudo::shadergroupresource::shadergroupresource(const std::vector<bicudo::shadermodule> &pipeline_shader_module_list) {
    this->program = glCreateProgram();
    this->loaded_shader_module_list = pipeline_shader_module_list;
}

void bicudo::shadergroupresource::on_load() {
    std::vector<uint32_t> compiled_shader_list {};
    std::string shader_source {};

    int32_t gl_output {};
    const char *p_shader_src {};

    for (bicudo::shadermodule &shader_module : this->loaded_shader_module_list) {
        shader_source.clear();
        if (bicudo::readfile(shader_module.p_path, shader_source)) {
            break;
        }

        auto &shader {compiled_shader_list.emplace_back() = glCreateShader(shader_module.stage)};
        p_shader_src = shader_source.c_str();

        glShaderSource(shader, 1, &p_shader_src, nullptr);
        glCompileShader(shader);

        glGetShaderiv(shader, GL_COMPILE_STATUS, &gl_output);
        if (gl_output == GL_FALSE) {
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &gl_output);

            std::string info_log_message {};
            info_log_message.resize(gl_output);

            glGetShaderInfoLog(shader, gl_output, nullptr, info_log_message.data());
            bicudo::log() << "Failed to compile shader '" << shader_module.p_path << "': \n" << info_log_message;
            break;
        }
    }

    bool able_to_link_program {compiled_shader_list.size() == this->loaded_shader_module_list.size()};
    for (uint32_t &compiled_shader : compiled_shader_list) {
        if (able_to_link_program) {
            glAttachShader(this->program, compiled_shader);
        }

        glDeleteShader(compiled_shader);
    }

    if (able_to_link_program) {
        glLinkProgram(this->program);
        glGetProgramiv(this->program, GL_LINK_STATUS, &gl_output);

        if (gl_output == GL_FALSE) {
            glGetProgramiv(this->program, GL_INFO_LOG_LENGTH, &gl_output);

            std::string info_log_message {};
            info_log_message.resize(gl_output);

            glGetProgramInfoLog(this->program, gl_output, nullptr, info_log_message.data());
            bicudo::log() << "Failed to link program: \n" << info_log_message;
            return;
        }

        bicudo::log() << "Resource shader group compiled & program sucessfully linked!";
    }
}

void bicudo::shadergroupresource::on_destroy() {
    glDeleteProgram(this->program);
}

uint32_t bicudo::shadergroupresource::get_program() {
    return this->program;
}