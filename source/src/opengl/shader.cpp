#include "bicudo/opengl/shader.hpp"
#include "GL/glew.h"
#include "bicudo/util/file.hpp"
#include "bicudo/util/logger.hpp"

void bicudo::shader::invoke() const {
    glUseProgram(this->buffer_shader_program);
}

void bicudo::shader::revoke() const {
    glUseProgram(0);
}

bicudo::shader::shader() {
    this->buffer_shader_program = glCreateProgram();
}

bicudo::shader::~shader() {
    glDeleteProgram(this->buffer_shader_program);
}

bicudo::shader::shader(std::string_view shading_name) {
    this->name = shading_name;
    this->buffer_shader_program = glCreateProgram();
}

void bicudo::shader::set_uniform_mat4(const std::string &uniform_name, const float *p_data) {
    int32_t &location {this->shader_location_map[uniform_name] == 0 ? (this->shader_location_map[uniform_name] = glGetUniformLocation(this->buffer_shader_program, uniform_name.c_str()) + 1) : this->shader_location_map[uniform_name]};
    glUniformMatrix4fv(location - 1, 1, GL_FALSE, p_data);
}

void bicudo::shader::set_uniform_vec4(const std::string &uniform_name, const float *p_data) {
    int32_t &location {this->shader_location_map[uniform_name] == 0 ? (this->shader_location_map[uniform_name] = glGetUniformLocation(this->buffer_shader_program, uniform_name.c_str()) + 1) : this->shader_location_map[uniform_name]};
    glUniform4fv(location - 1, 1, p_data);
}

bool bicudo::createshader(bicudo::shader *&p_shader, const std::vector<bicudo::shading> &shading_list) {
    if (shading_list.empty()) {
        return bicudo::exception("Invalid shading list, empty.");
    }

    std::vector<uint32_t> compiled_shader_list {};
    std::string shader_source {};

    for (const bicudo::shading &resources : shading_list) {
        shader_source.clear();
        if (resources.path_is_resource) {
            shader_source = resources.path;
        } else if (bicudo::readfile(resources.path, shader_source)) {
            break;
        }

        const char *p_resource {&shader_source[0]};
        uint32_t shader {glCreateShader(resources.stage)};

        glShaderSource(shader, 1, &p_resource, nullptr);
        glCompileShader(shader);

        int32_t request {};
        glGetShaderiv(shader, GL_COMPILE_STATUS, &request);
        if (request == GL_FALSE) {
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &request);
            std::string msg {}; msg.resize(request);

            glGetShaderInfoLog(shader, request, nullptr, msg.data());
            bicudo::exception("Failed to compile shader '" + p_shader->name + "'. \n" + msg);
            glDeleteShader(shader);
            break;
        }

        glAttachShader(p_shader->buffer_shader_program, shader);
        compiled_shader_list.push_back(shader);
    }

    bool error_going_on {true};
    if (compiled_shader_list.size() == shading_list.size()) {
        error_going_on = false;
        glLinkProgram(p_shader->buffer_shader_program);

        int32_t request {};
        glGetProgramiv(p_shader->buffer_shader_program, GL_LINK_STATUS, &request);
        if (request == GL_FALSE) {
            glGetProgramiv(p_shader->buffer_shader_program, GL_INFO_LOG_LENGTH, &request);
            std::string msg {}; msg.resize(request);

            glGetProgramInfoLog(p_shader->buffer_shader_program, request, nullptr, msg.data());
            error_going_on = bicudo::exception("Failed to link program '" + p_shader->name + "'. \n" + msg);
            delete p_shader;
        } else {
            error_going_on = bicudo::log("Successfully linked program '" + p_shader->name + "'.");
        }
    }

    return error_going_on;
}
