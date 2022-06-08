#pragma once

#include "includes/includes.h"

#ifndef SHADER_H
#define SHADER_H

struct fx {
	GLuint program;
};

class shader {
	struct file {
		void load(fx);
	};
};

#endif