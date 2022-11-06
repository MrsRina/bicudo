#ifndef BICUDO_API_MODULE_H
#define BICUDO_API_MODULE_H

#include "registry.hpp"
#include "base.hpp"
#include "bicudo/api/feature/feature.hpp"

namespace bicudo {
    class module : public bicudo::module_base, public bicudo::module_registry, public bicudo::feature {
    public:

    };
}

#endif