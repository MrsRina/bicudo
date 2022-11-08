#ifndef BICUDO_API_SCENE_H
#define BICUDO_API_SCENE_H

#include "bicudo/api/feature/feature.hpp"
#include <iostream>

namespace bicudo {
    class scene : public bicudo::feature {
    public:
        std::string tag {};
        std::string description {};

        virtual void on_update();
    };
}

#endif