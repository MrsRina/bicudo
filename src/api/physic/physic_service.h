#pragma once

#include "api/service/service.h"

#ifndef PHYSIC_SERVICE_H
#define PHYSIC_SERVICE_H

class physic_service : public service {
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