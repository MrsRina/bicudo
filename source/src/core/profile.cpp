#include "bicudo/core/profile.hpp"


void bicudo::profile::do_create_feature(bicudo::feature *feature) {
    switch (feature->mode) {
        case bicudo::features::undefined: {
            break;
        }

        case bicudo::features::module: {
            break;
        }

        case bicudo::features::component: {
            break;
        }

        case bicudo::features::scene: {
            break;
        }

        case bicudo::features::surface: {
            this->surface_native = (bicudo::surface_native*) feature;
            break;
        }
    }
}

void bicudo::profile::do_destroy_feature(bicudo::feature *feature) {

}

void bicudo::profile::do_create() {
    this->logger = new bicudo::logger {"MAIN"};
}

void bicudo::profile::do_destroy() {
}

void bicudo::profile::do_loop() {

}