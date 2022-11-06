#ifndef BICUDO_API_COMPONENT_H
#define BICUDO_API_COMPONENT_H

#include "bicudo/api/feature/feature.hpp"

template<typename t>
class component : public feature {
public:
    t object {};
};

#endif