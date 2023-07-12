#ifndef BICUDO_FEATURE_SERVICE_H
#define BICUDO_FEATURE_SERVICE_H

#include "feature.hpp"
#include <vector>

namespace bicudo {
    template<typename T>
    class service {
    public:
        std::vector<bicudo::feature<T>*> features {};

        virtual void add(bicudo::feature<T> *p_feature) {
            this->features.push_back(p_feature);
        }
    };
}

#endif