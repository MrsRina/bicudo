#pragma once
#include "includes/includes.h"

#ifndef FEATURE_H
#define FEATURE_H

/**
 * Feature class to every synchronized object in game.
 **/
class ifeature {
protected:
    /* Different places in the game are connected by an id. */
    uint32_t feature_id;

    /* Set visibility. */
    unsigned int visibility;

    /* Alive state. */
    bool alive;
public:
    ifeature();
    ~ifeature();

    /* Start of setter and getter. */
    void set_feature_id(uint32_t id);
    uint32_t get_feature_id();

    void set_visibility_flag(unsigned int flag);
    unsigned int get_visibility();

    void set_alive_state(bool state);
    bool is_alive();
    /* End of setter and getter. */

    /* Start of abstract methods. */
    virtual void on_event(SDL_Event &sdl_event) {}
    virtual void on_locked_update(uint64_t delta) {}
    virtual void on_update(uint64_t delta) {}
    virtual void on_render(float render_time) {}
    /* End of abstract methods. */
};

#endif