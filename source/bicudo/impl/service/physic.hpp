#ifndef BICUDO_IMPL_SERVICE_PHYSIC_H
#define BICUDO_IMPL_SERVICE_PHYSIC_H

#include "bicudo/api/rigid/rigid.hpp"
#include <vector>

namespace bicudo {
    class physic {
    protected:
        std::vector<bicudo::rigid*> loaded_rigid_list {};
    };
}

#endif