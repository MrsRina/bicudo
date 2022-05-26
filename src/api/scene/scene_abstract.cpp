#include "scene_abstract.h"
#include "api/util/util.h"

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

    if (util::debug_scene) {
        util::log(this->get_name() + " feature " + std::to_string(feature_id) + " registered.");
    }
}

void scene_abstract::remove(uint32_t feature_id) {
    if (!this->contains(feature_id)) {
        util::log(this->get_name() + " feature id " + std::to_string(feature_id) + " not registered.");
        return;
    }

    uint32_t index = NULL;

    for (uint32_t i = 0; i < this->feature_ids.size(); i++) {
        if (this->feature_ids.at(i) == feature_id) {
            index = i;
            break;
        }
    }

    if (index != NULL) {
        this->feature_ids.erase(this->feature_ids.begin() + index);

        if (util::debug_scene) {
            util::log(this->get_name() + " feature " + std::to_string(feature_id) + " removed.");
        }
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