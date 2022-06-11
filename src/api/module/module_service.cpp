#include "module_service.h"

module* module_service::get_module_by_name(const std::string &name) {
    for (ifeature* &features : this->update_list) {
        module* modules = (module*) features;

        if (modules->get_name() == name) {
            return (module*) modules;
        }
    }

    return nullptr;
}

module* module_service::get_module_by_feature_id(uint32_t feature_id) {
    for (ifeature* &modules : this->update_list) {
        if (modules->get_feature_id() == feature_id) {
            return (module*) modules;
        }
    }

    return nullptr;
}

void module_service::on_start() {
    service::on_start();
}

void module_service::on_end() {
    service::on_end();
}

void module_service::on_event(SDL_Event &sdl_event) {
    for (ifeature* &feature : this->update_list) {
        feature->on_event(sdl_event);
    }
}

void module_service::on_locked_update() {
    for (ifeature* &feature : this->update_list) {
        feature->on_locked_update();
    }
}

void module_service::on_update() {
    for (ifeature* &feature : this->update_list) {
        feature->on_update();
    }
}

void module_service::on_render() {
    for (ifeature* &feature : this->render_list) {
        feature->on_render();
    }
}