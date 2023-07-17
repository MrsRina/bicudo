#ifndef BICUDO_DIRECT_RESOURCE_H
#define BICUDO_DIRECT_RESOURCE_H

#include <cinttypes>

namespace bicudo {
    enum class resourcetype {
        abstract, shadergroup, texture
    };

    class resource {
    public:
        resourcetype type {};
    public:
        virtual void on_load() {};
        virtual void on_destroy() {};
        virtual uint32_t get_program() { return 0; };
    };
}

#endif