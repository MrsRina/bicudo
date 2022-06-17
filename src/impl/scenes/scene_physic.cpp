#include "scene_physic.h"
#include "api/client/instance.h"
#include "api/render/tessellator.h"
#include "api/physic/rigid/rigid.h"

material material_shape;
scene_physic *scene_physic::instance = nullptr;

void scene_physic::on_start() {
    material_shape.color.set(255, 255, 255, 100);

    rigid* rigid_object = new rigid(100.0f, 100.0f);
    rigid_object->pos = math::vec2(200, 200);
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
    util::log("Physic size list: " + std::to_string(BICUDO->get_physic_manager().get_update_list().size()));

    for (ifeature* &features : BICUDO->get_physic_manager().get_update_list()) {
        rigid* rigid_objects = (rigid*) features; 
        util::log(std::to_string(rigid_objects->pos.x));

        draw::shape::circle(rigid_objects->pos.x, rigid_objects->pos.y, rigid_objects->radius, material_shape);
    }
}