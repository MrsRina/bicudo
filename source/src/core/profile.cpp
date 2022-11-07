#include "bicudo/core/profile.hpp"

void bicudo::profile::do_create() {
    this->logger = new bicudo::logger {"MAIN"};
}

void bicudo::profile::do_destroy() {
}

void bicudo::profile::do_loop() {

}

void bicudo::profile::dispatch_surface(bicudo::surface *surf) {
    this->surfaces.push_back(surf);
}