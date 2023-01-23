#ifndef BICUDO_CORE_H
#define BICUDO_CORE_H

#include "../feature/feature.hpp"
#include "../direct/display.hpp"
#include "../service/service_display.hpp"
#include "bicudo/service/service_scene.hpp"

namespace bicudo {
    class core {
    public:
        bicudo::service_display service_display {};
        bicudo::service_scene service_scene {};

        bool window_show {};
        bool running_mainloop {};
        bool vsync {};

        uint64_t capped_fps {};
        float delta {};

        void on_native_init();
        void on_native_quit();

        int32_t mainloop();
    };
}

#endif