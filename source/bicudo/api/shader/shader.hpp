#ifndef BICUDO_API_SHADER_H
#define BICUDO_API_SHADER_H

#include <GL/GLEW.h>
#include <map>
#include <iostream>

namespace bicudo {
	struct shader {
        uint32_t shading_program_id {};

		void use();
		void unuse();

		void set_uniform(std::string_view, float);
		void set_uniform(std::string_view, int32_t);
		void set_uniform(std::string_view, bool);

		void set_uniform_vec4(std::string_view, const float*);
		void set_uniform_vec3(std::string_view, const float*);
		void set_uniform_vec2(std::string_view, const float*);
		
		void set_uniform_matrix4x4(std::string_view, const float*);
		void set_uniform_matrix3x3(std::string_view, const float*);
		void set_uniform_matrix2x2(std::string_view, const float*);
	};

	struct sshader {
	protected:
		std::map<const char*, int32_t> uniforms_map {};
	public:
        uint32_t shading_program_id {};
		void registry(std::string_view);

		void set_uniform(std::string_view, float);
		void set_uniform(std::string_view, int32_t);
		void set_uniform(std::string_view, bool);

		void set_uniform_vec4(std::string_view, const float*);
		void set_uniform_vec3(std::string_view, const float*);
		void set_uniform_vec2(std::string_view, const float*);
		
		void set_uniform_matrix4x4(std::string_view, const float*);
		void set_uniform_matrix3x3(std::string_view, const float*);
		void set_uniform_matrix2x2(std::string_view, const float*);
	};
}

#endif