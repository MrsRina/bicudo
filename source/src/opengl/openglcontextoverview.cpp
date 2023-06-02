#include "bicudo/opengl/openglcontextoverview.hpp"
#include "GL/glew.h"
#include "bicudo/util/logger.hpp"

bool bicudo::gl_context_initialised {};
const char *bicudo::gl_shading_version {"#version 450"};
unsigned char bicudo::gl_minor_version {4};
unsigned char bicudo::gl_major_version {4};
SDL_GLContext bicudo::sdl_gl_context {};

void bicudo::initglcontext() {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, bicudo::gl_major_version);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, bicudo::gl_minor_version);
}

void bicudo::createglcontext(SDL_Window *p_root) {
    bicudo:sdl_gl_context = SDL_GL_CreateContext(p_root);
    glewExperimental = bicudo::gl_context_initialised = true;
    glewInit();
    bicudo::log("OpenGL context initialised.");
}
