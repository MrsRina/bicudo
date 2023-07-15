#ifndef BICUDO_CORE_H
#define BICUDO_CORE_H

#include "bicudo/direct/displayservice.hpp"
#include "bicudo/direct/sceneservice.hpp"
#include "bicudo/util/logger.hpp"
#include "bicudo/util/priority.hpp"

#include <queue>

namespace bicudo {
    struct coreproperty {
    public:
        bicudo::displayservice *p_display_service {};
        bicudo::sceneservice *p_scene_service {};
    };

    struct core {
    public:
        bicudo::displayservice *p_display_service {};
        bicudo::sceneservice *p_scene_service {};
    protected:
        bool window_show {};
        bool running_mainloop {};
        bool vsync {};

        uint64_t capped_fps {};
        float delta {};

        std::queue<bicudo::task> task_queue {};
    protected:
        void on_init_all();
        void on_quit_all();
    public:
        void set_core_property(bicudo::coreproperty &core_property);
        bicudo::task &generate_task();
        int32_t mainloop();
    };
}

#endif