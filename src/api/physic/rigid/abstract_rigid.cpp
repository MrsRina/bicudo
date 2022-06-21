#include "abstract_rigid.h"
#include "api/client/instance.h"

void abstract_rigid::set_type(rigid::type val_type) {
    this->type = val_type;
}

rigid::type abstract_rigid::get_type() {
    return this->type;
}

bool abstract_rigid::is_colliding(abstract_rigid *abstract) {
    return this->minx <= abstract->maxx && this->miny <= this->maxy && this->maxx >= this->miny && abstract->maxy >= this->miny;
}
