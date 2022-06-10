#pragma once

#include "includes/includes.h"

#ifndef SHADER_H
#define SHADER_H

struct fx {
	GLuint program;
	bool compiled;

	void use();
	void end();

	void set_mat4x4(const std::string &name, float* mat4x4);
	void set_bool(const std::string &name, bool val);
	void set_int(const std::string &name, int32_t val);
	void set_float(const std::string &name, float val);
};

struct shader {
	/* All fx registered in game. */
	static fx fx_default;

	/* Matrix used in shaders. */
	static float mat4x4_ortho2d[16];
	static float mat2x2_viewport[4];

	static void init();
	static void context();
	static bool compile(GLuint &shader, GLuint shader_mode, const char* shader_str);
	static bool compile_fx(fx &shader_fx);
	static bool load(fx &shader_fx, const char* vsh_path, const char* fsh_path);
};

#endif