#include "rigid2d.h"
#include "api/client/instance.h"

rigid2d::rigid2d() {
    this->set_type(RIGID_TYPE_RIGID2D);
    this->set_visibility_flag(util::visibility::LOW_PRIORITY);

    BICUDO->get_physic_manager().add((ifeature*)  this);
}

rigid2d::rigid2d(float val_radius, float val_mass) {
    this->radius = val_radius;
    this->mass = val_mass;

    this->set_type(RIGID_TYPE_RIGID2D);
    this->set_visibility_flag(util::visibility::LOW_PRIORITY);

    BICUDO->get_physic_manager().add((ifeature*) this);
}

void rigid2d::on_event(SDL_Event &sdl_event) {

}

void rigid2d::on_locked_update() {
    const math::vec2 velocity = current_pos - previous_pos;
    previous_pos = current_pos;

    current_pos = current_pos + velocity + motion * util::timing->locked_delta_time * util::timing->locked_delta_time;
    motion = {};
}

void rigid2d::on_update() {

}