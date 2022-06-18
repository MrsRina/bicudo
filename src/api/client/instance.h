#pragma once
#include "bicudo.h"

extern game_core* const BICUDO;

namespace bicudo {
    void set_guiscreen(gui* new_gui);
    gui* current_guiscreen();

    void set_scene(scene* new_scene);
    scene* current_scene();
    scene_service &service_scene();

    module_service &service_module();

    task* create_task(const std::string &task_name);
    void stop_task(const std::string &task_name);
    bool is_task_done(const std::string &task_name);
    task_service &service_task();

    physic_service &service_physic();
};