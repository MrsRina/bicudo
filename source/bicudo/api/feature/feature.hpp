#ifndef BICUDO_API_FEATURE_H
#define BICUDO_API_FEATURE_H

namespace bicudo {
    enum class features {
        undefined, module, scene, component, surface
    };

    class feature {
    public:
        bicudo::features mode {bicudo::features::undefined};

        virtual void on_create();
        virtual void on_destroy();
    };
}

#endif