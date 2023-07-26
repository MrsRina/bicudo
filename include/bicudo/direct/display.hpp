#ifndef BICUDO_NATIVE_DISPLAY_H
#define BICUDO_NATIVE_DISPLAY_H

#include "bicudo/platform/platform.hpp"
#include "bicudo/platform/contextoverview.hpp"
#include "bicudo/util/math.hpp"

namespace bicudo {
    struct displayproperty {
    public:
        const char *p_title {};
        bicudo::ivec2 size {-1, -1};
        bicudo::ivec2 position {-1, -1};
        int8_t fullscreen {-1};
        int8_t resizable {-1};
        int8_t vsync {-2};
        bicudo::contextoverview *p_api_context_overview {};
    };

    class display {
    protected:
        SDL_Window *p_root {};
        uint16_t context_api {};
        int32_t display_id {};
        int8_t vysnc {};
    public:
        bicudo::ivec2 size {};
    public:
        int32_t &id();
        SDL_Window *&root();
    };
}

#endif