#include "bicudo/opengl/shader.hpp"
#include "GL/glew.h"
#include "bicudo/util/file.hpp"
#include "bicudo/util/logger.hpp"

void bicudo::shader::invoke() const {
    glUseProgram(this->program_buffer_name_object);
}

void bicudo::shader::revoke() const {
    glUseProgram(0);
}

bicudo::shader::shader() {
    this->program_buffer_name_object = glCreateProgram();
}

bicudo::shader::~shader() {
    glDeleteProgram(this->program_buffer_name_object);
}

bicudo::shader::shader(std::string_view shading_name) {
    this->name = shading_name;
    this->program_buffer_name_object = glCreateProgram();
}

void bicudo::shader::set_uniform_mat4(const std::string &uniform_name, const float *p_data) {
    glUniformMatrix4fv(this->shader_location_map[uniform_name], 1, GL_FALSE, p_data);
}

void bicudo::shader::set_uniform_vec4(const std::string &uniform_name, const float *p_data) {
    glUniform4fv(this->shader_location_map[uniform_name], 1, p_data);
}

void bicudo::shader::fill_uniforms() {
    int32_t active_uniforms_location {};
    glGetProgramInterfaceiv(this->program_buffer_name_object, GL_UNIFORM, GL_ACTIVE_RESOURCES, &active_uniforms_location);

    GLenum properties[4] {GL_NAME_LENGTH, GL_TYPE, GL_LOCATION, GL_BLOCK_INDEX};
    int32_t results[4] {};

    for (int32_t it {}; it < active_uniforms_location; ++it) {
        glGetProgramResourceiv(this->program_buffer_name_object, GL_UNIFORM, it, 4, properties, 4, nullptr, results);

        int32_t name_buf_size {results[0] + 1};
        char *p_data {new char[name_buf_size]};

        glGetProgramResourceName(this->program_buffer_name_object, GL_UNIFORM, it, name_buf_size, nullptr, p_data);
        this->shader_location_map.insert({p_data, it});
        delete[] p_data;
    }
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

        glAttachShader(p_shader->program_buffer_name_object, shader);
        compiled_shader_list.push_back(shader);
    }

    bool error_going_on {true};
    if (compiled_shader_list.size() == shading_list.size()) {
        error_going_on = false;
        glLinkProgram(p_shader->program_buffer_name_object);

        int32_t request {};
        glGetProgramiv(p_shader->program_buffer_name_object, GL_LINK_STATUS, &request);
        if (request == GL_FALSE) {
            glGetProgramiv(p_shader->program_buffer_name_object, GL_INFO_LOG_LENGTH, &request);
            std::string msg {}; msg.resize(request);

            glGetProgramInfoLog(p_shader->program_buffer_name_object, request, nullptr, msg.data());
            error_going_on = bicudo::exception("Failed to link program '" + p_shader->name + "'. \n" + msg);
            delete p_shader;
        } else {
            error_going_on = bicudo::log("Successfully linked program '" + p_shader->name + "'.");
            p_shader->fill_uniforms();
        }
    }

    return error_going_on;
}
