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
    GLOBAL_WORLD_2D_GRAVITY.y = 0.0f;

    for (uint32_t i = 0; i < 40; i++) {
       auto rigid2d_obj = new rigid2d_rectangle(math::vec2(rand() % 1280, 200 + rand() % 100), rand() % 100, 200.0f, 0.2f, rand() % 75, rand() % 75);
       rigid2d_obj->set_physic(rigid::physic::FULL);
    }

    new rigid2d_rectangle(math::vec2(400, 10), 0.0f, 0.0f, 0.0f, 1280, 100);
    new rigid2d_rectangle(math::vec2(10, 300), 0.0f, 1.0f, 0.0f, 100, 800);
    new rigid2d_rectangle(math::vec2(400, 600), 0.0f, 0.0f, 0.0f, 1280, 100);
    new rigid2d_rectangle(math::vec2(800, 300), 0.0f, 1.0f, 0.0f, 100, 800);

    tag::set("MoveForward", false);
    tag::set("MoveStrafeLeft", false);
    tag::set("MoveStrafeRight", false);
    tag::set("MoveBack", false);

    auto button = ekg::button("hello");
    auto frame = ekg::frame();
    auto frame2 = ekg::frame();

    frame->set_pos(100, 50);
    frame->set_drag_dock(ekg::dock::TOP);
    frame->set_drag_offset(30.0f);

    frame2->set_pos(80, 90);
    frame2->set_size(300, 300);

    frame2->set_resize_dock(ekg::dock::LEFT | ekg::dock::BOTTOM | ekg::dock::RIGHT);
    frame2->set_drag_dock(ekg::dock::TOP);
    frame2->set_drag_offset(30.0f);
    frame2->set_resize_offset(30.0f);

    frame2->place(button, 10, 10);
}

void scene_physic::on_end() {

}

void scene_physic::on_event(SDL_Event &sdl_event) {
    switch (sdl_event.type) {
        case SDL_MOUSEWHEEL: {
            float s = sdl_event.wheel.preciseY;

            if (rigid_object != nullptr) {
                rigid_object->angular_velocity = s * (float) sin(SDL_GetTicks64());
            }

            break;
        }

        case SDL_MOUSEBUTTONDOWN: {
            bicudo::camera()->position.z -= 50;

            rigid_object = nullptr;

            for (uint32_t i = 0; i < bicudo::service_physic().get_rigid2d_iterator(); i++) {
                rigid_object = bicudo::service_physic().get_rigid2d_list()[i];

                if (rigid2d_collide_with_point(rigid_object, (float) sdl_event.motion.x, (float) sdl_event.motion.y)) {
                    cx = (float) sdl_event.motion.x - rigid_object->minx;
                    cy = (float) sdl_event.motion.y - rigid_object->miny;

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
            rigid_object = nullptr;

            break;
        }

        case SDL_MOUSEMOTION: {
            float mx = (float) sdl_event.motion.x;
            float my = (float) sdl_event.motion.y;
        
            bicudo::camera()->update_camera_motion(mx - prev_x, prev_y - my, true);

            prev_x = mx;
            prev_y = my;

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
    if (rigid_object != nullptr) {
        x = prev_x - (rigid_object->minx + cx);
        y = prev_y - (rigid_object->miny + cy);

        math::vec2 delta = math::vec2(x, y);

        if (rigid_object->mass == 0.0f) {
            rigid_object->move(delta);
        } else {
            rigid_object->velocity = delta;
        }
    }
}

void scene_physic::on_render() {
    bicudo::service_physic().on_render();
}