#ifndef BICUDO_DIRECT_ASSET_H
#define BICUDO_DIRECT_ASSET_H

#include "bicudo/direct/resource/resource.hpp"
#include "bicudo/platform/platform.hpp"
#include <iostream>
#include <vector>

namespace bicudo {
    struct assetdescriptor {
        const char *p_tag {};
        uint32_t resource_count {};
        bicudo::resource **pp_resources {};
    };

    class asset {
    protected:
        int32_t asset_id {};
    public:
       std::vector<bicudo::resource*> resources {};
       std::string tag {};
   public:
       int32_t &id();
    };
}

#endif