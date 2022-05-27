#include "module_service.h"

module* module_service::get_module_by_name(const std::string &name) {
    for (module* &modules : this->element_list) {
        if (modules->get_name() == name) {
            return modules;
        }
    }

    return NULL;
}

module* module_service::get_module_by_feature_id(uint32_t feature_id) {
    for (module* &modules : this->element_list) {
        if (modules->get_feature_id() == feature_id) {
            return modules;
        }
    }

    return NULL;
}

void module_service::on_start() {

}

void module_service::on_end() {

}