#include "bicudo/opengl/opengl_context_overview.hpp"

bool bicudo::gl_context_initialised {};
const char *bicudo::gl_shading_version {"#version 450"};
unsigned char bicudo::gl_minor_version {4};
unsigned char bicudo::gl_major_version {4};
SDL_GLContext bicudo::sdl_gl_context {};
