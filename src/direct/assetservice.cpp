#include "bicudo/direct/assetservice.hpp"
#include "bicudo/bicudo.hpp"

bicudo::asset *bicudo::assetservice::get(std::string_view tag) {
    return this->loaded_asset_unordered_map[tag.data()];
}

void bicudo::assetservice::registry(bicudo::assetdescriptor &asset_descriptor, bicudo::asset *p_asset) {
    p_asset->tag = asset_descriptor.p_tag;
    p_asset->loaded_resource_list.resize(asset_descriptor.resource_count);

    for (uint64_t it {}; it < p_asset->loaded_resource_list.size(); it++) {
        p_asset->loaded_resource_list.at(it) = asset_descriptor.pp_resources[it];
    }

    if (!this->loaded_asset_unordered_map.count(p_asset->tag)) {
        this->loaded_asset_unordered_map.insert({p_asset->tag, p_asset});
        bicudo::kernel::p_core->generate_task() = {
            .p_data   = nullptr,
            .function = [p_asset](void*) {
                p_asset->do_load_resources();
            }
        };
    }
}