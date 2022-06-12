#pragma once

#include "api/module/module.h"
#include "includes/includes.h"

#ifndef CONTEXT_H
#define CONTEXT_H

/**
 * Context to stuff in game.
 **/
struct context {
    /* Start of main methods. */
    void add_module(const std::string &name, const std::string &description, module* feature);
    /* End of main methods. */

    /* Start of abstract methods. */
    virtual void on_end() {};
    virtual void on_update() {};
    /* End of abstract methods. */
};

#endif