#include "bicudo/bicudo.hpp"

bicudo::profile* bicudo::core {nullptr}; 

void bicudo::init() {
    SDL_Init(SDL_INIT_VIDEO);

    bicudo::core = new bicudo::profile {};
    bicudo::core->do_create();
}

void bicudo::create(bicudo::surface *surf) {
    bicudo::core->dispatch_surface(surf);
}

void bicudo::destroy(bicudo::surface *) {

}

bicudo::gc &bicudo::gc() {
    return bicudo::core->get_custom_garbage_collector();
}

bicudo::logger* bicudo::log() {
    return bicudo::core->get_logger();
}