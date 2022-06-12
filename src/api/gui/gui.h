#pragma once

#include "api/feature/feature.h"

#ifndef GUI_H
#define GUI_H

/**
 * Gui to display any render context.
 **/
class gui : public ifeature {
protected:
    std::string name;
    std::string description;
public:
    gui() : ifeature() {   
        // invoke register.
        this->on_registry();
    }

    /* Start of setters and getters. */
    void set(const std::string &gui_name, const std::string &gui_description);

    std::string get_name();
    std::string get_description();
    /* End of setters and getters. */

    /* Start of abstract override methods. */
    virtual void on_registry();
    /* End of abstract override methods. */

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