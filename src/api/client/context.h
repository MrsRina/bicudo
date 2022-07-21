#pragma once

#ifndef CONTEXT_H
#define CONTEXT_H

#include "api/module/module.h"

const static uint32_t EVENT_TICK_UPDATE = 1;

/**
 * Context to stuff in game.
 **/
class context {
public:
    context() {}

    /* Start of main methods. */
    void add_module(const std::string &name, const std::string &description, module* feature);
    /* End of main methods. */

    /* Start of abstract methods. */
    virtual void on_start() {};
    virtual void on_update() {};
    /* End of abstract methods. */
};

#endif