#ifndef BICUDO_GPU_SHADING_PROGRAM_H
#define BICUDO_GPU_SHADING_PROGRAM_H

#include "api/util/file.hpp"

namespace bicudo {
	bool compile_shader_stage(int32_t&, int32_t, bicudo::resource&);
	bool create_shading_program(int32_t&, std::vector<bicudo::resource>&);
}

#endif