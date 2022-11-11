#include "bicudo/gpu/driver_impl_manager.hpp"
#include <GL/GLEW.h>
#include <SDL2/SDL.h>

void bicudo::driver_impl_manager::prepare_opengl_attributes() {
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, this->major_opengl_version);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, this->minor_opengl_version);
};

void bicudo::driver_impl_manager::create_opengl_context() {
	glewExperimental = true;
	glewInit();
}

void bicudo::driver_impl_manager::update_viewport_size(int32_t w, int32_t h) {
	this->viewport_width = w;
	this->viewport_height = h;

	glViewport(0, 0, this->viewport_width, this->viewport_height);
}

void bicudo::driver_impl_manager::clear_buffers() {
	glClearColor(this->absolute_surface_color[0], this->absolute_surface_color[1], this->absolute_surface_color[2], 1);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void bicudo::driver_impl_manager::update_absolute_surface_color(float r, float g, float b) {
	this->absolute_surface_color[0] = r;
	this->absolute_surface_color[1] = g;
	this->absolute_surface_color[2] = b;
}