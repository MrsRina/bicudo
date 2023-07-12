#ifndef BICUDO_PHYSIC_COLLIDE_INFO_H
#define BICUDO_PHYSIC_COLLIDE_INFO_H

#include "bicudo/util/math.hpp"
#include "rigid.hpp"

namespace bicudo {
    typedef struct collideinfo {
        bicudo::vec2 normal {}, start {}, end {};
        float distance {};
    } collideinfo;

    typedef struct supportinfo {
        bicudo::vec2 point {};
        float projection {};
        float distance {};
    } supportinfo;

    void changedir(bicudo::collideinfo &r);
    void setcollideinfo(bicudo::collideinfo &collide_info, float distance, const bicudo::vec2 &n, const bicudo::vec2 &s);

    bool findcollideinfo(bicudo::rigid &r, bicudo::rigid &l, bicudo::collideinfo &collide_info);
    bool checksupportpoint(bicudo::rigid &r, bicudo::vec2 &direction_projection, bicudo::vec2 &vertex_projected, bicudo::supportinfo &support_info);
    bool checkcollision(bicudo::rigid &r, bicudo::rigid &l, bicudo::collideinfo &collide_info);
}

#endif