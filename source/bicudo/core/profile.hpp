#ifndef BICUDO_CORE_H
#define BICUDO_CORE_H

#include "bicudo/api/surface/surface.hpp"
#include "bicudo/api/util/log.hpp"
#include "bicudo/impl/gc/garbage_collector.hpp"
#include "bicudo/gpu/driver_impl_manager.hpp"
#include "bicudo/impl/service/handler.hpp"

namespace bicudo {
    class profile {
    protected:
        std::vector<bicudo::surface*> surfaces {};
        bicudo::logger* logger {nullptr};
        bicudo::garbage_collector custom_gc {};
        bicudo::driver_impl_manager* driver_impl_manager {nullptr};
        bicudo::handler *handler {nullptr};

        bool mainloop {};
        uint64_t cpu_interval_ticks {};
    public:
        void dispatch_surface(bicudo::surface*);
        void set_capped_fps(uint64_t);
        void set_vsync(bool);

        void do_create();
        void do_destroy();
        void do_loop();

        bicudo::garbage_collector &get_custom_gc();
        bicudo::logger *get_logger();
        bicudo::handler *get_handler();
    };
}

#endif