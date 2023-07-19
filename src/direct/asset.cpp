#include "bicudo/direct/asset.hpp"

void bicudo::asset::do_load_resources() {
    for (bicudo::resource *&p_resource : this->loaded_resource_list) {
        p_resource->on_load();
    }
}

int32_t &bicudo::asset::id() {
    return this->asset_id;
}

bicudo::resource *bicudo::asset::get(uint64_t index) {
    return this->loaded_resource_list.at(index);
}