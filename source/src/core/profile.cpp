#include "bicudo/core/profile.hpp"

void bicudo::profile::do_create() {
    this->logger = new bicudo::logger {"MAIN"};
    this->mainloop = true;
}

void bicudo::profile::do_destroy() {
}

void bicudo::profile::do_loop() {
    while (this->mainloop) {
    }
}

void bicudo::profile::dispatch_surface(bicudo::surface *surf) {
    this->surfaces.push_back(surf);
}

bicudo::gc &bicudo::profile::gc() {
    return this->custom_gc;
}
