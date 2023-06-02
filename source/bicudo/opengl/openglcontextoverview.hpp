#ifndef BICUDO_OPENGL_CONTEXT_OVERVIEW_H
#define BICUDO_OPENGL_CONTEXT_OVERVIEW_H

#include <SDL2/SDL_video.h>

namespace bicudo {
    extern bool gl_context_initialised;
    extern const char* gl_shading_version;
    extern unsigned char gl_major_version;
    extern unsigned char gl_minor_version;
    extern SDL_GLContext sdl_gl_context;

    void initglcontext();
    void createglcontext(SDL_Window *p_root);
}

#endif