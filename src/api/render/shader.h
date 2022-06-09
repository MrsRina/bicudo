#pragma once

#include "includes/includes.h"

#ifndef SHADER_H
#define SHADER_H

struct fx {
	GLuint program;
	bool compiled;
};

struct shader {
	static GLuint compile(GLuint &shader, GLuint shader_mode, const char* shader_str);
	static GLuint compile_fx(fx &shader_fx);

	struct file {
		static bool load(fx &shader_fx, const char* vsh_path, const char* fsh_path);
	};
};