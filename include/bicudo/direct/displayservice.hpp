#ifndef BICUDO_DISPLAY_SERVICE_H
#define BICUDO_DISPLAY_SERVICE_H

#include "bicudo/service/service.hpp"
#include "display.hpp"
#include "bicudo/platform/contextoverview.hpp"

namespace bicudo {
    class displayservice : public service<bicudo::display*, int32_t> {
    protected:
        int32_t highest_token {};
    public:
        void update(bicudo::displayproperty &display_property, bicudo::display *p_display);
    public:
        int64_t find(int32_t id) override;
        bicudo::display *get(int32_t index) override;
        void add(bicudo::display *p_display) override;
    };
}

#endif