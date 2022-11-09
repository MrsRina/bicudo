#ifndef BICUDO_CORE_H
#define BICUDO_CORE_H

#include "bicudo/api/surface/surface.hpp"
#include "bicudo/api/util/log.hpp"
#include "bicudo/impl/gc/gc.hpp"

namespace bicudo {
    class profile {
    protected:
        std::vector<bicudo::surface*> surfaces {};
        bicudo::logger* logger {nullptr};
        bicudo::gc custom_gc {};

        bool mainloop {};
    public:
        void dispatch_surface(bicudo::surface*);

        void do_create();
        void do_destroy();
        void do_loop();

        bicudo::gc &custom_garbage_collector();
        bicudo:logger* get_logger();
    };
}

#endif