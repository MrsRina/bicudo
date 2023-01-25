#include "bicudo/bicudo.hpp"
#include "bicudo/opengl/opengl_context_overview.hpp"

bicudo::core *bicudo::kernel::p_core {};

void bicudo::createcore(bicudo::core *&p_core) {
    bicudo::kernel::p_core = p_core;
    bicudo::initglcontext();
    bicudo::log("Kernel core created.");
}

void bicudo::createdisplay(bicudo::feature<bicudo::display> *&p_feature) {
    bicudo::kernel::p_core->service_display.add(p_feature);
}

void bicudo::createscene(bicudo::feature<bicudo::scene *> *&p_feature) {
    bicudo::kernel::p_core->service_scene.add(p_feature);
}