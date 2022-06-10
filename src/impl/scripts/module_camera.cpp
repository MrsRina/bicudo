#include "module_camera.h"
#include "api/render/tessellator.h"

module_camera *module_camera::instance = nullptr;

void module_camera::set_pos(double pos_x, double pos_y, double pos_z) {
    this->x = pos_x;
    this->y = pos_y;
    this->z = pos_z;
}

void module_camera::on_start() {

}

void module_camera::on_end() {

}

void module_camera::on_event(SDL_Event &sdl_event) {

}

void module_camera::on_locked_update(uint64_t delta) {

}

void module_camera::on_update(uint64_t delta) {

}

void module_camera::on_render(float render_time) {
    draw::immediate::batch(GL_TRIANGLES, 6);
    draw::immediate::vertex(0.0f, 0);
    draw::immediate::vertex(0.0f, 0);
    draw::immediate::vertex(0.0f, 0);
    draw::immediate::draw();
}