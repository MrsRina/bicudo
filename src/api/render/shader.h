#pragma once

#include "includes/includes.h"

#ifndef SHADER_H
#define SHADER_H

/**
 * FX effects in game.
 **/
struct fx {
	GLuint program;
	bool compiled;

	/* Start of main methods. */
	void use();
	void end();
	
	void set_mat4x4(const std::string &name, float* mat4x4);
	void set_bool(const std::string &name, bool val);
	void set_int(const std::string &name, int32_t val);
	void set_float(const std::string &name, float val);
	/* End of main methods. */
};

/**
 * Shader management.
 **/
struct shader {
	/* All active_fx registered in game. */
	static fx fx_default;
    static fx fx_terrain;

	/* Matrix used in shaders. */
	static float mat4x4_ortho2d[16];
	static float mat2x2_viewport[4];
    static float* mat4x4_view;
    static float* mat4x4_perspective;

	static void init();
	static void context();
	static bool compile(GLuint &shader, GLuint shader_mode, const char* shader_str);
	static bool compile_fx(fx &shader_fx);
	static bool load(fx &shader_fx, const char* vsh_path, const char* fsh_path);
};

#endif