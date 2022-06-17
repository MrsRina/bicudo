#pragma once
#include "bicudo.h"

extern game_core* const BICUDO;

namespace bicudo {
    void set_guiscreen(gui* new_gui);
    gui* current_guiscreen();

    void set_scene(scene* new_scene);
    scene* current_scene();

    task* create(const std::string &task_name);
    void stop(const std::string &task_name);
    bool is_done(const std::string &task_name);
};