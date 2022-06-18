#pragma once

#include "api/service/service.h"

#ifndef PHYSIC_SERVICE_H
#define PHYSIC_SERVICE_H

/**
 * Manage all abstract_rigid objects to apply physic.
 **/
class physic_service : public service {
protected:
    // The gravity to push down all objects.
    math::vec2 gravity = {0, 1000.0f};

    /* Start of methods used in physic engine. */
    void update_pos();
    void update_gravity();
    /* End of methods. */
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