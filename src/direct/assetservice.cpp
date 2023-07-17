#include "bicudo/direct/assetservice.hpp"

bicudo::asset *bicudo::assetservice::get(std::string_view tag) {
    return this->loaded_asset_unordered_map[tag.data()];
}

void bicudo::assetservice::registry(bicudo::assetdescriptor &asset_descriptor, bicudo::asset *p_asset) {
    p_asset->tag = asset_descriptor.p_tag;
    p_asset->resources.resize(asset_descriptor.resource_count);

    for (uint64_t it {}; it < p_asset->resources.size(); it++) {
        p_asset->resources.at(it) = asset_descriptor.pp_resources[it];
    }

    this->loaded_asset_unordered_map.insert({p_asset->tag, p_asset});
}