#include "scene_physic.h"
#include "api/client/instance.h"
#include "api/render/tessellator.h"
#include "api/physic/rigid.h"
#include "api/util/tag.h"

material material_shape;
rigid2d* rigid_object;

scene_physic *scene_physic::instance = nullptr;
draw::mesh3d_instanced mesh;

float cx, cy, x, y, prev_x, prev_y;
bool moving;

void scene_physic::on_start() {

    for (uint32_t i = 0; i < 40; i++) {
       auto rigid2d_obj = new rigid2d_rectangle(math::vec2(rand() % 1280, 200 + rand() % 100), 200.0f, 1.0f, 0.2f, rand() % 75, rand() % 75);
       rigid2d_obj->set_physic(rigid::physic::POS);
    }

    auto rigid2d_obj = new rigid2d_rectangle(math::vec2(400, 600), 0.0f, 1.0f, 0.0f, 1280, 100);
    auto r2 = new rigid2d_rectangle(math::vec2(400, 600), 0.0f, 1.0f, 0.0f, 100, 800);

    tag::set("MoveForward", false);
    tag::set("MoveStrafeLeft", false);
    tag::set("MoveStrafeRight", false);
    tag::set("MoveBack", false);
}

void scene_physic::on_end() {

}

void scene_physic::on_event(SDL_Event &sdl_event) {
    switch (sdl_event.type) {
        case SDL_MOUSEBUTTONDOWN: {
            bicudo::camera()->position.z -= 50;

            rigid_object = nullptr;

            for (uint32_t i = 0; i < bicudo::service_physic().get_rigid2d_iterator(); i++) {
                rigid_object = bicudo::service_physic().get_rigid2d_list()[i];

                if (rigid2d_collide_with_point(rigid_object, (float) sdl_event.motion.x, (float) sdl_event.motion.y)) {
                    cx = (float) sdl_event.motion.x - rigid_object->center.x;
                    cy = (float) sdl_event.motion.y - rigid_object->center.y;

                    break;
                }

                rigid_object = nullptr;
            }

            break;
        }

        case SDL_KEYDOWN: {
            auto k = sdl_event.key.keysym.sym;

            if (k == SDLK_w) {
                tag::set("MoveForward", true);
            } else if (k == SDLK_a) {
                tag::set("MoveStrafeLeft", true);
            } else if (k == SDLK_d) {
                tag::set("MoveStrafeRight", true);
            } else if (k == SDLK_s) {
                tag::set("MoveBack", true);
            }

            break;
        }

        case SDL_KEYUP: {
            auto k = sdl_event.key.keysym.sym;

            if (k == SDLK_w) {
                tag::set("MoveForward", false);
            } else if (k == SDLK_a) {
                tag::set("MoveStrafeLeft", false);
            } else if (k == SDLK_d) {
                tag::set("MoveStrafeRight", false);
            } else if (k == SDLK_s) {
                tag::set("MoveBack", false);
            }

            break;
        }

        case SDL_MOUSEBUTTONUP: {
            if (rigid_object != nullptr) {
                rigid_object->velocity = math::vec2(0, 0);
            }

            rigid_object = nullptr;

            break;
        }

        case SDL_MOUSEMOTION: {
            float mx = (float) sdl_event.motion.x;
            float my = (float) sdl_event.motion.y;
        
            bicudo::camera()->update_camera_motion(mx - prev_x, prev_y - my, true);

            prev_x - mx;
            prev_y = my;

            if (rigid_object != nullptr) {
                x = ((mx - cx) - rigid_object->center.x);
                y = ((my - cy) - rigid_object->center.y);

                math::vec2 delta = math::vec2(x, y);
                rigid_object->velocity = delta;
            }

            break;
        }
    }
}

void scene_physic::on_locked_update() {
    if (tag::get("MoveForward")) {
        bicudo::camera()->position.x += 1;
    }

    if (tag::get("MoveStrafeLeft")) {
        bicudo::camera()->position.z -= 1;
    }

    if (tag::get("MoveStrafeRight")) {
        bicudo::camera()->position.z += 1;
    }

    if (tag::get("MoveBack")) {
        bicudo::camera()->position.x -= 1;
    }
}

void scene_physic::on_update() {

}

void scene_physic::on_render() {
    bicudo::service_physic().on_render();
}