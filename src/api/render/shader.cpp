#include "shader.h"
#include "api/util/util.h"

fx shader::fx_default;
fx shader::fx_terrain;

float shader::mat4x4_ortho2d[16];
float shader::mat2x2_viewport[4];
float shader::mat4x4_perspective[16];
float shader::mat4x4_view[16];

void fx::use() {
	glUseProgram(this->program);
}

void fx::end() {
	glUseProgram(0);
}

void fx::set_mat4x4(const std::string &name, float* mat4x4) {
	glUniformMatrix4fv(glGetUniformLocation(this->program, name.c_str()), 1, GL_FALSE, mat4x4);
}

void fx::set_bool(const std::string &name, bool val) {
	glUniform1i(glGetUniformLocation(this->program, name.c_str()), (int) val);
}

void fx::set_int(const std::string &name, int32_t val) {
	glUniform1i(glGetUniformLocation(this->program, name.c_str()), val);
}

void fx::set_float(const std::string &name, float val) {
	glUniform1f(glGetUniformLocation(this->program, name.c_str()), val);
}

void shader::init() {
	shader::load(shader::fx_default, "data/fx/fx_default.vsh", "data/fx/fx_default.fsh");
    shader::load(shader::fx_terrain, "data/fx/fx_terrain.vsh", "data/fx/fx_terrain.fsh");
}

void shader::context() {
	glGetFloatv(GL_VIEWPORT, mat2x2_viewport);
	math::ortho2d(mat4x4_ortho2d, 0.0f, mat2x2_viewport[2], mat2x2_viewport[3], 0.0f);
}

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

	glLinkProgram(shader_fx.program);
	glGetProgramiv(shader_fx.program, GL_LINK_STATUS, &program_compiled_status);

	if (program_compiled_status != GL_TRUE) {
		char log[256];
		glGetProgramInfoLog(shader_fx.program, 256, NULL, log);

		util::log(std::string(log));
		return false;
	}

	return true;
}

bool shader::load(fx &shader_fx, const char* vsh_path, const char* fsh_path) {
	if (!util::file::exists(vsh_path)) {
		util::log("Could not read '" + std::string(vsh_path) + "' file.");
		return false;
	}

	if (!util::file::exists(fsh_path)) {
		util::log("Could not read '" + std::string(fsh_path) + "' file.");
		return false;
	}

	game_resource vertex_resource, fragment_resource;
	GLuint vertex_shader, fragment_shader;
	shader_fx.compiled = false;

	util::file::load(vertex_resource, vsh_path);
	util::file::load(fragment_resource, fsh_path);

	util::log("Shader FX loading (...) " + std::string(vsh_path));
	bool vertex_shader_status = shader::compile(vertex_shader, GL_VERTEX_SHADER, vertex_resource.str.c_str());

	util::log("Shader FX loading (...) " + std::string(fsh_path));
	bool vertex_fragment_status = shader::compile(fragment_shader, GL_FRAGMENT_SHADER,  fragment_resource.str.c_str());

	if (vertex_shader_status && vertex_fragment_status) {
		shader_fx.program = glCreateProgram();

		glAttachShader(shader_fx.program, vertex_shader);
		glAttachShader(shader_fx.program, fragment_shader);

		shader_fx.compiled = shader::compile_fx(shader_fx);

		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);

		if (shader_fx.compiled) {
			util::log("Shader compiled.");
		}
	}

	return shader_fx.compiled;
}