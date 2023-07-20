#ifndef BICUDO_CORE_H
#define BICUDO_CORE_H

#include "bicudo/direct/displayservice.hpp"
#include "bicudo/direct/sceneservice.hpp"
#include "bicudo/direct/assetservice.hpp"
#include "bicudo/util/logger.hpp"
#include "bicudo/util/priority.hpp"

#include <queue>

namespace bicudo {
    struct coreproperty {
    public:
        bicudo::displayservice *p_display_service {};
        bicudo::sceneservice *p_scene_service {};
        bicudo::assetservice *p_asset_service {};
    };

    struct core {
    public:
        bicudo::displayservice *p_display_service {};
        bicudo::sceneservice *p_scene_service {};
        bicudo::assetservice *p_asset_service {};
        bicudo::vec4 clean_color {0.34547584f, 0.12231312f, 1.0f, 1.0f};
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