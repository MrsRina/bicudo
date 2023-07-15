#ifndef BICUDO_UTIL_PRIORITY_H
#define BICUDO_UTIL_PRIORITY_H

#include <functional>

namespace bicudo {
    enum look {
        low, medium, high
    };

    enum stack {
        toplevel = 0, secondary = 1
    };

    struct task {
    public:
        void *p_data {};
        std::function<void(void*)> function {};
    };
}

#endif