#pragma once
#include "includes/includes.h"

/**
 *  to every synchronized object in game.
 **/
class ifeature {
public:
    ifeature();
    ~ifeature();

    /* Start of abstract methods. */
    virtual void on_locked_update(uint64_t delta);
    virtual void on_update(uint64_t delta);
    virtual void on_render(float render_time);
    /* End of abstract methods. */
};