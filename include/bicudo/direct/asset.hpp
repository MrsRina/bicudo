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
        std::vector<bicudo::resource*> loaded_resource_list {};
        std::string tag {};
    public:
        void do_load_resources();
        bicudo::resource *get(uint64_t index);
        int32_t &id();
    };
}

#endif