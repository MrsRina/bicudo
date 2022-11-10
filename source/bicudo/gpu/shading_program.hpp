#ifndef BICUDO_GPU_SHADING_PROGRAM_H
#define BICUDO_GPU_SHADING_PROGRAM_H

#include "bicudo/api/util/file.hpp"

namespace bicudo {
	bool compile_shader_stage(uint32_t&, int32_t, const char*);
	bool create_shading_program(uint32_t&, std::vector<bicudo::resource>&);
}

#endif