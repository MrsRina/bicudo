#include "scene_physic.h"
#include "api/client/instance.h"
#include "api/render/tessellator.h"
#include "api/physic/rigid.h"
#include "api/util/tag.h"
#include <ekg/ekg.hpp>

scene_physic *scene_physic::instance = nullptr;

void scene_physic::on_start() {
    GLOBAL_WORLD_2D_GRAVITY = math::vec2(0, 9.0f);

    player = new rigid2d_rectangle(math::vec2(300, 10), 20.0f, 0.0001f, 0.2f, 100.0f, 50.0f);
    player->set_physic(rigidutil::physic::FULL);

    for (uint32_t i = 0; i < 200; i++) {
        auto rigid2d_obj = new rigid2d_rectangle(math::vec2(rand() % 1280, 200 + rand() % 100), rand() % 100, 0.0001f,
                                                 0.2f, 75, 75);
        rigid2d_obj->set_physic(rigidutil::physic::FULL);
    }

    new rigid2d_rectangle(math::vec2(400, 10), 0.0f, 0.2f, 1.0f, 1280, 100);
    new rigid2d_rectangle(math::vec2(10, 300), 0.0f, 0.0f, 0.0f, 100, 800);
    new rigid2d_rectangle(math::vec2(400, 600), 0.0f, 0.2f, 0.2f, 1280, 100);
    new rigid2d_rectangle(math::vec2(800, 300), 0.0f, 0.2f, 0.2f, 100, 800);

    tag::set("MoveForward", false);
    tag::set("MoveStrafeLeft", false);
    tag::set("MoveStrafeRight", false);
    tag::set("MoveBack", false);

    ekg::set_font("data/fonts/font-kit-jetbrains-mono/ttf/JetBrainsMono-Bold.ttf");
    ekg::set_font_size(26);

    float axis = 0;

    this->frame_text_box = ekg::frame();
    this->frame_text_box->set_resize_dock(ekg::dock::BOTTOM | ekg::dock::LEFT | ekg::dock::RIGHT);
    this->frame_text_box->set_drag_dock(ekg::dock::TOP);
    this->frame_text_box->set_drag_offset(30.0f);
    this->frame_text_box->set_pos(400, 300);

    this->text_box = ekg::textbox();
    this->text_box->set_text("hi hi");
    this->text_box->set_max_rows(14);
    this->frame_text_box->place(this->text_box, 10, 10);

    this->top_bar = ekg::frame();
    this->top_bar->set_pos(0, 0);
    this->top_bar->set_drag_dock(ekg::dock::UNDEFINED);

    auto check = ekg::button("Exit");
    this->top_bar->place(check, 1, 1);

    this->left_bar = ekg::frame();
    this->left_bar->set_pos(0, 0);
    this->left_bar->set_drag_dock(ekg::dock::UNDEFINED);
    this->left_bar->set_resize_dock(ekg::dock::RIGHT);

    this->gravity_setting = ekg::slider(9.0f, 0.0f, 100.0f);
    this->left_bar->place(this->gravity_setting, 10, 10);

    auto combobox = ekg::checkbox("Acc-Angular");
    auto comobobobo = ekg::combobox("oi oi modos", "modo 1", {"modo 1", "modo 2", "modo 3", "modo 4"});
    combobox->set_checked(true);
    comobobobo->set_width(150);

    this->left_bar->place(combobox, 10, 50);
    this->left_bar->place(comobobobo, 10, combobox->get_y() + combobox->get_height() + 5);
    this->top_bar->set_height(33);

    ekg::core->debug_mode = false;

    geometry_mesh mesh;

    // face 1
    mesh.push_back(0.0f, 0.0f, 0.0f); mesh.push_back(0.0f, 0.0f);
    mesh.push_back(0.0f, 1.0f, 0.0f); mesh.push_back(0.0f, 0.0f);
    mesh.push_back(1.0f, 1.0f, 0.0f); mesh.push_back(0.0f, 0.0f);
    mesh.push_back(1.0f, 1.0f, 0.0f); mesh.push_back(0.0f, 0.0f);
    mesh.push_back(1.0f, 0.0f, 0.0f); mesh.push_back(0.0f, 0.0f);
    mesh.push_back(0.0f, 0.0f, 0.0f); mesh.push_back(0.0f, 0.0f);

    // face 2
    mesh.push_back(0.0f, 1.0f, 0.0f); mesh.push_back(0.0f, 0.0f);
    mesh.push_back(0.0f, 1.0f, 1.0f); mesh.push_back(0.0f, 0.0f);
    mesh.push_back(1.0f, 1.0f, 1.0f); mesh.push_back(0.0f, 0.0f);
    mesh.push_back(1.0f, 1.0f, 1.0f); mesh.push_back(0.0f, 0.0f);
    mesh.push_back(1.0f, 1.0f, 0.0f); mesh.push_back(0.0f, 0.0f);
    mesh.push_back(0.0f, 1.0f, 0.0f); mesh.push_back(0.0f, 0.0f);

    // face 3
    mesh.push_back(0.0f, 0.0f, 0.0f); mesh.push_back(0.0f, 0.0f);
    mesh.push_back(0.0f, 0.0f, 1.0f); mesh.push_back(0.0f, 0.0f);
    mesh.push_back(0.0f, 1.0f, 1.0f); mesh.push_back(0.0f, 0.0f);
    mesh.push_back(0.0f, 1.0f, 1.0f); mesh.push_back(0.0f, 0.0f);
    mesh.push_back(0.0f, 1.0f, 0.0f); mesh.push_back(0.0f, 0.0f);
    mesh.push_back(0.0f, 0.0f, 0.0f); mesh.push_back(0.0f, 0.0f);

    // face 4
    mesh.push_back(1.0f, 0.0f, 0.0f); mesh.push_back(0.0f, 0.0f);
    mesh.push_back(1.0f, 0.0f, 1.0f); mesh.push_back(0.0f, 0.0f);
    mesh.push_back(1.0f, 1.0f, 1.0f); mesh.push_back(0.0f, 0.0f);
    mesh.push_back(1.0f, 1.0f, 1.0f); mesh.push_back(0.0f, 0.0f);
    mesh.push_back(1.0f, 1.0f, 0.0f); mesh.push_back(0.0f, 0.0f);
    mesh.push_back(1.0f, 0.0f, 0.0f); mesh.push_back(0.0f, 0.0f);

    this->batch.invoke();
    this->batch.dispatch_geometry(mesh);
    this->batch.revoke();
}

