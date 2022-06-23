#include "api/physic/rigid.h"

rigid::type rigid2d::get_type() {
    return this->type;
}

void rigid2d::set_physic(rigid::physic val_enum) {
    this->physic = val_enum;
}

rigid::physic rigid2d::get_physic() {
    return this->physic;
}

bool rigid2d::collide_ab_with(rigid2d *&r) {
    return this->minx <= r->maxx && this->miny <= this->maxy && this->maxx >= this->miny && r->maxy >= this->miny;
}

bool rigid2d::collide_axis_with(rigid2d *&r) {
    bool flag_collided = false;

    switch (r->get_type()) {
        case rigid::type::RIGID2D_RECTANGLE:
            auto rigid2d_rect_obj = (rigid2d_rectangle*) r;

            if (this->type == rigid::type::RIGID2D_RECTANGLE) {
                flag_collided = rigid2d_rect_collide_with_rect((rigid2d_rectangle*) this, rigid2d_rect_obj);
            }

            break;
    }

    return flag_collided;
}
