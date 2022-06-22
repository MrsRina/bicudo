#include "scene_physic.h"
#include "api/client/instance.h"
#include "api/render/tessellator.h"
#include "api/physic/rigid.h"

material material_shape;
rigid2d* rigid_object;

scene_physic *scene_physic::instance = nullptr;

float x, y;

void scene_physic::on_start() {
    for (uint8_t i = 0; i < 30; i++) {
        rigid2d_rectangle* rigid2d_obj = new rigid2d_rectangle(math::vec2(rand() % 1280, 200 + rand() % 100), rand() % 5, 0.0f, 0.2f, rand() % 75, rand() % 75);
    }

    rigid2d_rectangle* rigid2d_obj = new rigid2d_rectangle(math::vec2(400, 600), 0.0f, 0.0f, 0.2f, 1280, 100);
}

void scene_physic::on_end() {

}

void scene_physic::on_event(SDL_Event &sdl_event) {
    switch (sdl_event.type) {
        case SDL_MOUSEBUTTONDOWN: {
            rigid_object = nullptr;

            for (uint32_t i = 0; i < bicudo::service_physic().get_rigid2d_iterator(); i++) {
                rigid_object = bicudo::service_physic().get_rigid2d_list()[i];

                if (rigid2d_collide_with_point(rigid_object, (float) sdl_event.motion.x, (float) sdl_event.motion.y)) {
                    rigid_object = rigid_object;

                    x = (float) sdl_event.motion.x - rigid_object->center.x;
                    y = (float) sdl_event.motion.y - rigid_object->center.y;

                    break;
                }

                rigid_object = nullptr;
            }

            break;
        }
        case SDL_MOUSEBUTTONUP: {
            rigid_object = nullptr;

            break;
        }

        case SDL_MOUSEMOTION: {
            if (rigid_object != nullptr) {
                rigid_object->move(math::vec2((float) sdl_event.motion.x - x, (float) sdl_event.motion.y - y) - rigid_object->center);
                rigid_object->velocity = math::vec2(0, 0);
            }

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
    bicudo::service_physic().on_render();
}