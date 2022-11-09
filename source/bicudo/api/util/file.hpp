#ifndef BICUDO_API_UTIL_FILE_H
#define BICUDO_API_UTIL_FILE_H

#include <iostream>
#include <vector>
#include <GL/GLEW.h>

namespace bicudo {
	enum imageformats {
		png = 2, jpng = 4, bitmap = 8
	};

	enum shaderstages {
		vertex = GL_VERTEX_SHADER, geometry = GL_GEOMETRY_SHADER, fragment = GL_FRAGMENT_SHADER, computed = GL_COMPUTE_SHADER
	}

	struct resource {
		std::string path {};
		uint16_t type {};
		void* data {};
	};

	bool readfile(std::string_view, std::string&);
	bool readfile(std::string_view, std::vector<int32_t>&);
}

#endif
