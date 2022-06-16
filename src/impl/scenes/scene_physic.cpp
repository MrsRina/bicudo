#include "scene_physic.h"
#include "api/client/instance.h"
#include "api/render/tessellator.h"

class rigid_circle {
public:
    float x, y, r;
    float mx, my;

    bool grounded;
    uint64_t last_time;

    rigid_circle(float pos_x, float pos_y, float radius) {
        this->x = pos_x;
        this->y = pos_y;
        this->r = radius;

        grounded = false;
        last_time = 0;
    }

    void on_locked_update() {
        if (!grounded) {
            this->my -= 0.5 * util::timing->locked_delta - last_time;
        } else {
            last_time = util::timing->locked_delta;
        }
        
        this->x += this->mx * util::timing->locked_delta_time;
        this->y -= this->my * util::timing->locked_delta_time;

        util::log("goo");
    }
};

std::vector<rigid_circle> rigid_objs;

material material_shape;
scene_physic *scene_physic::instance = nullptr;

void scene_physic::on_start() {
    material_shape.color.set(255, 255, 255, 100);

    rigid_circle rigid(50, 50, 70);
    rigid_objs.push_back(rigid);
}

void scene_physic::on_end() {

}

void scene_physic::on_event(SDL_Event &sdl_event) {

}

void scene_physic::on_locked_update() {
    for (rigid_circle &rigids : rigid_objs) {
        rigids.on_locked_update();
    }
}

void scene_physic::on_update() {

}

void scene_physic::on_render() {
    for (rigid_circle &rigids : rigid_objs) {
        draw::shape::circle(rigids.x, rigids.y, rigids.r, material_shape);
    }
}