#include "bicudo/bicudo.hpp"

bicudo::core *bicudo::kernel::p_core {};
int32_t bicudo::toplevel {};

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