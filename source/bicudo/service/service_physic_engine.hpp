#ifndef BICUDO_SERVICE_PHYSIC_ENGINE_H
#define BICUDO_SERVICE_PHYSIC_ENGINE_H

#include "../feature/service.hpp"
#include "../physic/rigid.hpp"
#include "../opengl/opengl_tools.hpp"
#include "../physic/physic_sat.hpp"

namespace bicudo {
    class service_physic_engine : public service<bicudo::rigid> {
    protected:
        buffering buffer {};
        shader *p_shader_debug {};
        bicudo::collideinfo collide_info {};
    public:
        void on_native_init();
        void on_native_quit();
        void on_native_update();
        void on_native_render();

        void process_displacement_resolution(bicudo::rigid &r, bicudo::rigid &l);
    };
}

#endif