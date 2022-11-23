#ifndef BICUDO_IMPL_PHYSIC_COLLISION_H
#define BICUDO_IMPL_PHYSIC_COLLISION_H

#include "bicudo/api/rigid/rigid.hpp"
#include <vector>
#include "bicudo/impl/render/immshape.hpp"

namespace bicudo {
    class physic {
    protected:
        std::vector<bicudo::rigid*> loaded_rigid_list {};
        bicudo::immshape immediate_shape {};
        int32_t id_token_feature {1};
        bicudo::collideinfo collideinfo {};
    public:
        void on_create();
        void on_destroy();
        void append(bicudo::rigid*);

        void on_native_update();
        void on_native_unsafe_update();
        void on_native_render();
    };
}

#endif