#include "scene_physic.h"
#include "api/client/instance.h"
#include "api/render/tessellator.h"
#include "api/physic/rigid.h"

material material_shape;
scene_physic *scene_physic::instance = nullptr;

void scene_physic::on_start() {
    material_shape.color.set(255, 255, 255, 100);

    auto rigid_object = new rigid2d(100.0f, 100.0f);
}

void scene_physic::on_end() {

}

void scene_physic::on_event(SDL_Event &sdl_event) {

}

void scene_physic::on_locked_update() {

}

void scene_physic::on_update() {
    
}

void scene_physic::on_render() {
    for (ifeature* &features : BICUDO->get_physic_manager().get_update_list()) {
        auto rigid_object = (abstract_rigid *) features;

        if (rigid_object->get_type() == rigid::type::RIGID2D) {
            auto rigid2d_object = (rigid2d *) rigid_object;
            draw::shape::circle(rigid2d_object->current_pos.x, rigid2d_object->current_pos.y, rigid2d_object->radius, material_shape);
        }
    }
}