#include "bicudo/api/surface/surface.hpp"

void bicudo::on_create() {
	auto flags {SDL_WINDOW_OPENGL};

	if (this->fullscreen) {
		flags |= SDL_FULLSCREEN;
	}

	if (this->resizable) {
		flags |= SDL_RESIZABLE;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_ACCELERATED_VISUAL, 1);

	this->root = SDL_CreateWindow(this->tag, this->rect.x, this->rect.y, this->rect.w, this->rect.h, flags);
	this->context = SDL_GLCreateContext(this->root);
}

void bicudo::on_destroy() {

}