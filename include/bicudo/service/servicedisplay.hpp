#ifndef BICUDO_SERVICE_DISPLAY_H
#define BICUDO_SERVICE_DISPLAY_H

#include "bicudo/feature/service.hpp"
#include "bicudo/direct/display.hpp"
#include "bicudo/platform/contextoverview.hpp"

namespace bicudo {
    class servicedisplay : public service<bicudo::display> {
    protected:
        bicudo::contextoverview *p_context_overview {};
    public:
        void set_context_overview(bicudo::contextoverview *p_context_overview);
        void add(bicudo::feature<bicudo::display> *p_feature) override;
        bicudo::display &get_display(uint32_t priority);
    };
}

#endif