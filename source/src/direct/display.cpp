#include "bicudo/direct/display.hpp"
#include "GL/glew.h"
#include "bicudo/opengl/opengl_context_overview.hpp"
#include "bicudo/util/logger.hpp"

SDL_Window *&bicudo::display::root() {
    return this->p_root;
}

void bicudo::display::on_update() {
    if (this->p_root == nullptr) {
        this->p_root = SDL_CreateWindow(this->title.c_str(), this->rect[0], this->rect[1], this->rect[2], this->rect[3], SDL_WINDOW_OPENGL | this->flags);

        if (!bicudo::gl_context_initialised) {
            bicudo:sdl_gl_context = SDL_GL_CreateContext(this->p_root);
            glewExperimental = bicudo::gl_context_initialised = true;
            glewInit();
            bicudo::log("OpenGL context initialised.");
        } else {
            SDL_GL_MakeCurrent(this->p_root, bicudo::sdl_gl_context);
            bicudo::log("OpenGL context changed to " + this->title + " window.");
        }
    } else {
        SDL_SetWindowSize(this->p_root, this->rect[2], this->rect[3]);
        SDL_SetWindowTitle(this->p_root, this->title.c_str());
    }

    SDL_SetWindowOpacity(this->p_root, this->opacity);
}
