#pragma once
#include "api/service/service.h"
#include "scene.h"

#ifndef SCENE_MANAGER
#define SCENE_MANAGER

class scene_manager : public service<scene*> {
protected:
    /* The current scene we will works. */
    sc
public:
    /* Start of main methods. */
    /* End of main methods. */

    /* Start of override methods. */
    void on_start();
    void on_end();
    void on_event(SDL_Event &sdl_event);
    void on_locked_update(uint64_t delta);
    void on_update(uint32_t delta);
    void on_render(float render_time);
    /* End of override methods. */
};

#endif