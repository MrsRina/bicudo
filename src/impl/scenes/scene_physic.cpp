#include "scene_physic.h"
#include "api/client/instance.h"
#include "api/render/tessellator.h"
#include "api/physic/rigid.h"

material material_shape;
rigid2d* rigid_object;

scene_physic *scene_physic::instance = nullptr;

float x, y;

void scene_physic::on_start() {
    material_shape.color.set(255, 255, 255, 100);

    rigid_object = new rigid2d(math::vec2(200, 200), 100, 100);
    x = 0, y = 0;

    rigid2d* static_objc = new rigid2d(math::vec2(10, 300), 800, 100);
    static_objc->no_gravity = true;
}

void scene_physic::on_end() {

}

void scene_physic::on_event(SDL_Event &sdl_event) {
    switch (sdl_event.type) {
        case SDL_MOUSEBUTTONUP: {
            math::vec2 vec = math::vec2((float) sdl_event.motion.x, (float) sdl_event.motion.y);
            rigid_object->set_pos(vec);
            break;
        }
    }
}

void scene_physic::on_locked_update() {

}

void scene_physic::on_update() {
    
}

void scene_physic::on_render() {
    for (ifeature* &features : BICUDO->get_physic_manager().get_update_list()) {
        auto obj = (abstract_rigid *) features;

        if (obj->get_type() == rigid::type::RIGID2D) {
            auto rigid2d_object = (rigid2d *) obj;
            draw::shape::rect(rigid2d_object->get_vertices()[0]->position.x, rigid2d_object->get_vertices()[0]->position.y, rigid2d_object->width, rigid2d_object->height, material_shape);
        }
    }
}