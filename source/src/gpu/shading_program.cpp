#include "bicudo/gpu/shading_program.hpp"
#include "bicudo/bicudo.hpp"

bool bicudo::compile_shader_stage(int32_t &shader, int32_t stage, const char* source) {
	shader = glCreateShader(stage);
	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);

	bool compile_status {};
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);

	if (!compile_status) {
		char info_log[256];

		return false;
	}

	return true;
}

bool bicudo::create_shading_program(int32_t &program, std::vector<bicudo::resource> &resources) {
	program = glCreateProgram();
	bool flag {program == 0};

	std::string shader_data {};
	std::vector<int32_t> compiled_shaders {};
	int32_t shader {};

	for (bicudo::resource &resource : resources) {
		// reduce var creation.
		shader_data = "Compiling shader... '";
		shader_data += resource.path;
		shader_data += "'";
		bicudo::core->get_logger().send_info(shader_data);

		flag = flag && bicudo::readfile(resource.path, shader_data);
		flag = flag && bicudo::compile_shader_stage(shader, resource.type, shader_data.c_str());

		if (!flag) {
			break;
		}

		compiled_shaders.push_back(shader);
	}

	bool link_status {};
	if (resources.size() == compiled_shaders.size()) {
		program = glCreateProgram();

		for (int32_t &shaders : compiled_shaders) {
			glAttachShader(program, shaders);
		}

		glLinkProgram(program);
		glGetProgramiv(program, GL_LINK_STATUS, &link_status);

		if (!link_status) {
			char info_log[256];

			glGetProgramInfoLog(program.program, 256, nullptr, info_log);
			glDeleteProgram(program);

			// reduce var creation.
			shader_data.clear();
			shader_data += "Failed to link shading program: \n";
			shader_data += info_log;
			bicudo::core->get_logger().send_warning(shader_data);
		}
	}

	for (int32_t &shaders : compiled_shaders) {
		glDeleteShader(shaders);
	}
}