#include "bicudo/api/shader/shader.hpp"
#include <GL/GLEW.h>

void bicudo::shader::use() const {
    glUseProgram(this->shading_program_id);
}

void bicudo::shader::unuse() const {
    glUseProgram(0);
}

void bicudo::shader::set_uniform(std::string_view name, float val) const {
    glUniform1f(glGetUniformLocation(this->shading_program_id, name.data()), val);
}

void bicudo::shader::set_uniform(std::string_view name, int32_t val) const {
    glUniform1i(glGetUniformLocation(this->shading_program_id, name.data()), val);
}

void bicudo::shader::set_uniform(std::string_view name, bool val) const {
    glUniform1i(glGetUniformLocation(this->shading_program_id, name.data()), val);
}

void bicudo::shader::set_uniform_vec4(std::string_view name, const float *val) const {
    glUniform4fv(glGetUniformLocation(this->shading_program_id, name.data()), 1, val);
}

void bicudo::shader::set_uniform_vec3(std::string_view name, const float *val) const {
    glUniform3fv(glGetUniformLocation(this->shading_program_id, name.data()), 1, val);
}

void bicudo::shader::set_uniform_vec2(std::string_view name, const float *val) const {
    glUniform2fv(glGetUniformLocation(this->shading_program_id, name.data()), 1, val);
}

void bicudo::shader::set_uniform_matrix4x4(std::string_view name, const float *mat) const {
    glUniformMatrix4fv(glGetUniformLocation(this->shading_program_id, name.data()), 1, GL_FALSE, mat);
}

void bicudo::shader::set_uniform_matrix3x3(std::string_view name, const float *mat) const {
    glUniformMatrix3fv(glGetUniformLocation(this->shading_program_id, name.data()), 1, GL_FALSE, mat);
}

void bicudo::shader::set_uniform_matrix2x2(std::string_view name, const float *mat) const {
    glUniformMatrix2fv(glGetUniformLocation(this->shading_program_id, name.data()), 1, GL_FALSE, mat);
}

void bicudo::sshader::registry(std::string_view) {

}

void bicudo::sshader::set_uniform(std::string_view, float) {

}

void bicudo::sshader::set_uniform(std::string_view, int32_t) {

}

void bicudo::sshader::set_uniform(std::string_view, bool) {

}

void bicudo::sshader::set_uniform_vec4(std::string_view, const float *) {

}

void bicudo::sshader::set_uniform_vec3(std::string_view, const float *) {

}

void bicudo::sshader::set_uniform_vec2(std::string_view, const float *) {

}

void bicudo::sshader::set_uniform_matrix4x4(std::string_view, const float *) {

}

void bicudo::sshader::set_uniform_matrix3x3(std::string_view, const float *) {

}

void bicudo::sshader::set_uniform_matrix2x2(std::string_view, const float *) {

}
