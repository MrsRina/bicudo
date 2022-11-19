#include "bicudo/gpu/shading_program.hpp"
#include "bicudo/bicudo.hpp"

const char* bicudo::gl_version {"#version 450 core"};

bool bicudo::compile_shader_stage(uint32_t &shader, int32_t stage, const char* source) {
    shader = glCreateShader(stage);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    int32_t compile_status {};
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);

    if (!compile_status) {
        char info_log[256];
        glGetShaderInfoLog(shader, 256, nullptr, info_log);

        std::string log {};
        log += '\n';
        log += info_log;
        bicudo::core->get_logger()->send_warning(log);
        return false;
    }

    return true;
}

bool bicudo::create_shading_program(uint32_t &program, const std::vector<bicudo::resource> &resources, bool readfile) {
    program = glCreateProgram();
    bool flag {true};

    std::string shader_data {}, compile_log {};
    std::vector<uint32_t> compiled_shaders {};
    uint32_t shader {};

    for (const bicudo::resource& resource : resources) {
        compile_log = "Compiling shader ";
        compile_log += std::to_string(compiled_shaders.size() + 1);
        compile_log += " ... ";

        if (readfile) {
            compile_log += "'";
            compile_log += resource.path;
            compile_log += "'";
            flag = bicudo::readfile(resource.path, shader_data);
        } else {
            shader_data = resource.path;
        }

        bicudo::core->get_logger()->send_info(compile_log);
        flag = flag && bicudo::compile_shader_stage(shader, resource.type, shader_data.c_str());

        if (!flag) {
            bicudo::core->get_logger()->send_warning("Could not compile all shaders.");
            break;
        }

        compiled_shaders.push_back(shader);
    }

    int32_t link_status {};
    if (resources.size() == compiled_shaders.size()) {
        program = glCreateProgram();

        for (uint32_t &shaders : compiled_shaders) {
            glAttachShader(program, shaders);
        }

        glLinkProgram(program);
        glGetProgramiv(program, GL_LINK_STATUS, &link_status);

        if (!link_status) {
            char info_log[256];

            glGetProgramInfoLog(program, 256, nullptr, info_log);
            glDeleteProgram(program);

            compile_log.clear();
            compile_log += "Failed to link shading program: \n";
            compile_log += info_log;
            bicudo::core->get_logger()->send_warning(compile_log);
        } else {
            compile_log = "Shading program successfully linked ";
            compile_log += std::to_string(resources.size());
            compile_log += " compiled shaders!";
            bicudo::core->get_logger()->send_info(compile_log);
        }
    }

    for (uint32_t &shaders : compiled_shaders) {
        glDeleteShader(shaders);
    }

    return link_status;
}