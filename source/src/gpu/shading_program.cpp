#include "bicudo/gpu/shading_program.hpp"
#include "bicudo/bicudo.hpp"

bool bicudo::compile_shader_stage(uint32_t &shader, int32_t stage, const char* source) {
	shader = glCreateShader(stage);
	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);

	int32_t compile_status {};
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);

	if (!compile_status) {
		char info_log[256];

        std::string log {};
        log += '\n';
        log += info_log;
        bicudo::core->get_logger()->send_warning(log);
		return false;
	}

	return true;
}

bool bicudo::create_shading_program(uint32_t &program, const std::vector<bicudo::resource> &resources) {
	program = glCreateProgram();
	bool flag {program == 0};

	std::string shader_data {};
	std::vector<uint32_t> compiled_shaders {};
	uint32_t shader {};

	for (const bicudo::resource& resource : resources) {
		// reduce var creation.
		shader_data = "Compiling shader... '";
		shader_data += resource.path;
		shader_data += "'";
		bicudo::core->get_logger()->send_info(shader_data);

		flag = flag && bicudo::readfile(resource.path, shader_data);
		flag = flag && bicudo::compile_shader_stage(shader, resource.type, shader_data.c_str());

		if (!flag) {
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

			// reduce var creation.
			shader_data.clear();
			shader_data += "Failed to link shading program: \n";
			shader_data += info_log;
			bicudo::core->get_logger()->send_warning(shader_data);
		}
	}

	for (uint32_t &shaders : compiled_shaders) {
		glDeleteShader(shaders);
	}

    return link_status;
}