#include "abstract_rigid.h"
#include "api/client/instance.h"

void abstract_rigid::set_type(rigid::type val_type) {
    this->type = val_type;
}

rigid::type abstract_rigid::get_type() {
    return this->type;
}