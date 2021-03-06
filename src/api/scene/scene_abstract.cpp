#include "scene_abstract.h"
#include "api/util/util.h"

void scene_abstract::on_start() {

}

void scene_abstract::on_end() {
    
}

void scene_abstract::registry(const std::string &scene_name, const std::string &scene_description) {
    this->name = scene_name;
    this->description = scene_description;
}

void scene_abstract::set_name(const std::string &module_name) {
    this->name = module_name;
}

std::string scene_abstract::get_name() {
    return this->name;
}

void scene_abstract::set_description(const std::string &module_description) {
    this->description = module_description;
}

std::string scene_abstract::get_description() {
    return this->description;
}

void scene_abstract::add(uint32_t feature_id) {
    if (this->contains(feature_id)) {
        util::log(this->get_name() + " feature id " + std::to_string(feature_id) + " already registered.");
        return;
    }

    this->feature_ids.push_back(feature_id);
}

void scene_abstract::remove(uint32_t feature_id) {
    int32_t index = -1;

    for (uint32_t i = 0; i < this->feature_ids.size(); i++) {
        if (this->feature_ids.at(i) == feature_id) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        this->feature_ids.erase(this->feature_ids.begin() + index);
    }
}

bool scene_abstract::contains(uint32_t feature_id) {
    for (uint32_t ids : this->feature_ids) {
        if (ids == feature_id) {
            return true;
        }
    }

    return false;
}