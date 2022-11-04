#ifndef BICUDO_API_MODULE_H
#define BICUDO_API_MODULE_H

#include "registry.hpp"
#include "base.hpp"
#include "bicudo/api/feature/feature.hpp"

namespace bicudo {
    class module : public bicudo::modulebase, public bicudo::moduleregistry, public bicudo::feature {
    public:

    };
}

#endif