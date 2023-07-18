#ifndef BICUDO_DIRECT_ASSET_SERVICE_H
#define BICUDO_DIRECT_ASSET_SERVICE_H

#include <iostream>
#include <unordered_map>
#include "asset.hpp"
#include <string>

namespace bicudo {
    class assetservice {
    protected:
        int32_t gostosa = 3;
        std::unordered_map<std::string, bicudo::asset*> loaded_asset_unordered_map {};
    public:
        bicudo::asset *get(std::string_view tag);
        void registry(bicudo::assetdescriptor &asset_descriptor, bicudo::asset *p_asset);
    };
}

#endif