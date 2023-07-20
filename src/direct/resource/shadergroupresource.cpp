#include "bicudo/direct/resource/shadergroupresource.hpp"
#include "bicudo/util/file.hpp"
#include "bicudo/util/logger.hpp"

bicudo::shadergroupresource::shadergroupresource(const std::vector<bicudo::shadermodule> &pipeline_shader_module_list) {
    this->program = glCreateProgram();
    this->loaded_shader_module_list = pipeline_shader_module_list;
}

void bicudo::shadergroupresource::on_load() {
    bicudo::log() << "loading shaders";

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
    
        int32_t active_uniforms_location {};
        glGetProgramInterfaceiv(this->program, GL_UNIFORM, GL_ACTIVE_RESOURCES, &active_uniforms_location);

        GLenum properties[4] {GL_NAME_LENGTH, GL_TYPE, GL_LOCATION, GL_BLOCK_INDEX};
        int32_t results[4] {};

        std::string uniform {};
        for (int32_t it {}; it < active_uniforms_location; ++it) {
            glGetProgramResourceiv(this->program_buffer_name_object, GL_UNIFORM, it, 4, properties, 4, nullptr, results);
            int32_t name_buf_size {results[0] + 1};
            
            uniform.clear();
            uniform.resize(name_buf_size);

            glGetProgramResourceName(this->program_buffer_name_object, GL_UNIFORM, it, name_buf_size, nullptr, uniform.data());
            std::cout << uniform << std::endl;

            this->loaded_uniform_map.insert({uniform.c_str(), it});
        }
    }
}

void bicudo::shadergroupresource::on_destroy() {
    glDeleteProgram(this->program);
}

uint32_t bicudo::shadergroupresource::get_program() {
    return this->program;
}