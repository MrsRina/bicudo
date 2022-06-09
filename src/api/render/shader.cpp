#include "shader.h"
#include "api/util/util.h"

fx shader::fx_default = fx();

void shader::init() {
	shader::load(shader::fx_default, "data/fx/fx_default.vsh", "data/fx/fx_default.fsh");
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

	shader_fx.compiled = false;
	GLuint vertex_shader, fragment_shader;

	util::log(std::string(vsh_path) + " ...");
	bool vertex_shader_status = shader::compile(vertex_shader, GL_VERTEX_SHADER, static_cast<std::string>(util::file::load(vsh_path)).c_str()));

	util::log(std::string(fsh_path) + " ...");
	bool vertex_fragment_status = shader::compile(fragment_shader, GL_FRAGMENT_SHADER, static_cast<std::string>(util::file::load(fsh_path)).c_str());

	if (vertex_shader_status && vertex_fragment_status) {
		shader_fx.program = glCreateProgram();

		glAttachShader(shader_fx.program, vertex_shader);
		glAttachShader(shader_fx.program, fragment_shader);

		shader_fx.compiled = shader::compile_fx(shader_fx);

		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
	}

	return shader_fx.compiled;
}