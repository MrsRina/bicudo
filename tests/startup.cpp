#include <iostream>
#include <bicudo/bicudo.hpp>
#include "starter.hpp"
#include "bicudo/opengl/opengl_context_overview.hpp"

int32_t main(int32_t, char**) {
    /* Specify vendor GL context. */
    bicudo::gl_minor_version = 4;
    bicudo::gl_major_version = 4;
    bicudo::gl_shading_version = "#version 450";

    /* Init the bicudo core. */
    bicudo::core *p_core {new bicudo::core()};
    bicudo::createcore(p_core);

    /* Create a display. */
    bicudo::feature<bicudo::display> *p_display {new bicudo::feature<bicudo::display>()};
    p_display->content.rect[2] = 1280;
    p_display->content.rect[3] = 800;
    p_display->content.title = "Hello this is Bicudo3.";
    p_display->content.flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
    p_display->content.opacity = 1.0f;
    bicudo::createdisplay(p_display);

    /* Insert a scene. */
    bicudo::feature<bicudo::scene*> *p_scene {new bicudo::feature<bicudo::scene*>(new scene_starter())};
    bicudo::createscene(p_scene);

    /* Run bicudo core. */
    return p_core->mainloop();
}