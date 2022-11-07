#include "bicudo/bicudo.hpp"

bicudo::profile* bicudo::core {nullptr}; 

void bicudo::init() {
    bicudo::core = new bicudo::profile {};
    bicudo::core->do_create();
}

void bicudo::create(bicudo::surface *surf) {
    bicudo::core->dispatch_surface(surf);
}

void bicudo::destroy(bicudo::surface *) {

}
