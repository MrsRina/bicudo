#pragma once
#include "api/feature/feature.h"
#include "module_abstract.h"

#ifndef MODULE_H
#define MODULE_H

/**
 * Module feature to create scripts.
 **/
class module : public module_abstract, public ifeature {
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