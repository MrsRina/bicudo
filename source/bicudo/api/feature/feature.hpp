#ifndef BICUDO_API_FEATURE_H
#define BICUDO_API_FEATURE_H

#include <iostream>

namespace bicudo {
    enum class features {
        undefined, module, scene, component, surface
    };

    class feature {
    protected:
        int32_t id {};
        bool dead {};
        bool initialised {};
    public:
        bicudo::features mode {bicudo::features::undefined};

        virtual void on_create();
        virtual void on_destroy();

        void set_id(int32_t);
        int32_t get_id();

        void set_dead(bool);
        bool is_dead();
        bool is_initialised();
    };
}

#endif