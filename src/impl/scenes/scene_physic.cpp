#include "scene_physic.h"
#include "api/client/instance.h"
#include "api/render/tessellator.h"
#include "api/physic/rigid.h"
#include "api/util/tag.h"
#include <ekg/ekg.hpp>

scene_physic *scene_physic::instance = nullptr;

void scene_physic::on_start() {
    GLOBAL_WORLD_2D_GRAVITY = math::vec2(0, 9.0f);

    for (uint32_t i = 0; i < 1; i++) {
        auto rigid2d_obj = new rigid2d_rectangle(math::vec2(rand() % 1280, 200 + rand() % 100), rand() % 100, 0.0001f,
                                                 0.2f, rand() % 75, rand() % 75);
        rigid2d_obj->set_physic(rigidutil::physic::FULL);
    }

    player = new rigid2d_rectangle(math::vec2(300, 10), 1.0f, 0.8f, 0.2f, 100.0f, 100.0f);

    new rigid2d_rectangle(math::vec2(400, 10), 900.0f, 0.0f, 0.0f, 1280, 100);
    new rigid2d_rectangle(math::vec2(10, 300), 0.0f, 0.0f, 0.0f, 100, 800);
    new rigid2d_rectangle(math::vec2(400, 600), 0.0f, 0.0f, 0.0f, 1280, 100);
    new rigid2d_rectangle(math::vec2(800, 300), 0.0f, 1.0f, 0.0f, 100, 800);

    tag::set("MoveForward", false);
    tag::set("MoveStrafeLeft", false);
    tag::set("MoveStrafeRight", false);
    tag::set("MoveBack", false);

    ekg::set_font_size(28);

    float axis = 0;

    this->top_bar = ekg::frame();
    this->top_bar->set_pos(0, 0);
    this->top_bar->set_drag_dock(ekg::dock::UNDEFINED);
    this->top_bar->set_resize_dock(ekg::dock::BOTTOM);

    auto check = ekg::button("hi");
    this->top_bar->place(check, 300, 2);

    this->left_bar = ekg::frame();
    this->left_bar->set_pos(0, 0);
    this->left_bar->set_drag_dock(ekg::dock::UNDEFINED);
    this->left_bar->set_resize_dock(ekg::dock::RIGHT);

    this->gravity_setting = ekg::slider(9.0f, 0.0f, 100.0f);
    this->left_bar->place(this->gravity_setting, 10, 10);

    auto combobox = ekg::combobox("hi", "component 1", {"component 1", "component 2", "component 3"});
    this->left_bar->place(combobox, 2, 50);

    the_ekg_core->debug_mode = true;
}

void scene_physic::on_end() {

}

void scene_physic::on_event(SDL_Event &sdl_event) {
    float x, y;

    if (ekgapi::input_up_right(sdl_event, x, y)) {
        auto popup = ekg::popup("popup", {"element 1", "element 2", "element 3"});
        auto popup2 = ekg::popup("element 1", {"thasaturation", "ui 2", "micie 3"});
        auto popup3 = ekg::popup("element 3", {"25", "ui 2", "micie 3"});
        auto popup4 = ekg::popup("ui 2", {"oi", "ui 2", "micie 3"});

        if (popup != nullptr) {
            popup->state("element 3", false);
            popup->place(popup2);
            popup2->place(popup3);
            popup3->place(popup4);
        }
    }

    switch (sdl_event.type) {
        case SDL_USEREVENT: {
            auto event = ekg::event();

            if (event == nullptr) {
                break;
            }

            if (event->type == ekg::ui::POPUP) {
                util::log("Received UI event from ekg: " + event->text);
            }

            if (event->type == ekg::ui::BUTTON) {
                util::log("Received UI event from ekg: " + event->text);

                if (event->text == "hi") {
                    SDL_Event sdl_custom_event;
                    sdl_custom_event.type = SDL_QUIT;
                    sdl_custom_event.quit.type = SDL_QUIT;
                    sdl_custom_event.quit.timestamp = 20;
                    SDL_PushEvent(&sdl_custom_event);
                }
            }

            break;
        }

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

            if (ekg::hovered_element_id() != ekg::ui::NONE) {
                return;
            }

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

            if (k == SDLK_UP) {
                tag::set("MoveForward", true);
            } else if (k == SDLK_LEFT) {
                tag::set("MoveStrafeLeft", true);
            } else if (k == SDLK_RIGHT) {
                tag::set("MoveStrafeRight", true);
            } else if (k == SDLK_DOWN) {
                tag::set("MoveBack", true);
            }

            break;
        }

        case SDL_KEYUP: {
            auto k = sdl_event.key.keysym.sym;

            if (k == SDLK_UP) {
                tag::set("MoveForward", false);
            } else if (k == SDLK_LEFT) {
                tag::set("MoveStrafeLeft", false);
            } else if (k == SDLK_RIGHT) {
                tag::set("MoveStrafeRight", false);
            } else if (k == SDLK_DOWN) {
                tag::set("MoveBack", false);
            }

            break;
        }

        case SDL_MOUSEBUTTONUP: {
            rigid_object = nullptr;
            break;
        }

        case SDL_MOUSEMOTION: {
            float mx = static_cast<float>(sdl_event.motion.x);
            float my = static_cast<float>(sdl_event.motion.y);
        
            bicudo::camera()->update_camera_motion(mx - prev_x, prev_y - my, true);

            prev_x = mx;
            prev_y = my;

            GLOBAL_WORLD_2D_GRAVITY = math::vec2(0.0f, this->gravity_setting->get_value());
            break;
        }
    }
}

void scene_physic::on_locked_update() {
    if (tag::get("MoveForward")) {
        player->velocity.y -= 5;
    }

    if (tag::get("MoveStrafeLeft")) {
        player->velocity.x -= 1;
    }

    if (tag::get("MoveStrafeRight")) {
        player->velocity.x += 1;
    }

    if (tag::get("MoveBack")) {
        bicudo::camera()->position.x -= 1;
    }
}

void scene_physic::on_update() {
    this->top_bar->set_width(static_cast<float>(game_core::screen_width));
    this->left_bar->set_pos(0, this->top_bar->get_height());
    this->left_bar->set_height(static_cast<float>(game_core::screen_height) - this->top_bar->get_height());

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

    //util::log(std::to_string(BICUDO->get_fps()));
}

void scene_physic::on_render() {
    bicudo::service_physic().on_render();
}