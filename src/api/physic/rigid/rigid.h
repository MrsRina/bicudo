#pragma once
#include "api/feature/feature.h"
#include "api/util/util.h"

#ifndef RIGID_H
#define RIGID_H

namespace rigid {
    /**
     * All rigid types.
     **/
    enum type {
        RIGID2D = 1,
        RIGID3D = 2
    };
};

/**
 * Rigid class to all rigid objects.
 **/
class rigid : public ifeature {
protected:
    uint8_t type;
public:
    /* Start of setters and getters. */
    uint8_t set_type(uint8_t val_type);
    uint8_t get_type();
    /* End of setters and getters. */

    /* Start of override methods. */
    void on_event(SDL_Event &sdl_event);
    void on_locked_update();
    void on_update();
    /* End of override methods. */
};

#endif