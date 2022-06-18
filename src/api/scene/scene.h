#pragma once
#include "scene_abstract.h"
#include "api/feature/feature.h"

#ifndef SCENE_H
#define SCENE_H

/**
 * Scene in game to create_task different contexts.
 **/
class scene : public scene_abstract, public ifeature {
public:
    scene() : ifeature() {}
    ~scene() {}

    /* Start of main methods. */
    void disable_all_modules();
    void enable_all_modules();
    /* End of main methods. */

    /* Start of override methods. */
    void on_start();
    void on_end();
    void on_event(SDL_Event &sdl_event);
    void on_locked_update();
    void on_update();
    void on_render();
    /* End of override methods. */
};

#endif