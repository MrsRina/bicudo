#include "physic_service.h"
#include "rigid/rigid.h"

void physic_service::update_gravity() {
    for (ifeature* &features : this->update_list) {
        rigid* rigid_object = (rigid*) features;
        rigid_object->motion += this->gravity;
    }
}

void physic_service::update_pos() {
    for (ifeature* &features : this->update_list) {
        features->on_locked_update();
    }
}

void physic_service::on_start() {

}

void physic_service::on_end() {

}

void physic_service::on_event(SDL_Event &sdl_event) {
    for (ifeature* &features : this->update_list) {
        features->on_event(sdl_event);
    }
}

void physic_service::on_locked_update() {
    this->update_gravity();
    this->update_pos();
}

void physic_service::on_update() {
    for (ifeature* &features : this->update_list) {
        features->on_update();
    }
}

void physic_service::on_render() {
}