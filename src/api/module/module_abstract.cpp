#include "module_abstract.h"

void module_abstract::set_name(const std::string &module_name) {
    this->name = module_name;
}

std::string module_abstract::get_name() {
    return this->name;
}

void module_abstract::set_description(const std::string &module_description) {
    this->description = module_description;
}

std::string module_abstract::get_description() {
    return this->description;
}

void module_abstract::set_enable_state(bool state) {
    this->enabled = state;
}

bool module_abstract::is_enabled() {
    return this->enabled;
}

void module_abstract::registry(const std::string &module_name, const std::string &module_description) {
    this->set_name(module_name);
    this->set_description(module_description);
}