#ifndef BICUDO_CORE_H
#define BICUDO_CORE_H

#include "bicudo/api/surface/surface.hpp"
#include "bicudo/api/util/log.hpp"
#include "bicudo/impl/gc/garbage_collector.hpp"
#include "bicudo/gpu/glimpl.hpp"
#include "bicudo/impl/handler/handler.hpp"
#include "bicudo/impl/physic/physic.hpp"
#include "bicudo/impl/input/input.hpp"
#include "bicudo/core/mixin.hpp"

namespace bicudo {
    class profile {
    protected:
        std::vector<bicudo::surface*> surfaces {};
        bicudo::mixin runtime_initialisation {}, runtime_eventlistener {}, runtime_update {}, runtime_unsafeupdate {}, runtime_render {};

        bicudo::logger* logger {nullptr};
        bicudo::garbage_collector custom_gc {};
        bicudo::glimpl *driver_impl_manager {nullptr};
        bicudo::handler *handler {nullptr};
        bicudo::physic *physic {};
        bicudo::input *input {};

        bool mainloop {};
        uint8_t async_quit_stage {};
        uint64_t cpu_ticks_interval {};

        void update_render_matrices();
        void process_internal_event(bicudo::event&);
    public:
        void dispatch_surface(bicudo::surface*);
        void set_capped_fps(uint64_t);
        void set_vsync(bool);

        void do_create();
        void do_destroy();
        void do_loop();
        void do_unsafe_update();

        bicudo::garbage_collector &get_custom_gc();
        bicudo::logger *get_logger();
        bicudo::handler *get_handler();
        bicudo::physic *get_physic();
        bicudo::input *get_input();

        void inject(bicudo::runtime, bicudo::mixin&);
        bool is_mainloop_running();
        void end_mainloop();
    };

    void unsafe(bicudo::profile*);
}

#endif