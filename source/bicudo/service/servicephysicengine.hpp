#ifndef BICUDO_SERVICE_PHYSIC_ENGINE_H
#define BICUDO_SERVICE_PHYSIC_ENGINE_H

#include "../feature/service.hpp"
#include "../physic/rigid.hpp"
#include "../opengl/opengltools.hpp"
#include "../physic/physicsat.hpp"

namespace bicudo {
    class servicephysicengine : public service<bicudo::rigid> {
    protected:
        buffering buffer {};
        shader *p_shader_debug {};
        bicudo::collideinfo collide_info {};
        bicudo::vec2 gravity {0, 90.0f};
        float angle {};
    public:
        void update_mass(bicudo::rigid *p_rigid, float delta);
        void set_gravity(float x, float y);
        bicudo::vec2 get_current_gravity();

        void on_native_init();
        void on_native_quit();
        void on_native_update();
        void on_native_render();

        void add(bicudo::feature<bicudo::rigid> *p_feature) override;
        void process_displacement_resolution(bicudo::rigid &l, bicudo::rigid &r);
    };
}

#endif