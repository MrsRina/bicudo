#include "feature.h"

ifeature::ifeature() {
    // Constructor.
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