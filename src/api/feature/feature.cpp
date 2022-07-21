#include "feature.h"
#include "api/util/util.h"

ifeature::ifeature() {
    // Constructor.
    
    // for default a low priority can be cool (no render).
    this->set_visibility_flag(util::visibility::LOW_PRIORITY);
}

ifeature::~ifeature() {
    // Destructor.
}

void ifeature::set_feature_id(uint32_t id) {
    this->feature_id = id;
}

uint32_t ifeature::get_feature_id() {
    return this->feature_id;
}

void ifeature::set_visibility_flag(unsigned int flag) {
    this->visibility = flag;
}

unsigned int ifeature::get_visibility() {
    return this->visibility;
}

void ifeature::set_alive_state(bool state) {
    this->alive = state;
}

bool ifeature::is_alive() {
    return this->alive;
}