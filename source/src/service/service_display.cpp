#include "bicudo/service/service_display.hpp"

bicudo::display &bicudo::service_display::get_display(uint32_t priority) {
    return this->features[priority]->content;
}

void bicudo::service_display::add(bicudo::feature<bicudo::display> *p_feature) {
    if (!this->features.empty()) {
        return;
    }

    service::add(p_feature);
    p_feature->content.on_update();
}
