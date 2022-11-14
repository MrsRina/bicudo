#include "bicudo/api/surface/surface.hpp"
#include "bicudo/api/util/flag.hpp"

void bicudo::surface::on_create() {
    feature::on_create();
    int32_t flags {SDL_WINDOW_OPENGL};

    if (this->fullscreen) {
        flags |= SDL_WINDOW_FULLSCREEN;
    }

    if (this->resizable) {
        flags |= SDL_WINDOW_RESIZABLE;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    uint32_t win_pos_x {this->rect.x == bicudo::centered ? SDL_WINDOWPOS_CENTERED : static_cast<uint32_t>(this->rect.x)}, win_pos_y {this->rect.y == bicudo::centered ? SDL_WINDOWPOS_CENTERED : static_cast<uint32_t>(this->rect.y)};
    this->root = SDL_CreateWindow(this->tag, static_cast<int32_t>(win_pos_x), static_cast<int32_t>(win_pos_y), static_cast<int32_t>(this->rect.w), static_cast<int32_t>(this->rect.h), flags);
    this->context = SDL_GL_CreateContext(this->root);
}

void bicudo::surface::on_destroy() {
    feature::on_destroy();
}
