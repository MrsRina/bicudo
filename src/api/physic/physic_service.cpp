#include "physic_service.h"
#include "api/client/instance.h"

void physic_service::update_gravity() {
}

void physic_service::update_pos() {
    for (uint32_t i = 0; i < this->rigid2d_iterator; i++) {
        this->rigid2d_list[i]->on_update_position();
    }
}

void physic_service::on_start() {
    this->shape_builder.set_default_depth_dist(0.0f);
}

void physic_service::on_end() {

}

void physic_service::on_event(SDL_Event &sdl_event) {

}

void physic_service::on_locked_update() {
    this->update_pos();
    uint8_t i = 0;

    for (i = 0; i < this->setting_iterations_count; i++) {
        for (this->x = 0; x < this->rigid2d_iterator; x++) {
            rigid2d* &rigid_obj1 = this->rigid2d_list[this->x];

            for (this->y = 0; y < this->rigid2d_iterator; y++) {
                rigid2d* &rigid_obj2 = this->rigid2d_list[this->y];

                if (rigid_obj1 == rigid_obj2 || !rigid_obj1->collide_axis_with(rigid_obj2)) {
                    continue;
                }

                if (rigid_obj1->collide_axis_with(rigid_obj2)) {
                    rigid2d_solve_collide(rigid_obj1, rigid_obj2);
                }
            }
        }
    }
}

void physic_service::on_update() {
}

void physic_service::on_render() {
    this->shape_builder.invoke();

    float cx = 0;
    float cy = 0;
    float cw = 0;
    float ch = 0;

    rigid2d* rigid2d_obj;

    for (uint32_t i = 0; i < this->rigid2d_iterator; i++) {
        rigid2d_obj = this->rigid2d_list[i];

        if (rigid2d_obj->get_type() == rigidutil::type::RIGID2D_RECTANGLE) {
            auto rigid2d_rect_obj = (rigid2d_rectangle*) rigid2d_obj;

            cw = rigid2d_rect_obj->w;
            ch = rigid2d_rect_obj->h;
            cx = rigid2d_rect_obj->center.x - (cw / 2);
            cy = rigid2d_rect_obj->center.y - (ch / 2);
            
            BICUDO->get_camera2d().add(cx, cy, cw, ch);

            this->shape_builder.build(draw::shape::RECT, math::vec4(0.0f, 1.0f, 1.0f, 1.0f));
            this->shape_builder.rotate(rigid2d_obj->angle);
            this->shape_builder.draw(cx, cy, cw, ch);
        }
    }

    this->shape_builder.revoke();
}

void physic_service::add_rigid2d(rigid2d *rigid2d_body) {
    this->rigid2d_list[this->rigid2d_iterator++] = rigid2d_body;
}

std::array<rigid2d*, 2048> &physic_service::get_rigid2d_list() {
    return this->rigid2d_list;
}

uint32_t physic_service::get_rigid2d_iterator() {
    return this->rigid2d_iterator;
}
