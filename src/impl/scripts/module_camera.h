#pragma once

#include "includes/includes.h"
#include "api/module/module.h"

#ifndef MODULE_CAMERA_H
#define MODULE_CAMERA_H

class module_camera : public module {
public:
    static module_camera *instance;
    double x, y, z;

    module_camera() {
        instance = this;
    }

    ~module_camera() {
        instance = nullptr;
    }

    void set_pos(double pos_x, double pos_y, double pos_z);

    void on_start();
    void on_end();
    void on_event(SDL_Event &sdl_event);
    void on_locked_update(uint64_t delta);
    void on_update(uint64_t delta);
    void on_render(float render_time);
};

#endif