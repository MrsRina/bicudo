#include "physic_scene.h"

physic_scene *physic_scene::instance = nullptr;

void physic_scene::set_pos(double pos_x, double pos_y, double pos_z) {
    this->x = pos_x;
    this->y = pos_y;
    this->z = pos_z;
}

void physic_scene::on_start() {

}

void physic_scene::on_end() {

}

void physic_scene::on_event(SDL_Event &sdl_event) {

}

void physic_scene::on_locked_update(uint64_t delta) {

}

void physic_scene::on_update(uint64_t delta) {

}

void physic_scene::on_render(float render_time) {

}