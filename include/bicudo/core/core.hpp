#ifndef BICUDO_CORE_H
#define BICUDO_CORE_H

#include "bicudo/direct/displayservice.hpp"
#include "bicudo/util/logger.hpp"

namespace bicudo {
    struct core {
    public:
        bicudo::displayservice *p_display_service {};
    protected:
        bool window_show {};
        bool running_mainloop {};
        bool vsync {};

        uint64_t capped_fps {};
        float delta {};
    protected:
        void on_init_all();
        void on_quit_all();
    public:
        explicit core() {
            this->on_init_all();
        }

        int32_t mainloop();
    };
}

#endif