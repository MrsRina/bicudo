#include "physic_service.h"
#include "api/physic/rigid/abstract_rigid.h"

void physic_service::update_gravity() {
    for (ifeature* &features : this->update_list) {
        auto rigid_object = (abstract_rigid*) features;
        rigid_object->on_update_gravity();
    }
}

void physic_service::update_pos() {
    for (ifeature* &features : this->update_list) {
        auto rigid_object = (abstract_rigid*) features;
        rigid_object->on_update_position();
    }
}

void physic_service::on_start() {

}

void physic_service::on_end() {

}

void physic_service::on_event(SDL_Event &sdl_event) {

}

void physic_service::on_locked_update() {
    this->update_gravity();
    this->update_pos();
}

void physic_service::on_update() {

}

void physic_service::on_render() {

}