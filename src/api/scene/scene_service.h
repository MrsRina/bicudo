#pragma once
#include "api/service/service.h"
#include "scene.h"

#ifndef SCENE_SERVICE_H
#define SCENE_SERVICE_H

/**
 * Management service for scene in game.
 **/
class scene_service : public service {
protected:
    /* Works with this scene only. */
    scene* current_scene = NULL;
public:
    scene_service(const std::string &service_name) : service(service_name) { 
    }

    /* Start of setters & getters. */
    // void set_current_scene(scene* raw_scene);
    scene* get_current_scene();
    /* End of setters & getters. */

    /* Start of main methods. */
    void start_scene(scene* raw_scene);
    void end_scene(scene* raw_scene);
    /* End of main methods. */
    
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