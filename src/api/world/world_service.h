#pragma once
#include "api/service/service.h"

#ifndef WORLD_SERVICE_H
#define WORLD_SERVICE_H

class world_service : public service {
public:
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