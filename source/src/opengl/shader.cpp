#include "bicudo/opengl/shader.hpp"
#include "GL/glew.h"

void bicudo::shader::invoke() const {

}

void bicudo::shader::revoke() const {

}

bicudo::shader::shader() {
    this->buffer_shader_program = glCreateProgram();
}

bicudo::shader::~shader() {
    glDeleteProgram(this->buffer_shader_program);
}
