#include "scene_physic.h"
#include "api/client/instance.h"
#include "api/render/tessellator.h"
#include "api/physic/rigid/rigid2d.h"

material material_shape;
scene_physic *scene_physic::instance = nullptr;

void scene_physic::on_start() {
    material_shape.color.set(255, 255, 255, 100);
    rigid2d* rigid_object = new rigid2d(100.0f, 100.0f);
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
        rigid* rigid_objects = (rigid2d*) features;

        if (rigid->get_type() == )
        draw::shape::circle(rigid_objects->current_pos.x, rigid_objects->current_pos.y, rigid_objects->radius, material_shape);
    }
}