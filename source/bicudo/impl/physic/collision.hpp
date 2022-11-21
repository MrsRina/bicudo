#ifndef BICUDO_IMPL_PHYSIC_H
#define BICUDO_IMPL_PHYSIC_H

#include "bicudo/api/util/math.hpp"
#include "bicudo/api/rigid/rigid.hpp"

namespace bicudo {
    bool find_axis_least_penetration(bicudo::collideinfo&, bicudo::rigid*, bicudo::rigid*);
    bool check_collideinfo(bicudo::collideinfo&, bicudo::rigid*, bicudo::rigid*);
    bool check_collide_mask(bicudo::rigid*, bicudo::rigid*);
}

#endif