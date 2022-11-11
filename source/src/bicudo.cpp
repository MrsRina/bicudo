#include "bicudo/bicudo.hpp"
#include "bicudo/gpu/shading_program.hpp"

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

bicudo::garbage_collector &bicudo::gc() {
    return bicudo::core->get_custom_gc();
}

bicudo::logger* bicudo::log() {
    return bicudo::core->get_logger();
}

void bicudo::create(bicudo::shader *shader, const std::vector<bicudo::resource> &resources) {
    bicudo::create_shading_program(shader->shading_program_id, resources);
}

void bicudo::mainloop() {
    bicudo::core->do_loop();
}
