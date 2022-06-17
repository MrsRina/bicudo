#pragma once
#include "includes/includes.h"
#include "api/util/util.h"
#include "api/feature/feature.h"

#ifndef SERVICE_H
#define SERVICE_H

/**
 * Build service list.
 **/
class service : public ifeature {
protected:
    /* List with all elements in. */
    std::vector<ifeature*> update_list;
    std::vector<ifeature*> render_list;

    /* Name of this service. */
    std::string name;
public:
    service() {}
    ~service() {}

    /* Start of setters and getters. */
    void set_name(const std::string &service_name);
    std::string get_name();
    /* End of setters and getters. */

    /* Start of main methods. */
    void add(ifeature* feature);
    void remove(ifeature* feature);
    bool contains(ifeature* feature);

    std::vector<ifeature*> &get_update_list();
    std::vector<ifeature*> &get_render_list();
    /* End of main methods. */

    /* Start of abstract methods. */
    virtual void on_start();
    virtual void on_end();
    /* End of abstract methods. */

    /* Start of override methods. */
    void on_event(SDL_Event &sdl_event);
    void on_locked_update();
    void on_update();
    void on_render();
    /* End of override methods. */
};

#endif