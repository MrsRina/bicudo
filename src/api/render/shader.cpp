#include "shader.h"

bool shader::compile(GLuint &shader, GLuint shader_mode, const char* shader_str) {
	shader = glCreateShader(shader_mode);

	glShaderSource(shader, 1, &shader_str, NULL);
	glCompileShader(shader);

	GLint shader_compile_status = GL_FALSE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_compile_status);

	if (shader_compile_status != GL_TRUE) {
		char log[256];
		glGetShaderInfoLog(shader, 256, NULL, log);

		util::log(std::string(log));
		return false;
	}

	return true;
}

bool shader::compile_fx(fx &shader_fx) {
	GLint program_compiled_status = GL_FALSE;
	glGetProgramiv(shader_fx.program, GL_LINK_STATUS, &program_compiled_status);

	if (program_compiled_status != GL_TRUE) {
		char log[256];
		glGetProgramInfoLog(shader_fx.proram, 256, NULL, log);

		util::log(stdf::string(log));
		return false;
	}

	return true;
}

bool shader::file::load(fx &shader_fx, const char* vsh_path, const char* fsh_path) {
	if (util::file::exists(vsh_path)) {
		util::log("Could not read '" + std::string(vsh_path) + "' file.");
		return false;
	}

	if (util::file::exists(fsh_path)) {
		util::log("Could not read '" + std::string(fsh_path) + "' file.");
		return false;
	}

	shader_fx.compiled = false;
	GLuint vertex_shader, fragment_shader;

	shader::compile(vertex_shader, GL_VERTEX_SHADER, vsh_path);
	shader::compile(fragment_shader, GL_FRAGMENT_SHADER, fsh_path);

	return true;
}