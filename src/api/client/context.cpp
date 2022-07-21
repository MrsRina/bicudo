#include "api/client/instance.h"

void context::add_module(const std::string &name, const std::string &description, module* feature) {
    feature->registry(name, description);
    BICUDO->get_module_manager().add(feature);
}