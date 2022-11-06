#include "bicudo/bicudo.hpp"

bicudo::profile* bicudo::core {nullptr}; 

void bicudo::init() {
    bicudo::core = new bicudo::profile {};
    bicudo::core->do_create();
}

void bicudo::create(bicudo::feature *feature) {
    bicudo::core->do_create_feature(feature);
}

void bicudo::destroy(bicudo::feature *feature) {
    bicudo::core->do_destroy_feature(feature);
}