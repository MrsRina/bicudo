#include "service.h"

void service::set_name(const std::string &service_name) {
    this->name = service_name;
}

std::string service::get_name() {
    return this->name;
}

void service::add(ifeature* feature) {
    this->update_list.push_back(feature);

    if (feature->get_visibility() == util::visibility::VISIBLE) {
        this->render_list.push_back(feature);
    }
}

void service::remove(ifeature* feature) {
    int32_t index = -1;
    ifeature* found_feature = nullptr;

    for (uint32_t i = 0; i < this->update_list.size(); i++) {
        if (this->update_list.at(i) == feature) {
            found_feature = feature;
            index = i;
            break;
        }
    }

    if (index != -1) {
        this->update_list.erase(this->update_list.begin() + index);
    }

    index = -1;

    for (uint32_t i = 0; i < this->render_list.size(); i++) {
        if (this->render_list.at(i) == feature) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        this->render_list.erase(this->render_list.begin() + index);
    }

    if (found_feature != nullptr) {
        delete found_feature;
    }
}

bool service::contains(ifeature* feature) {
    for (ifeature* features : this->update_list) {
        if (features == feature) {
            return true;
        }
    }

    return false;
}

std::vector<ifeature*> &service::get_update_list() {
    return this->update_list;
}

std::vector<ifeature*> &service::get_render_list() {
    return this->render_list;
}

void service::on_start() {
    util::log(this->get_name() + " service invoke.");
}

void service::on_end() {
    util::log(this->get_name() + " service end.");
}

void service::on_event(SDL_Event &sdl_event) {

}

void service::on_locked_update() {

}

void service::on_update() {

}

void service::on_render() {

}