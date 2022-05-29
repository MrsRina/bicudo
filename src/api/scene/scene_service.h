#pragma once
#include "api/service/service.h"
#include "scene.h"

#ifndef SCENE_SERVICE
#define SCENE_SERVICE

/**
 * Management service for scene in game.
 **/
class scene_service : public service<scene*> {
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

    scene* get_scene_by_name(const std::string &scene_name);
    scene* get_scene_by_feature_id(uint32_t feature_id);
    /* End of main methods. */

    /* Start of override methods. */
    void on_start();
    void on_end();
    /* End of override methods. */
};

#endif