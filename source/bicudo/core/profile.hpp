#ifndef BICUDO_CORE_H
#define BICUDO_CORE_H

#include "bicudo/api/surface/native.hpp"
#include "bicudo/api/util/log.hpp"

namespace bicudo {
    class profile {
    protected:
        bicudo::surface_native* surface_native {nullptr};
        bicudo::logger* logger {nullptr};
    public:
        void do_create_feature(bicudo::feature*);
        void do_destroy_feature(bicudo::feature*);

        void do_create();
        void do_destroy();
        void do_loop();
    };
}

#endif