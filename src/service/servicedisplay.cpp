#include "bicudo/service/servicedisplay.hpp"

bicudo::display &bicudo::servicedisplay::get_display(uint32_t priority) {
    return this->features[priority]->content;
}

void bicudo::servicedisplay::add(bicudo::feature<bicudo::display> *p_feature) {
    if (!this->features.empty()) {
        return;
    }

    service::add(p_feature);
    p_feature->content.on_update();
}
