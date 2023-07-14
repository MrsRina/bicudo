#ifndef BICUDO_SERVICE_H
#define BICUDO_SERVICE_H

#include <iostream>
#include <vector>

namespace bicudo {
    template<typename t, typename s>
    class service {
    protected:
        std::vector<t> features {};
    public:
        std::vector<t> &get_features() { return this->features; }
        virtual void add(t feature) { this->features.push_back(feature); }
        virtual t get(s) { return {}; }
        virtual int64_t find(s) { return -1; };
        virtual void on_init() {};
        virtual void on_quit() {};
    };
}

#endif