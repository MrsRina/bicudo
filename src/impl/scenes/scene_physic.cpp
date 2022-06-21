#include "scene_physic.h"
#include "api/client/instance.h"
#include "api/render/tessellator.h"
#include "api/physic/rigid.h"

material material_shape;
rigid2d_rectangle* rigid_object;

scene_physic *scene_physic::instance = nullptr;

float x, y;

void scene_physic::on_start() {
    material_shape.color.set(255, 255, 255, 100);

    rigid_object = new rigid2d_rectangle(math::vec2(10, 10), 200, 0.0f, 0.2f, 30, 30);

    for (uint32_t i = 0; i < 30; i++) {
        rigid2d_rectangle* r = new rigid2d_rectangle(math::vec2(rand() % 1280, rand() % 800), 0, 0.0f, 0.0f, rand() % 60, rand() % 60);
    }

    x = 0, y = 0;

    rigid2d_rectangle* static_objc = new rigid2d_rectangle(math::vec2(600, 600), 0.0f, 0.0f, 0.2f, 1280, 100);
}

void scene_physic::on_end() {

}

void scene_physic::on_event(SDL_Event &sdl_event) {
    switch (sdl_event.type) {
        case SDL_MOUSEBUTTONUP: {
            math::vec2 vec = math::vec2((float) sdl_event.motion.x, (float) sdl_event.motion.y);
            rigid_object->move(vec - rigid_object->center);
            break;
        }
    }
}

void scene_physic::on_locked_update() {

}

void scene_physic::on_update() {
    util::log(std::to_string(BICUDO->get_fps()));
}

void scene_physic::on_render() {
    // Draw physic objects.
    bicudo::service_physic().on_render();
}