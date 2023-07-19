#include "bicudo/bicudo.hpp"

bicudo::core *bicudo::kernel::p_core {};

void bicudo::createcore(bicudo::coreproperty &core_property, bicudo::core *p_core) {
    bicudo::kernel::p_core = p_core;
    bicudo::log() << "Kernel core created";
    p_core->set_core_property(core_property);
}

void bicudo::createdisplay(bicudo::displayproperty &display_property, bicudo::display *p_display) {
    bicudo::kernel::p_core->p_display_service->add(p_display);
    bicudo::kernel::p_core->p_display_service->update(display_property, p_display);
}

void bicudo::createscene(bicudo::scene *p_scene) {
    bicudo::kernel::p_core->p_scene_service->add(p_scene);
}

void bicudo::startscene(bicudo::scene *p_scene, bool reload) {
    bicudo::kernel::p_core->p_scene_service->start(p_scene, reload);
}

void bicudo::createasset(bicudo::assetdescriptor &asset_descriptor, bicudo::asset *p_asset) {
    bicudo::kernel::p_core->p_asset_service->registry(asset_descriptor, p_asset);
}

bicudo::asset *bicudo::getasset(std::string_view tag) {
    return bicudo::kernel::p_core->p_asset_service->get(tag);
}