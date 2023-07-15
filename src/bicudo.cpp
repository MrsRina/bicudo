#include "bicudo/bicudo.hpp"

bicudo::core *bicudo::kernel::p_core {};

void bicudo::createcore(bicudo::core *p_core) {
    bicudo::kernel::p_core = p_core;
    bicudo::log() << "Kernel core created";
}

void bicudo::createdisplay(bicudo::display *p_display) {
    bicudo::kernel::p_core->p_display_service->add(p_display);
}

void bicudo::createscene(bicudo::scene *p_scene) {
    bicudo::kernel::p_core->p_scene_service->add(p_scene);
}

void bicudo::startscene(bicudo::scene *p_scene, bool reload) {
    bicudo::kernel::p_core->p_scene_service->start(p_scene, reload);
}