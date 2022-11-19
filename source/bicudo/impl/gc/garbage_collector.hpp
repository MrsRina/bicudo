#ifndef BICUDO_IMPL_GC_H
#define BICUDO_IMPL_GC_H

#include <queue>
#include "bicudo/api/feature/feature.hpp"

namespace bicudo {
    class garbage_collector {
    protected:
        std::queue<bicudo::feature*> features_queue {};
        bool poll_features_queue {};
    public:
        void destroy(bicudo::feature*);
        void create(bicudo::feature*);
        void on_native_update();
    };
};

#endif