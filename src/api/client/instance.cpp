#include "instance.h"

game_core* const BICUDO = new game_core();

void bicudo::set_guiscreen(gui* new_gui) {
    BICUDO->set_guiscreen(new_gui);
}

gui* bicudo::current_guiscreen() {
    return BICUDO->get_guiscreen();
}

void bicudo::set_scene(scene* new_scene) {
    BICUDO->get_scene_manager().start(new_scene);
}

scene* bicudo::current_scene() {
    return BICUDO->get_scene_manager().get_current_scene();
}

task* bicudo::create(const std::string &task_name) {
    return BICUDO->get_task_manager().start(task_name);
}

void bicudo::stop(const std::string &task_name) {
    BICUDO->get_task_manager().end(BICUDO->get_task_manager().get_task_by_name(task_name));
}

bool bicudo::is_task_done(const std::string &task_name) {
    
}