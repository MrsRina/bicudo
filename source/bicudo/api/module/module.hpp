#ifndef BICUDO_API_MODULE_H
#define BICUDO_API_MODULE_H

#include "bicudo/api/feature/feature.hpp"
#include <iostream>

namespace bicudo {
    class module : public bicudo::feature {
    private:
        bicudo::features mode {bicudo::features::module};
    protected:
        bool enabled {};
    public:
        std::string tag {};
        std::string description {};

        void set_enabled(bool);
        bool is_enabled();
    };
}

#endif