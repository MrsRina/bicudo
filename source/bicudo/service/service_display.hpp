#ifndef BICUDO_SERVICE_DISPLAY_H
#define BICUDO_SERVICE_DISPLAY_H

#include "../feature/service.hpp"
#include "../direct/display.hpp"

namespace bicudo {
    class service_display : public service<bicudo::display> {
    public:
        void add(bicudo::feature<bicudo::display> *p_feature) override;
        bicudo::display &get_display(uint32_t priority);
    };
}

#endif