void scene_physic::on_end() {

}

void scene_physic::on_event(SDL_Event &sdl_event) {
    float x, y;

    if (ekgapi::input_up_right(sdl_event, x, y)) {
        if (this->rigid_object == nullptr) {
            auto popup = ekg::popup("popup", {"Add"});
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

                if (event->text == "popup | Add") {
                   x = ekgapi::display_interact_x;
                   y = ekgapi::display_interact_y;

                   bicudo::camera2d().subtract_pos(x, y);
                   auto rigid2d_obj = new rigid2d_rectangle(math::vec2(x, y), rand() % 100, 0.0001f,
                                                             0.2f, rand() % 75, rand() % 75);
                }
            }

            if (event->type == ekg::ui::BUTTON) {
                util::log("Received UI event from ekg: " + event->text);

                if (event->text == "Exit") {
                    SDL_Event sdl_custom_event;
                    sdl_custom_event.type = SDL_QUIT;
                    sdl_custom_event.quit.type = SDL_QUIT;
                    sdl_custom_event.quit.timestamp = 20;
                    SDL_PushEvent(&sdl_custom_event);
                }
            }

            if (event->type == ekg::ui::CHECKBOX) {
                util::log("Received UI event from ekg: " + event->text);

                if (event->text == "Acc-Angular") {
                    for (uint32_t i = 0; i < bicudo::service_physic().get_rigid2d_iterator(); i++) {
                        bicudo::service_physic().get_rigid2d_list()[i]->set_physic(event->boolean ? rigidutil::physic::FULL : rigidutil::physic::POS);
                    }
                }
            }

            break;
        }

        case SDL_MOUSEWHEEL: {
            float s = sdl_event.wheel.preciseY;

            if (s > 0) {
                bicudo::camera2d().rect.w++;
                bicudo::camera2d().rect.h++;
            } else {
                bicudo::camera2d().rect.w--;
                bicudo::camera2d().rect.h--;
            }

            break;
        }

        case SDL_MOUSEBUTTONDOWN: {
            bicudo::camera()->position.z -= 50;

            rigid_object = nullptr;
            moving_camera = false;

            if (ekg::hovered_element_id() != ekg::ui::NONE) {
                return;
            }

            switch (sdl_event.button.button) {
                case SDL_BUTTON_LEFT: {
                    auto mx = static_cast<float>(sdl_event.motion.x);
                    auto my = static_cast<float>(sdl_event.motion.y);

                    BICUDO->get_camera2d().subtract_pos(mx, my);

                    for (uint32_t i = 0; i < bicudo::service_physic().get_rigid2d_iterator(); i++) {
                        rigid_object = bicudo::service_physic().get_rigid2d_list()[i];

                        if (rigid2d_collide_with_point(rigid_object, mx, my)) {
                            cx = static_cast<float>(sdl_event.motion.x) - rigid_object->minx;
                            cy = static_cast<float>(sdl_event.motion.y) - rigid_object->miny;

                            break;
                        }

                        rigid_object = nullptr;
                    }

                    break;
                }

                case SDL_BUTTON_MIDDLE: {
                    cx = static_cast<float>(sdl_event.motion.x) - bicudo::camera2d().rect.x;
                    cy = static_cast<float>(sdl_event.motion.y) - bicudo::camera2d().rect.y;
                    moving_camera = true;
                    break;
                }
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
            moving_camera = false;
            break;
        }

        case SDL_MOUSEMOTION: {
            auto mx = static_cast<float>(sdl_event.motion.x);
            auto my = static_cast<float>(sdl_event.motion.y);

            if (moving_camera) {
                bicudo::camera2d().rect.x = mx - cx;
                bicudo::camera2d().rect.y = my - cy;
            }
        
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
    this->text_box->set_pos(10, 10);
    this->text_box->set_size(this->frame_text_box->get_width() - (10 * 2), this->frame_text_box->get_height() - (10 * 2));

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
    this->batch.draw(glm::vec3(0, 0, 10), glm::mat4(1.0), math::vec4(255, 255, 255, 255));
}