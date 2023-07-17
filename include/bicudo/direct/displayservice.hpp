#ifndef BICUDO_DIRECT_DISPLAY_SERVICE_H
#define BICUDO_DIRECT_DISPLAY_SERVICE_H

#include "bicudo/platform/contextoverview.hpp"
#include "display.hpp"
#include <vector>

namespace bicudo {
    class displayservice {
    protected:
        std::vector<bicudo::display*> loaded_display_list {};
        int32_t highest_token {};
    public:
        void update(bicudo::displayproperty &display_property, bicudo::display *p_display);
        int64_t find(int32_t id);
        bicudo::display *get(int32_t index);
        void add(bicudo::display *p_display);
        void on_shutdown();
    };
}

#endif