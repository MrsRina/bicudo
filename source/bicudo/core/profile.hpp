#ifndef BICUDO_CORE_H
#define BICUDO_CORE_H

#include "bicudo/api/surface/surface.hpp"
#include "bicudo/api/util/log.hpp"

namespace bicudo {
    class profile {
    protected:
        std::vector<bicudo::surface*> surfaces {};
        bicudo::logger* logger {nullptr};
    public:
        void dispatch_surface(bicudo::surface*);

        void do_create();
        void do_destroy();
        void do_loop();
    };
}

#endif