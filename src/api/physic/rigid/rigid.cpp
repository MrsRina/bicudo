#include "rigid.h"
#include "api/client/instance.h"

rigid::rigid() {
    this->set_visibility_flag(util::visibility::LOW_PRIORITY);
    BICUDO->get_physic_manager().add((ifeature*)  this);
}

rigid::rigid(float val_radius, float val_mass) {
    this->radius = val_radius;
    this->mass = val_mass;

    this->set_visibility_flag(util::visibility::LOW_PRIORITY);
    BICUDO->get_physic_manager().add((ifeature*) this);
}

void rigid::on_event(SDL_Event &sdl_event) {

}

void rigid::on_locked_update() {
    const math::vec2 velocity = pos - previous_pos;
    previous_pos = pos;

    pos = pos + velocity + motion * util::timing->locked_delta_time * util::timing->locked_delta_time;
    motion = {};
}

void rigid::on_update() {

}

void rigid::on_render() {

}