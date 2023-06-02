#ifndef BICUDO_CORE_H
#define BICUDO_CORE_H

#include "../feature/feature.hpp"
#include "../direct/display.hpp"
#include "../service/servicedisplay.hpp"
#include "bicudo/service/servicescene.hpp"
#include "bicudo/service/servicephysicengine.hpp"

namespace bicudo {
    class core {
    public:
        bicudo::servicedisplay service_display {};
        bicudo::servicescene service_scene {};
        bicudo::servicephysicengine service_physic_engine {};

        bool window_show {};
        bool running_mainloop {};
        bool vsync {};

        uint64_t capped_fps {};
        float delta {};
    public:
        void on_native_init();
        void on_native_quit();

        int32_t mainloop();
    };
}

#endif