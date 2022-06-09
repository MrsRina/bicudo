#pragma once

#include "includes/includes.h"

#ifndef SHADER_H
#define SHADER_H

struct fx {
	GLuint program;
	bool compiled;
};

struct shader {
	/* All fx registered in game. */
	static fx fx_default;

	static void init();
	static bool compile(GLuint &shader, GLuint shader_mode, const char* shader_str);
	static bool compile_fx(fx &shader_fx);
	static bool load(fx &shader_fx, const char* vsh_path, const char* fsh_path);
};

#endif